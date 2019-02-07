#include "sample.h"

// Helper function to convert to a string
std::string ConvertToString(v8::Local<v8::Value> nodeString){
  return *Nan::Utf8String(nodeString->ToString());
}

// Helper function to convert to an integer
int ConvertToInt(v8::Local<v8::Value> nodeInt){
  return nodeInt->Int32Value(Nan::GetCurrentContext()).FromJust();
}

// Helper function to convert to a callback
int ConvertToCallback(v8::Local<v8::Value> nodeCallback){
  return new Nan::Callback(nodeCallback.As<v8::Function>());
}

// All functions that you can call from Node.js
NAN_MODULE_INIT(ScreenCapture::Init){
  Nan::SetMethod(target, "Testing"       , Testing);
  Nan::SetMethod(target, "TakeScreenshot", TakeScreenshot);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

NAN_METHOD(ScreenCapture::Testing){
  // std::string    s1 = *Nan::Utf8String(info[0]->ToString());
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
  std::cout << "=============== INIT ===============\n";
  firstName = s1;
  lastName  = s2;
  myInt1    = i1;
  myInt2    = i2;
}

void JustSomeFunctionNameThing::Execute(){
  std::cout << "=============== MAIN ===============\n";
  std::cout << firstName << "\n";
  std::cout << lastName  << "\n";
  std::cout << myInt1    << "\n";
  std::cout << myInt2    << "\n";

  fullName = firstName + " " + lastName;
  intTotal = myInt1 + myInt2;

  std::cout << fullName << "\n";
  std::cout << intTotal << "\n";
}

void JustSomeFunctionNameThing::HandleOKCallback(){
  std::cout << "================ OK ================\n";

  v8::Local<v8::Value> arguments[] = {
    v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), fullName.c_str()),
    v8::Number::New        (v8::Isolate::GetCurrent(), intTotal)
  };

  size_t argumentCount = sizeof(arguments)/sizeof(*arguments);

  // A dummy AsyncResource object needs to be created as a placeholder
  Nan::AsyncResource *dummy = new Nan::AsyncResource(Nan::New("").ToLocalChecked());

  callback->Call(argumentCount, arguments, dummy);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

NAN_METHOD(ScreenCapture::TakeScreenshot){
  // Nan::AsyncQueueWorker(new MyAsyncWorker(
  //   new Nan::Callback(info[0].As<v8::Function>())
  // ));

  Nan::AsyncQueueWorker(new MyAsyncWorker(
    // All parameters (except the final one) are variables passed from Node.JS
    // std::string(*Nan::Utf8String(info[0]->ToString())),

    // The final parameter in MyAsyncWorker will always be the callback function
    new Nan::Callback(info[1].As<v8::Function>())
  ));
}

///////////////////////////////////////////////////////////////////////////////////////////////////

MyAsyncWorker::MyAsyncWorker(Nan::Callback *callback) : Nan::AsyncWorker(callback){
  // Do whatever you want here
  std::cout << "=== C++ ==================================\n";
}

void MyAsyncWorker::Execute(){
  std::cout << "MyAsyncWorker::Execute()\n";
}

void MyAsyncWorker::HandleOKCallback(){
  v8::Local<v8::Value> arguments[] = {
    v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "Does this work")
  };

  size_t argumentCount = sizeof(arguments)/sizeof(*arguments);

  // A dummy AsyncResource object needs to be created as a placeholder
  Nan::AsyncResource *dummy = new Nan::AsyncResource(Nan::New("").ToLocalChecked());

  callback->Call(argumentCount, arguments, dummy);
}
