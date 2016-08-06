#ifndef _VERIFY_CALLBACK_H_
#define _VERIFY_CALLBACK_H_
#include <openssl/ssl.h>

int verify_callback(int preverify_ok, X509_STORE_CTX *ctx);
#endif
