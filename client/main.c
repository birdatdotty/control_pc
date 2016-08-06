#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#include "config.h"
#include "configure_context.h"
#include "create_context.h"
#include "verify_callback.h"
#include "create_socket.h"


void init_openssl()
{ 
    SSL_load_error_strings();	
    OpenSSL_add_ssl_algorithms();
}

void cleanup_openssl()
{
    EVP_cleanup();
}


int main(int argc, char **argv)
{
char* cmd_str = (char*) malloc (4096);
strcat (cmd_str, "CMD ");
for (int iter=1; iter<argc; iter++)
{
strcat (cmd_str, argv[iter]);
strcat (cmd_str, " ");
}
strcat (cmd_str, "\n");


OpenSSL_add_all_algorithms();
SSL_library_init();
    int sock;
    SSL_CTX *ctx;

    init_openssl();
    ctx = create_context();
    OpenSSL_add_all_ciphers();
    configure_context(ctx);
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    SSL_CTX_load_verify_locations (ctx, CA_CERT, NULL);
    SSL *ssl = SSL_new (ctx);

    if (ssl == NULL)
      puts ("ssl == NULL");

    sock = create_socket(PORT);
    printf("sock = %i\n", sock);

    struct sockaddr_in addr;
    int len = sizeof(addr);
    const char reply[] = "!!!test\n";
    puts ("---");
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    int verify_test = SSL_get_verify_result(ssl);
    printf ("verify_test = %i\n", verify_test);
    int ssl_connect = SSL_connect(ssl);
    printf ("ssl_connect = %i\n", ssl_connect);
SSL_write (ssl, cmd_str, strlen(cmd_str));
    puts ("---");
//    char *buf = calloc (1, 1024);
char *status = (char*) calloc (1,8);
sleep(1);
SSL_read (ssl, status, 8);
printf ("status = [%s]\n", status);
//SSL_read (ssl, status, 6);
//printf ("status = %s\n", status);

//sleep (2);
//  SSL_read (ssl, buf, 1024);
//  puts (buf);
//sleep (2);
//    int ssl_accept = SSL_accept (ssl);
//    if (SSL_accept (ssl) <= 0)
//printf ("ssl_accept = %i\n\n", ssl_accept);
//      puts ("SSL_accept (ssl) <= 0");
//    else
//      SSL_write (ssl, "HELLO\n", 5);
    //sleep (1);
//    SSL_read (ssl, buf, 1024);
//    puts (buf);
    SSL_CTX_free(ctx);
    cleanup_openssl();
    close (sock);
}

