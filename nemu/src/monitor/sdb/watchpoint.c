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

#include "sdb.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

WP* new_wp() {
  Assert(free_ != NULL, "free WP pool is empty!");
  WP *ret;
  // 头删，尾插
  ret = free_;
  free_ = free_->next;
  ret->next = NULL;
  if (head == NULL) {
    head = ret;
    return head;
  } else {
    WP *cur = head;
    for (cur = head; cur->next != NULL; cur = cur->next);
    cur->next = ret;
  }
  return ret;
} 

void free_wp(int num) {
  //bool find_wp = false;
  WP *cur = NULL, *lst = NULL;
  for (cur = head; cur != NULL; cur = cur->next) {
    if (cur->NO == num) {
      if (lst != NULL) lst->next = cur->next;
      if (head == cur) {
        head = cur->next;
      }
      cur->next = free_;
      memset(cur->str, '\0', sizeof(cur->str));
      free_ = cur;
      break;
    }
    lst = cur;
  }
  if (cur == NULL) {
    printf("WP num %d not found!, current wp:\n", num);
    wp_print();
  }
}

void wp_print() {
  printf("Num\t\tWhat\t\tVal\n");
  for (WP* cur = head; cur != NULL; cur = cur->next) {
    printf("%d\t\t%s\t\t"FMT_WORD"\n", cur->NO, cur->str, cur->val);
  }
}

void check_wp() {
  for (WP *cur = head; cur != NULL; cur = cur->next) {
    bool suc = false;
    word_t curval = expr(cur->str, &suc);
    if (cur->val != curval) {
      printf("wp %d lastval = "FMT_WORD", curval = "FMT_WORD"\n", cur->NO, cur->val, curval);
      cur->val = curval;
      nemu_state.state = NEMU_STOP;
    }
  }
}

/* TODO: Implement the functionality of watchpoint */

