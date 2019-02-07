
var screenCapture = require("../build/Release/screen-capture.node"); // C++ module for screen capturing

screenCapture.TakeScreenshot(function(result){
  console.log("========== COMPLETE ==========");
});

function TakeScreenshot(){
  win.hide();
  // win.minimize();

  // screenCapture.TakeScreenshot("My Custom String", function(result){
  screenCapture.TakeScreenshot(function(result){

    console.log("=== Electron =============================");
    console.log(result);

    // If the user clicked on the "Screenshot" button, then we'll display the window again
    if(clickedOnButton)
      win.show();
    else
      win.hide();

    var formData = {
      "key": "This is the user's secret",
      "file": fs.createReadStream(result)
    };

    request.post({url:"https://fizz.gg/send-screenshot", formData: formData, json: true}, function(err, res, body){

      if(err){
        if(err["code"] == "ENOTFOUND"){
          console.log("Client was unable to communicate with the server");
        }else{
          console.log("An unknown error occurred when trying to communicate with the server");
          console.log("Error code:", err["code"]);
        }
        return;
      }

      if(res["statusCode"] != 200){
        console.log("Invalid response from the server");
        console.log("Error code:", res["statusCode"]);
        return;
      }

      lastUploadedScreenshotUrl = body["url"];
      clipboard.write({"text": body["url"]});

      tray.displayBalloon({
        "title"  : "TESTING",
        "icon"   : path.join(__dirname, "img/icon64x64.png"),
        "title"  : "Uploaded image",
        "content": lastUploadedScreenshotUrl
      });

      SendMessage("PlaySfxNotification");
    });
  });
}

console.log("Hello world!");
