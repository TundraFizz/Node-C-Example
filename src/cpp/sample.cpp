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
  Nan::Callback *cb = ConvertToCallback(info[0]);

  Nan::AsyncQueueWorker(new MyAsyncWorker(
    cb
  ));
}

void MyAsyncWorker::Execute(){
  std::cout << "MyAsyncWorker::Execute()\n";
}
