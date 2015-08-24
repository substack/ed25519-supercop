#include <nan.h>
#include <node_buffer.h>
#include "vendor/ed25519/src/ed25519.h"
#include "vendor/ed25519/src/ge.h"
#include "vendor/ed25519/src/sc.h"

using namespace node;
using namespace v8;
using namespace Nan;

NAN_METHOD(Sign) {
  Local<Object> messageBuffer = info[0]->ToObject();
  unsigned char *message = (unsigned char*) Buffer::Data(messageBuffer);
  size_t messageLen = Buffer::Length(messageBuffer);
 
  Local<Object> publicKeyBuffer = info[1]->ToObject();
  if (Buffer::Length(publicKeyBuffer) != 32) {
    return ThrowError("public key must be 32 bytes");
  }
  unsigned char *publicKey = (unsigned char*) Buffer::Data(info[1]);
 
  Local<Object> secretKeyBuffer = info[2]->ToObject();
  if (Buffer::Length(secretKeyBuffer) != 64) {
    return ThrowError("secret key must be 64 bytes");
  }
  unsigned char *secretKey = (unsigned char*) Buffer::Data(info[2]);

  unsigned char signature[64];
  ed25519_sign(signature, message, messageLen, publicKey, secretKey);
 
  Local<Object> signatureBuffer = Buffer::New((char *) signature, 64);
  info.GetReturnValue().Set(signatureBuffer);
}

NAN_METHOD(Verify) {
  Local<Object> signatureBuffer = info[0]->ToObject();
  unsigned char *signature = (unsigned char*) Buffer::Data(signatureBuffer);
  if (Buffer::Length(signatureBuffer) != 64) {
    return ThrowError("signature must be 64 bytes");
  }

  Local<Object> messageBuffer = info[1]->ToObject();
  unsigned char *message = (unsigned char*) Buffer::Data(messageBuffer);
  size_t messageLen = Buffer::Length(messageBuffer);

  Local<Object> publicKeyBuffer = info[2]->ToObject();
  if (Buffer::Length(publicKeyBuffer) != 32) {
    return ThrowError("public key must be 32 bytes");
  }
  unsigned char *publicKey = (unsigned char*) Buffer::Data(info[1]);

  bool result = ed25519_verify(signature, message, messageLen, publicKey);
  info.GetReturnValue().Set(result);
}

NAN_MODULE_INIT(InitAll) {
  Set(target, New<String>("sign").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(Sign)).ToLocalChecked());
  Set(target, New<String>("verify").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(Verify)).ToLocalChecked());
}
NODE_MODULE(supercop, InitAll)
