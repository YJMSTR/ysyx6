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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
// #include <utils.h>


// this should be enough
static char buf[65536] = {};
static int buf_pointer = 0;
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";



 uint32_t tmp_stk[33];

static void gen(char c) {
	buf[buf_pointer++] = c;
	buf[buf_pointer] = '\0';
}

static void gen_num() {
	uint32_t res = (uint32_t)rand()%32768u;
	//printf("rand == %u\n", res);
	int tmp = rand()%7;	//1/7的概率生成负数
	if (tmp == 0) {
		gen('(');
		gen('-');
	}
	//if (rand() & 1) gen('-');
	uint32_t i = 0;
	while (res) {
		tmp_stk[++i] = res % 10;
		res /= 10;
	}
	if (i==0) {
		buf[buf_pointer++] = '0';
		gen('u');
		buf[buf_pointer] = '\0';
		return;
	}
	while (i) {
		buf[buf_pointer++] = tmp_stk[i--]+'0';
	}
  gen('u'); 
	if(tmp == 0) gen(')');
}



static void gen_rand_op() {
	switch (rand()%4) {
		case 0: gen('+'); break;
		case 1: gen('-'); break;
		case 2: gen('*'); break;
		default: gen('/'); break;
	}
}

static void gen_rand_expr() {
  if (rand() & 1) gen(' ');
  if (buf_pointer >= 40000) {
    gen_num();
    if (rand()&1) gen(' ');
		buf[buf_pointer] = '\0';
		return;
  }
  switch (rand()%3) {
  	case 0: gen_num(); break;
  	case 1: gen('('); gen_rand_expr(); gen(')'); break;
  	default: 
  		gen_rand_expr(); 
  		gen_rand_op(); 
      if (buf[buf_pointer-1]=='/') {
        gen('(');
        gen_rand_expr();
        gen(')');
        break;
      }
  		gen_rand_expr(); break;
  }
  if (rand()&1) gen(' ');
  buf[buf_pointer]='\0';
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
POS:
    buf_pointer = 0;
    buf[0] = '\0';
    gen_rand_expr();
    //printf("buf = %s\n", buf);
    sprintf(code_buf, code_format, buf);
    //printf("code_buf = %s\n", code_buf);
    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -Wall -Werror -o  /tmp/.expr");
    if (ret != 0) {
      goto POS;
    }

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);
    printf("%u %s\n", result, buf);
  }
  return 0;
}
