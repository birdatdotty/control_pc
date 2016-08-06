#ifndef _SSL_READ_CB_H_
#define _SSL_READ_CB_H_

#include <event2/bufferevent.h>

void ssl_read_cb(struct bufferevent *, void *);

#endif
