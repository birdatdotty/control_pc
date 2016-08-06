#include <event2/event.h>
#include <event2/util.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_ssl.h>

#include "cmd.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

void ssl_event_cb(struct bufferevent *bev, short events, void *arg)
{

exec_cmd *session_cmd = (exec_cmd*) arg;
    if (events & BEV_EVENT_CONNECTED)
    {
        printf("Client connected!\n");
    }
    else if (events & BEV_EVENT_EOF)
    {
        printf("Client disconnected!\n");
        bufferevent_free(bev);
        free(session_cmd->cmd);
        free_cmd (session_cmd);
    }
    else
    {
        int err = EVUTIL_SOCKET_ERROR();
        fprintf(stderr, "Got an error %d on ssl socket: %s\n",
            err, evutil_socket_error_to_string(err));
        bufferevent_free(bev);
        free(session_cmd->cmd);
        free_cmd (session_cmd);
    }
}

