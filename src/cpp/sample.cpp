#include "sample.h"

NAN_MODULE_INIT(ScreenCapture::Init){
  Nan::SetMethod(target, "TakeScreenshot", TakeScreenshot);
}

NAN_METHOD(ScreenCapture::TakeScreenshot){
  Nan::AsyncQueueWorker(new MyAsyncWorker(
    new Nan::Callback(info[0].As<v8::Function>())
  ));

  /*
  Nan::AsyncQueueWorker(new MyAsyncWorker(
    // All parameters (except the final one) are variables passed from Node.JS
    std::string(*Nan::Utf8String(info[0]->ToString())),

    // The final parameter in MyAsyncWorker will always be the callback function
    new Nan::Callback(info[1].As<v8::Function>())
  ));
  */
}

MyAsyncWorker::MyAsyncWorker(Nan::Callback *callback) : Nan::AsyncWorker(callback){
  // Do whatever you want here
  std::cout << "=== C++ ==================================\n";
}

void MyAsyncWorker::Execute(){
  std::cout << "MyAsyncWorker::Execute()\n";
}

void MyAsyncWorker::HandleOKCallback(){
  v8::Local<v8::Value> arguments[] = {
    // fileNamePngV8
    v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "Does this work")
  };

  size_t argumentCount = sizeof(arguments)/sizeof(*arguments);

  // A dummy AsyncResource object needs to be created as a placeholder
  Nan::AsyncResource *dummy = new Nan::AsyncResource(Nan::New("").ToLocalChecked());

  callback->Call(argumentCount, arguments, dummy);
}
