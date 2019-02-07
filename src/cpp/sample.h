#include <nan.h>
#include <iostream>

// #include <windows.h>
// #include <windowsx.h>
// #include <ole2.h>
// #include <olectl.h>
// #include <cmath>
// #include <time.h>
// #include <locale>
// #include <gdiplus.h>

// #pragma comment (lib, "Gdiplus.lib")

struct ScreenCapture {
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(TakeScreenshot);
  static NAN_METHOD(Testing);
};

// Async worker for: TakeScreenshot
class MyAsyncWorker: public Nan::AsyncWorker{
  public:

  // Constructor
  MyAsyncWorker(Nan::Callback *callback);
  // MyAsyncWorker(std::string directory, Nan::Callback *callback);

  // Mandatory special functions
  void Execute();          // Automatically called right after the Initializer
  void HandleOKCallback(); // Called once the program is completed
};

// Async worker for: Testing
class JustSomeFunctionNameThing: public Nan::AsyncWorker{
  public:

  // Constructor
  JustSomeFunctionNameThing(std::string &s1, std::string &s2, int i1, int i2, Nan::Callback *callback);

  // Mandatory special functions
  void Execute();          // Automatically called right after the Initializer
  void HandleOKCallback(); // Called once the program is completed

  // Other data
  std::string firstName;
  std::string lastName;
  std::string fullName;
  int myInt1;
  int myInt2;
  int intTotal;
};

// Self-register the module
NAN_MODULE_INIT(InitModule){
  ScreenCapture::Init(target);
}

NODE_MODULE(myModule, InitModule);
