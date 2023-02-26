#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "header.h"
#include "tokenizer.h"

int test(char *cmd) {
  size_t i = 0;
  while (cmd[i] != '\n') {
    if (cmd[i] == '|') return OUI;
    i++;
  }
  return NON;
}

int testRedirect(char *cmd) {
  size_t i = 0;
  while (cmd[i] != '\n') {
    if (cmd[i] == '>') return OUI;
    i++;
  }
  return NON;
}

void cut(char str[], char ret[], size_t len) {
  for (size_t i = 0; i < len - 1; i++)
    ret[i] = str[i];
}

const void *execute(char cmd[]) {
  Token *tok = tokenizer(cmd);
  size_t len = strlen(cmd);
  cmd[strcspn(cmd, "\n")] = 0;
  if (tok->len > 1) {
    char **optionsVal = options(tok);
    if (execlp(tok->val, tok->val, *optionsVal, NULL) < 0) perror("exec");
  }
  else 
    if (execlp(cmd, cmd, NULL) < 0) perror("exec");
}

void pipeline(char *cmd) {
  Token *pipeTok = pipelineTokenizer(cmd);
  size_t numPipes = pipeTok->len;
  int fds[2 * numPipes], j = 0, status;
  pid_t pid;

  for (size_t i = 0; i < numPipes; i++)
    if (pipe(fds + 2 * i) < 0) perror("error pipe");

  while (pipeTok != NULL) {
    pid = fork();
    if (pid == 0) {
      if (pipeTok->next) {
        if (dup2(fds[j + 1], 1) < 0) perror("dup2");
      }
      if (j != 0) {
        if (dup2(fds[j - 2], 0) < 0) perror("dup2");
      }
      for (size_t i = 0; i < 2 * numPipes; i++)
        close(fds[i]);
      if (execlp(pipeTok->val, pipeTok->val) < 0) {
        perror("exec");
        printf("%s", pipeTok->val);
      }
    }
    else if (pid < 0) perror("error pid");
    pipeTok = pipeTok->next;
    j = j + 2;
  }
  for (size_t i = 0; i < 2 * numPipes; i++)
    close(fds[i]);
  for (size_t i = 0; i < 2 * numPipes; i++)
    wait(&status);
}
