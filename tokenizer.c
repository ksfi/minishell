#include "header.h"

// option in 2nd pos
Token *tokenizer(char *cmd) {
  char *tok = strtok(cmd, " ");
  Token *ret, *temp;
  size_t k = 0;
  while (tok != NULL) {
    if (k == 0) {
      ret = init(tok);
      temp = ret;
      k++;
    }
    else {
      Token *newTok = add(temp, tok);
      temp = newTok;
    }
    tok = strtok(NULL, " \n\t");
  }
  return ret;
  free(ret);
}

// options for exec syscall
char **options(Token *tok) {
  tok = tok->next;
  char **ret = malloc(tok->len);
  size_t i = 0;
  while (tok != NULL) {
    ret[i] = malloc(strlen(tok->val) * sizeof(char));
    strcpy(ret[i], tok->val);
    tok = tok->next;
    i++;
  }
  return ret;
  free(ret);
}

Token *pipelineTokenizer(char *cmd) {
  char *tok = strtok(cmd, " | ");
  Token *ret, *temp;
  size_t k = 0;
  while (tok != NULL) {
    if (k == 0) {
      ret = init(tok);
      temp = ret;
      k++;
    }
    else {
      Token *newTok = add(temp, tok);
      temp = newTok;
    }
    tok = strtok(NULL, " \n\t|");
  }
  return ret;
  free(ret);
}
