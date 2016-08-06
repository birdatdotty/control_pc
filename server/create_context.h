#ifndef _CREATE_CONTEXT_
#define _CREATE_CONTEXT_
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

SSL_CTX *create_context();
#endif
