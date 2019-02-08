var cppModule = require("../build/Release/screen-capture.node"); // C++ module for screen capturing

cppModule.Testing("John", "Doe", 123, 456, function(result, second){
  console.log("WE ARE BACK IN NODE.JS");
  console.log(result);
  console.log(second);

  cppModule.TakeScreenshot(function(result){
    console.log("TakeScreenshot:", result);
  });
});

