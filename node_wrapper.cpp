// Import main.c here, and wrap it in functions for Node add-ons.
#include <node.h>
#include "src/main.c"
#include <string>
#include <iostream>

namespace liblhvm {

// buffer must be string lenght + 2 for null character and newline.
char buffer[10];



using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Array;
using v8::Exception;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void ReturnString(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  boing(buffer, 5);
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, buffer));
}

void GetType(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  
  if(args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Error: expected at least one argument!")));
    return;
  }

  if (args[0]->IsBoolean()) {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "is_boolean"));
    return;
  }
  if (args[0]->IsString()) {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "is_string"));
    return;
  }
  if (args[0]->IsObject()) {
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "is_object"));
    return;
  }
  if (args[0]->IsUndefined()) {
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

void ConstructLHVM(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if(args.Length() < 1 || !args[0]->IsObject()) {
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Error: One object expected")));
    return;
  }

  Local<Context> context = isolate->GetCurrentContext();
  Local<Object> obj = args[0]->ToObject(context).ToLocalChecked();
  Local<Array> props = obj->GetOwnPropertyNames(context).ToLocalChecked();

  // Right now, just log out the object that was provided.
  for(int i = 0, l = props->Length(); i < l; i++) {
    Local<Value> localKey = props->Get(i);
    Local<Value> localVal = obj->Get(context, localKey).ToLocalChecked();
    std::string key = *String::Utf8Value(localKey);
    std::string val = *String::Utf8Value(localVal);
    std::cout << key << ":" << val << std::endl;
  }
}

void CreateFunction(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, ConstructLHVM);
  Local<Function> fn = tpl->GetFunction();

  fn->SetName(String::NewFromUtf8(isolate, "LHVM"));
  args.GetReturnValue().Set(fn);
}

void init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(exports, "get_type", GetType);
  NODE_SET_METHOD(exports, "string", ReturnString);
  NODE_SET_METHOD(exports, "hello", Method);
  NODE_SET_METHOD(exports, "array_of_strings", ReturnArrayOfStrings);

  // Note: I'm not sure how to export a function to JS, while ALSO exposing
  // C functions as methods on that function object.
  // NODE_SET_METHOD(module, "exports", CreateFunction);
}

NODE_MODULE(lhvm, init)

}