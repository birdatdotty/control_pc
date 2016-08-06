#ifndef _UPDATE_PROG_H_
#define _UPDATE_PROG_H_

#include <openssl/ssl.h>
#include <event2/event.h>
#include <event2/util.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_ssl.h>

int update_prog(char *cmd_parm, struct bufferevent *bev);

#endif
