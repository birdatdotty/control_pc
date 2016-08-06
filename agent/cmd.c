#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"

exec_cmd* init_cmd (char* cmd_str)
{
  exec_cmd *tmp = (exec_cmd*) malloc (sizeof(exec_cmd));
  tmp->pos = 0;
  tmp->cmd = cmd_str;
  tmp->status = 0;
  tmp->end = '\0';

  return tmp;
}

void reset_cmd (exec_cmd* tmp)
{
  tmp->pos = 0;
  tmp->status = 0;
  tmp->end = '\0';
  tmp->cmd[0] = '\0';
}

void push_cmd (exec_cmd* tmp, char* buf)
{
  int len = strlen(buf);
  strncat ( (tmp->cmd) + (tmp->pos), buf, len);
  tmp->pos = tmp->pos + strlen(buf);

  int str_len = strlen (buf);
  if (buf[len-1] == 10)
    {
    if (buf[len-2] != 92)
      {
      tmp->end = 1;
      }
    }
  else
    tmp->pos -= 2;

}

void cmd(exec_cmd *tmp)
{
/** command:
 * CMD: run cmd                              // добавить проверку следующей команды
 * status get status
 */
printf ("[tmp->cmd = %s ]\n\n", tmp->cmd);
  static char *first_space;
  char *cmd = tmp->cmd;
  static int str_len;
  str_len = strlen (cmd);
  static int cmd_len;
  char *cmd_parm;
  static char type_cmd[20];

  first_space = strchr(cmd, ' ');
  cmd_len = first_space - cmd;
  if (cmd_len < 1)
    return;
  if (cmd_len < 20)
  {

printf ("[%s]\n\n", cmd);
    cmd_parm = cmd+cmd_len+1;
    strncpy (type_cmd, cmd, cmd_len);
    if ( (strcmp (type_cmd, "CMD")) == 0)
    {
      tmp->status = system(cmd_parm);
      tmp->pos = 0;
      memset(tmp->cmd, '\0', 1000);
    }
    else
    if (tmp->end == 0)
    {
     tmp->status = system(cmd_parm);
     tmp->pos = 0;
     memset(tmp->cmd, '\0', 1000);
    }
  }

}

void free_cmd (exec_cmd* tmp)
{
//  free (tmp->cmd);
  free (tmp);
}
