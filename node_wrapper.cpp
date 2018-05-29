// Import main.c here, and wrap it in functions for Node add-ons.
#include <node.h>
#include "src/main.c"

namespace liblhvm {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

// NOTE: not actually working yet.
void BoingWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "boing boing"));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "boing", BoingWrapper);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

}