#include <stdbool.h>

#include "header.h"
#include "pipeline.h"

int main(int argc, char *argv[]) {
  char line[CMD_SIZE];

  while (1) {
    printf("MINI SHELL $ ");
    if(fgets(line, sizeof line, stdin) != NULL) {
      if (strcmp(line, "\n") == 0) continue;
      if (strcmp(line, "quit\n") == 0) exit(0);
      if (test(line) == NON) {
        pid_t pid;
        pid = fork();
        if (pid == 0) execute(line);
      }
      if (test(line) == OUI) {
        pid_t pid;
        pid = fork();
        if (pid == 0) pipeline(line);
      }
    }
  }
}
