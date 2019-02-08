#include "helper.h"
#include <iostream>

struct ScreenCapture {
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(TakeScreenshot);
  static NAN_METHOD(Testing);
};

// Async worker for: TakeScreenshot
class MyAsyncWorker: public Nan::AsyncWorker{
  public:

  // Mandatory special functions
  // 1. Constructor
  // 2. Execute (Automatically called right after the Constructor)
  // 3. HandleOKCallback (Special callback function)

  MyAsyncWorker(Nan::Callback *callback):
    Nan::AsyncWorker(callback)
    {}

  void Execute();

  void HandleOKCallback(){
    std::vector<v8::Local<v8::Value>> arguments = {
      JavaScriptInt(12345)
    };

    ExecuteCallback(callback, arguments);
  }
};

// Async worker for: Testing
class JustSomeFunctionNameThing: public Nan::AsyncWorker{
  public:

  // Mandatory special functions
  // 1. Constructor
  // 2. Execute (Automatically called right after the Constructor)
  // 3. HandleOKCallback (Special callback function)

  JustSomeFunctionNameThing(std::string &s1, std::string &s2, int i1, int i2, Nan::Callback *callback):
    Nan::AsyncWorker(callback),
    firstName(s1),
    lastName(s2),
    myInt1(i1),
    myInt2(i2)
    {}

  void Execute();

  void HandleOKCallback(){
    std::vector<v8::Local<v8::Value>> arguments = {
      JavaScriptString(fullName),
      JavaScriptInt(intTotal)
    };

    ExecuteCallback(callback, arguments);
  }

  private:

  std::string firstName;
  std::string lastName;
  std::string fullName;
  int myInt1;
  int myInt2;
  int intTotal;
};

// vvvvvvvvvv ?????????????????????????????? vvvvvvvvvv

// Self-register the module
NAN_MODULE_INIT(InitModule){
  ScreenCapture::Init(target);
}

NODE_MODULE(myModule, InitModule);

// All functions that you can call from Node.js
NAN_MODULE_INIT(ScreenCapture::Init){
  Nan::SetMethod(target, "Testing"       , Testing);
  Nan::SetMethod(target, "TakeScreenshot", TakeScreenshot);
}
