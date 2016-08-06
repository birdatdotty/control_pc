#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "config.h"

void configure_context(SSL_CTX *ctx)
{
//    SSL_CTX_set_ecdh_auto(ctx, 1);
printf ("SSL_CTX_use_certificate_file (%s)\n", CERT_CERT);
    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, CERT_CERT, SSL_FILETYPE_PEM) < 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
printf ("SSL_CTX_use_PrivateKey_file (%s)\n", CERT_KEY);
    if (SSL_CTX_use_PrivateKey_file(ctx, CERT_KEY, SSL_FILETYPE_PEM) < 0 ) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}
