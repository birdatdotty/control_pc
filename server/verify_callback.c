#include <openssl/ssl.h>
#include <openssl/err.h>

#include "config.h"


int verify_callback(int preverify_ok, X509_STORE_CTX *ctx)
{
  return 1;
}
