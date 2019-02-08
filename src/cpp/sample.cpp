#include "sample.h"

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

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// All functions that you can call from Node.js
NAN_MODULE_INIT(ScreenCapture::Init){
  Nan::SetMethod(target, "Testing"       , Testing);
  Nan::SetMethod(target, "TakeScreenshot", TakeScreenshot);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

NAN_METHOD(ScreenCapture::Testing){
  std::string    s1 = ConvertToString(info[0]);
  std::string    s2 = ConvertToString(info[1]);
  int            i1 = ConvertToInt(info[2]);
  int            i2 = ConvertToInt(info[3]);
  Nan::Callback *cb = ConvertToCallback(info[4]);

  Nan::AsyncQueueWorker(new JustSomeFunctionNameThing(
    s1,
    s2,
    i1,
    i2,
    cb
  ));
}

///////////////////////////////////////////////////////////////////////////////////////////////////

JustSomeFunctionNameThing::JustSomeFunctionNameThing(std::string &s1, std::string &s2, int i1, int i2, Nan::Callback *callback) : Nan::AsyncWorker(callback) {
  firstName = s1;
  lastName  = s2;
  myInt1    = i1;
  myInt2    = i2;
}

void JustSomeFunctionNameThing::Execute(){
  fullName = firstName + " " + lastName;
  intTotal = myInt1 + myInt2;

  std::cout << fullName << "\n";
  std::cout << intTotal << "\n";
}

void JustSomeFunctionNameThing::HandleOKCallback(){
  std::vector< v8::Local<v8::Value> > arguments = {
    JavaScriptString(fullName),
    JavaScriptInt(intTotal)
  };

  ExecuteCallback(callback, arguments);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

NAN_METHOD(ScreenCapture::TakeScreenshot){
  Nan::AsyncQueueWorker(new MyAsyncWorker(
    new Nan::Callback(info[1].As<v8::Function>())
  ));
}

///////////////////////////////////////////////////////////////////////////////////////////////////

MyAsyncWorker::MyAsyncWorker(Nan::Callback *callback) : Nan::AsyncWorker(callback){
  std::cout << "=============== INIT ===============\n";
}

void MyAsyncWorker::Execute(){
  std::cout << "=============== MAIN ===============\n";
}

void MyAsyncWorker::HandleOKCallback(){
  std::cout << "================ OK ================\n";

  v8::Local<v8::Value> arguments[] = {
    v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "Does this work")
  };

  size_t argumentCount = sizeof(arguments)/sizeof(*arguments);

  // A dummy AsyncResource object needs to be created as a placeholder
  Nan::AsyncResource *dummy = new Nan::AsyncResource(Nan::New("").ToLocalChecked());

  callback->Call(argumentCount, arguments, dummy);
}
