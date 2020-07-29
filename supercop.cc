#include <node_api.h>
#include "vendor/ed25519/src/ed25519.h"
#include <napi-macros.h>

NAPI_METHOD(node_supercop_sign) {
  NAPI_ARGV(4)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, message, 0)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, public_key, 1)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, secret_key, 2)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, signature, 3)

  if (public_key_len != 32) {
    napi_throw_error(env, "EINVAL", "public key must be 32 bytes");
    return NULL;
  }

  if (secret_key_len != 64) {
    napi_throw_error(env, "EINVAL", "secret key must be 64 bytes");
    return NULL;
  }

  ed25519_sign(signature, message, message_len, public_key, secret_key);
  return NULL;
}

NAPI_METHOD(node_supercop_verify) {
  NAPI_ARGV(3)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, signature, 0)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, message, 1)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, public_key, 2)

  if (signature_len != 64) {
    napi_throw_error(env, "EINVAL", "signature key must be 64 bytes");
    return NULL;
  }

  if (public_key_len != 32) {
    napi_throw_error(env, "EINVAL", "public key must be 32 bytes");
    return NULL;
  }

  bool result = ed25519_verify(signature, message, message_len, public_key);
  int res = result ? 1 : 0;
  NAPI_RETURN_UINT32(res)
}

NAPI_METHOD(node_supercop_create_seed) {
  NAPI_ARGV(1)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, seed, 0)

  ed25519_create_seed(seed);
  return NULL;
}

NAPI_METHOD(node_supercop_create_key_pair) {
  NAPI_ARGV(3)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, seed, 0)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, public_key, 1)
  NAPI_ARGV_BUFFER_CAST(unsigned char *, secret_key, 2)

  if (seed_len != 32) {
    napi_throw_error(env, "EINVAL", "seed must be 32 bytes");
    return NULL;
  }

  ed25519_create_keypair(public_key, secret_key, seed);
  return NULL;
}

NAPI_INIT() {
  NAPI_EXPORT_FUNCTION(node_supercop_sign)
  NAPI_EXPORT_FUNCTION(node_supercop_verify)
  NAPI_EXPORT_FUNCTION(node_supercop_create_seed)
  NAPI_EXPORT_FUNCTION(node_supercop_create_key_pair)
}
