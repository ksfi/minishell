#ifndef __PIPE_H__
#define __PIPE_H__

#include "pipeline.c"

int test(char *cmd);
int testRedirect(char *cmd);
const void  *execute(char *cmd);
void pipeline(char *cmd);

#endif
