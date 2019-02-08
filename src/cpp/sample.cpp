#include "sample.h"

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

void JustSomeFunctionNameThing::Execute(){
  fullName = firstName + " " + lastName;
  intTotal = myInt1 + myInt2;

  std::cout << fullName << "\n";
  std::cout << intTotal << "\n";
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
