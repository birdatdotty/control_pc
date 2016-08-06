#ifndef _CMD_H_
#define _CMD_H_
typedef struct {
  int pos;
  char *cmd;
  char end;
  int status;
} exec_cmd;

exec_cmd* init_cmd (char* buf);
void push_cmd (exec_cmd *tmp, char* str);
void cmd (exec_cmd *tmp);
void free_cmd (exec_cmd* tmp);
#endif
