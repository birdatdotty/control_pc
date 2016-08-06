#ifndef _ACCEPT_CONN_CB_H_
#define _ACCEPT_CONN_CB_H_

#include <event2/event.h>
#include <event2/util.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_ssl.h>

void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd,
        struct sockaddr *address, int socklen, void *ctx);

#endif
