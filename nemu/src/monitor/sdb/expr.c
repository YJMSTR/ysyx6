/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <memory/vaddr.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ = '=',
  /* TODO: Add more token types */
  // 我们先来处理一种简单的情况 -- 算术表达式, 
  // 即待求值表达式中只允许出现以下的token类型:十进制数，加减乘除，括号，空格串
  TK_NUM = '0',
  TK_PLUS = '+',
  TK_SUB = '-',
  TK_MUL = '*',
  TK_DIV = '/',
  TK_LPAR = '(',
  TK_RPAR = ')',
  TK_HEX = 'x',
  TK_REG = '$',
  TK_NEQ = '!',
  TK_AND = '&',
  TK_DEREF,
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"\\-", TK_SUB},      // minus
  {"\\*", TK_MUL},      // multi
  {"/", TK_DIV},        // div
  {"\\(", TK_LPAR},    
  {"\\)", TK_RPAR},   
  {"[0-9]+", TK_NUM},     // 十进制数
  {"0[xX][0-9a-fA-F]+", TK_HEX},   // 十六进制数
  {"[\\$][0-9a-zA-Z]+", TK_REG},   // 寄存器
  {"!=", TK_NEQ},
  {"&&", TK_AND},
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;
// 为了支持负数扩容到64，因为填充的0要占token
// 默认负数前面有括号，除非负号是 token 0
// 测试表达式求值，将其改成65536
static Token tokens[65536] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case TK_NOTYPE:
            continue;
          default: 
            tokens[nr_token].type = rules[i].token_type;
        }
        if (substr_len >= 32) {
          // 缓冲区会溢出
          Log("regex token str too long, err");
          return false;
        }
        memset (tokens[nr_token].str, '\0', sizeof(tokens[nr_token].str));
        strncpy (tokens[nr_token].str, substr_start, substr_len);
        tokens[nr_token].str[substr_len] = '\0';
        nr_token++;
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }
  // 处理负号
  Token real_tokens[65536];
  int real_nr_token = 0;
  for (int i = 0; i < nr_token; i++) {
    if (tokens[i].type == '-') {
      if (i == 0 || tokens[i-1].type == '(') {
        memset(real_tokens[real_nr_token].str, '\0', sizeof(real_tokens[real_nr_token].str));
        real_tokens[real_nr_token].str[0] = '0';
        real_tokens[real_nr_token++].type = TK_NUM;
      } 
    }
    real_tokens[real_nr_token] = tokens[i];
    real_nr_token++;
  }
  for (int i = 0; i < real_nr_token; i++) {
    tokens[i] = real_tokens[i];
    Log("real_tokens[%d].type=%d str=%s\n", i, tokens[i].type, tokens[i].str);
  }
  nr_token = real_nr_token;
  return true;
}

bool check_parentheses_match(int p, int q) {
	if (p > q) return true;
	int s = 0;
	for (int i = p; i <= q; i++) {
		if (tokens[i].type == '(') s++;
		else if (tokens[i].type == ')') s--;
		if (s < 0) return false;
	}
  //Log("check parentheses match (%d %d) = %d", p, q, s == 0);
	return (s == 0);
}


bool check_parentheses(int p, int q) {
  bool res = tokens[p].type == '(' 
	&& tokens[q].type == ')' 
	&& check_parentheses_match(p+1, q-1);	//中间得是合法括号序列
  //Log("check parentheses (%d %d) = %d", p, q, res);
	return res;
}

word_t eval(int p, int q) {
  Log("eval %d %d", p, q);
  if (p > q) {
    Log("Bad expression, p > q");
    return -1;
  } else if (p == q) {
    Assert(tokens[p].type == TK_NUM || tokens[p].type == TK_REG, "illegal expr");
    if (tokens[p].type == TK_REG) {  
      bool success = false;
      word_t regval = isa_reg_str2val(tokens[p].str, &success);
      Assert(success == true, "isa_reg_str2val fail, success=%d", success);
      return regval;
    }
    return (word_t)atoi(tokens[p].str);
  } else if (check_parentheses(p, q) == true) {
    return eval(p + 1, q - 1);
  } else {
    int op = -1;
    int sump = 0;
    for (int i = p; i <= q; i++) {
      switch(tokens[i].type) {
        case '+':
        case '-':
          if (sump == 0)
            op = i;
          break;
        case TK_AND:
          if (sump == 0) 
            op = i;
          break;
        case TK_NEQ:
        case TK_EQ:
          if (sump == 0)
            op = i;
          break;
        case '*':
        case '/':
          if (sump == 0)
            op = i;
          break;
        case '(':
          sump++;
          break;
        case ')':
          sump--;
          break;
        case TK_DEREF:
          if (op == -1)
            op = i;
        case TK_NUM:
        case TK_REG:
        case TK_NOTYPE:
          continue;
        default:
          Assert(0, "op token type unsupport, token[%d].type=%d str=%s,p=%d,q=%d", i, tokens[i].type,tokens[i].str, p, q);
      }
    }
    if (op == -1) {
      Log("op == -1, p == %d, q == %d", p, q);
      return -1;
    } 
    if (tokens[op].type == TK_DEREF) {
      Log("DEREF op = %d token (%d %d)", op, p, q);
      word_t val = eval(op+1, q);
      Log("DEREF addr = 0x%08x == %u", val, val);
      word_t res = vaddr_read(val, 4);
      Log("DEREF res = 0x%08x == %u", res, res);
      return res;
    }
    word_t val1 = eval(p, op-1);
    word_t val2 = eval(op+1, q);

    switch (tokens[op].type) {
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      case TK_AND: return val1 && val2;
      case TK_EQ: return val1 == val2;
      case TK_NEQ: return val1 != val2;
      default: Assert(0, "token unsupport");
    }
  }
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  for (int i = 0; i < nr_token; i++) {
    if (tokens[i].type == '*' && (i == 0 || tokens[i-1].type == '+' || tokens[i-1].type == '-' || tokens[i-1].type == '*' || tokens[i-1].type == '/' || tokens[i-1].type == '(')) {
      tokens[i].type = TK_DEREF;
    }
  }

  word_t val = eval(0, nr_token-1);
  *success = true;
  return val;
}
