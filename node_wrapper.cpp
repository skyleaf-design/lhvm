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

void ReturnString(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  boing(buffer, 5);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, buffer));
}

void Echo(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  auto x = args.Data();
  if (x->IsBoolean()) {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "is_boolean"));
    return;
  }
  if (x->IsString()) {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "is_string"));
    return;
  }
  if (x->IsObject()) {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "is_object"));
    return;
  }
  if (x->IsUndefined()) {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "is_undefined"));
    return;
  }
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "is_unknown"));
}

void ReturnArrayOfStrings(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  boing(buffer, 5);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, buffer));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "string", ReturnString);
  NODE_SET_METHOD(exports, "echo", Echo);
  NODE_SET_METHOD(exports, "array_of_strings", ReturnArrayOfStrings);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)

}