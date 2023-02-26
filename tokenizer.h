#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "tokenizer.c"

Token *tokenizer(char *cmd);
Token *pipelineTokenizer(char *cmd);
char **options(Token *tok);

#endif
