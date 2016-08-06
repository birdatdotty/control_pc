#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "config.h"
#include "configure_context.h"
#include "create_context.h"
#include "verify_callback.h"
#include "cmd.h"
#include "ssl_read_cb.h"
#include "ssl_event_cb.h"
#include "accept_conn_cb.h"

#include <openssl/ssl.h>
#include <event2/event.h>
#include <event2/util.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_ssl.h>


void init_openssl()
{ 
    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
}

static void accept_error_cb(struct evconnlistener *listener, void *ctx)
{
    int err = EVUTIL_SOCKET_ERROR();
    fprintf(stderr, "Got an error %d on listener: %s\n", 
            err, evutil_socket_error_to_string(err));
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
  int sock;
  SSL_CTX *ctx;

  init_openssl();
  ctx = create_context();
  OpenSSL_add_all_ciphers();
  configure_context(ctx);

  SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT, verify_callback);
  SSL_CTX_load_verify_locations (ctx, CA_CERT, NULL);

  struct event_base *base = event_base_new();
  if (!base)
  {
    fprintf(stderr, "Could not open evnet base\n");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in servaddr;
  struct sockaddr *sa = (struct sockaddr *)&servaddr;
  int socklen = sizeof(servaddr);
  if (evutil_parse_sockaddr_port("0.0.0.0:4433", sa, &socklen) == -1)
  {
    fprintf(stderr, "Could not parse address\n");
    exit(EXIT_FAILURE);
  }

  struct evconnlistener *listener = evconnlistener_new_bind(base, accept_conn_cb, ctx,
    LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1, sa, sizeof(servaddr));

  if (NULL == listener)
  {
    fprintf(stderr, "Could not create listener\n");
    exit(EXIT_FAILURE);
  }

  evconnlistener_set_error_cb(listener, accept_error_cb);
  event_base_dispatch(base);
}

