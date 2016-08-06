#include <openssl/ssl.h>
#include <event2/event.h>
#include <event2/bufferevent_ssl.h>
#include <event2/listener.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "cmd.h"
#include "ssl_read_cb.h"
#include "ssl_event_cb.h"


void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd,
        struct sockaddr *address, int socklen, void *ctx)
{
    exec_cmd *session_cmd = init_cmd (calloc (1, 1024*1024));

    struct event_base *base = evconnlistener_get_base(listener);
    SSL *ssl = SSL_new((SSL_CTX *)ctx);
    if (NULL == ssl)
    {
        fprintf(stderr, "Could not create new SSL\n");
        exit(EXIT_FAILURE);
    }

    struct bufferevent *bev = bufferevent_openssl_socket_new(base, fd, ssl,
            BUFFEREVENT_SSL_ACCEPTING, BEV_OPT_CLOSE_ON_FREE);
    if (!bev)
    {
        fprintf(stderr, "Could not create new ssl bufferevent\n");
        exit(EXIT_FAILURE);
    }

    bufferevent_setcb(bev, ssl_read_cb, NULL, ssl_event_cb, (void*)session_cmd);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
}

