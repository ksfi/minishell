#ifndef __HEADER__
#define __HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_SIZE 256
#define OUI 1
#define NON 0

void bar() {
  printf("-----------\n");
}

typedef struct Token {
  char *val;
  struct Token *prev;
  struct Token *next;
  size_t len;
} Token;

Token *init(char *val) {
  Token *ret = malloc(sizeof(Token));
  ret->val = malloc(sizeof(val));
  strcpy(ret->val, val);
  ret->prev = NULL;
  ret->next = NULL;
  ret->len = 1;
  return ret;
  free(ret);
  free(ret->val);
}

void updateLen(Token *tok, size_t len) {
  while (tok != NULL) {
    tok->len = len;
    tok = tok->prev;
  }
}

Token *add(Token *prev, char *val) {
  Token *ret = init(val);
  ret->prev = prev;
  updateLen(ret, prev->len + 1);
  prev->next = ret;
  return ret;
  free(ret);
}

void display(Token *tok) {
  while (tok != NULL) {
    printf("%s\n", tok->val);
    tok = tok->next;
  }
}

#endif
