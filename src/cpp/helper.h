#include <nan.h>

// JS string => C++ string
std::string ConvertToString(v8::Local<v8::Value> nodeString){
  return *Nan::Utf8String(nodeString->ToString());
}

// JS int => C++ int
int ConvertToInt(v8::Local<v8::Value> nodeInt){
  return nodeInt->Int32Value(Nan::GetCurrentContext()).FromJust();
}

// Helper function to convert to a callback
Nan::Callback* ConvertToCallback(v8::Local<v8::Value> nodeCallback){
  return new Nan::Callback(nodeCallback.As<v8::Function>());
}

// C++ string => JS string
v8::Local<v8::Value> JavaScriptString(std::string str){
  return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), str.c_str());
}

// C++ int => JS int
v8::Local<v8::Value> JavaScriptInt(int i){
  return v8::Number::New(v8::Isolate::GetCurrent(), i);
}

void ExecuteCallback(Nan::Callback *callback, std::vector< v8::Local<v8::Value> > &vecArguments){
  // Dynamically allocate an array of Local<Value>
  size_t argumentCount = vecArguments.size();
  v8::Local<v8::Value> *arguments = new v8::Local<v8::Value> [argumentCount];

  // Copy the arguments over from the vector into our new dynamically allocated array
  for(size_t i = 0; i < argumentCount; i++)
    arguments[i] = vecArguments[i];

  // The last argument is a mandatory "dummy" AsyncResource object
  callback->Call(argumentCount,
                 arguments,
                 new Nan::AsyncResource(Nan::New("").ToLocalChecked()));
}
