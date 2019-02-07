#include <nan.h>
#include <cmath>
#include <windows.h>
#include <windowsx.h>
#include <iostream>
#include <ole2.h>
#include <olectl.h>
#include <gdiplus.h>
#include <time.h>
#include <locale> // Convert string to wstring

#pragma comment (lib, "Gdiplus.lib")

struct ScreenCapture {
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(TakeScreenshot);
};

class MyAsyncWorker: public Nan::AsyncWorker{
  public:

  // Constructor
  MyAsyncWorker(Nan::Callback *callback);
  // MyAsyncWorker(std::string directory, Nan::Callback *callback);

  // Mandatory special functions
  void Execute();          // Automatically called right after the Initializer
  void HandleOKCallback(); // Called once the program is completed
};

// Self-register the module
NAN_MODULE_INIT(InitModule){
  ScreenCapture::Init(target);
}

NODE_MODULE(myModule, InitModule);
