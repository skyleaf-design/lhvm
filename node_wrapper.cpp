// Import main.c here, and wrap it in functions for Node add-ons.
#include <node.h>
#include "src/main.c"

namespace liblhvm {

// buffer must be string lenght + 2 for null character and newline.
char buffer[10];

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

void BoingWrapper(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  boing(buffer, 5);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, buffer));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "boing", BoingWrapper);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

}