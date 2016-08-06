#include <string.h>

#include <event2/event.h>
#include <event2/util.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_ssl.h>

#include "cmd.h"

void ssl_read_cb(struct bufferevent *bev, void *arg)
{

    char recvbuf[1024] = {'\0'};
    char answar[10] = {'\0'};
    exec_cmd *session_cmd = (exec_cmd*) arg;

    printf ("session_cmd->end = %i\n", session_cmd->end);
    if (bufferevent_read(bev, recvbuf , 1024) > 0)
    {
          push_cmd (session_cmd, recvbuf);
          sprintf (answar, "%i", session_cmd->status);
          bufferevent_write (bev, answar, strlen (answar));
        if (session_cmd->end == 1)
          {
            session_cmd->end = 0;
            cmd (session_cmd);
          }

    }
}
