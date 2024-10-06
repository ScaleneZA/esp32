
static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<html>
  <head>
    <title>ESP32-CAM Robot</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Arial; text-align: center; margin:0px auto; padding-top: 30px;}
      table { margin-left: auto; margin-right: auto; }
      td { padding: 8 px; }
      .button {
        background-color: #2f4468;
        border: none;
        color: white;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 18px;
        margin: 6px 3px;
        cursor: pointer;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: rgba(0,0,0,0);
      }
      img {  width: auto ;
        max-width: 100% ;
        height: auto ; 
      }
    </style>
  </head>
  <body>
    <img src="" id="photo" >
    <table>
      <tr><td colspan="3" align="center"><button class="button" onmouseup="toggleCheckbox('up-stop');" onmousedown="toggleCheckbox('up');" ontouchend="toggleCheckbox('up-stop');" ontouchstart="toggleCheckbox('up');">⬆️</button></td></tr>  
      <tr>
        <td align="center"><button class="button" onmouseup="toggleCheckbox('left-stop');" onmousedown="toggleCheckbox('left');" ontouchend="toggleCheckbox('left-stop');" ontouchstart="toggleCheckbox('left');">⬅️</button></td>
        <td align="center"><button class="button" onmouseup="toggleCheckbox('right-stop');" onmousedown="toggleCheckbox('right');" ontouchend="toggleCheckbox('right-stop');" ontouchstart="toggleCheckbox('right');">➡️</button></td>
      </tr>         
      <tr><td colspan="3" align="center"><button class="button" onmouseup="toggleCheckbox('up-stop');" onmousedown="toggleCheckbox('down');" ontouchend="toggleCheckbox('up-stop');" ontouchstart="toggleCheckbox('down');">⬇️</button></td></tr>     
    </table>
   <script>
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/action?go=" + x, true);
     xhr.send();
   }

  var up = false;
  var down = false;
  var left = false;
  var right = false;

  function KeyCheckDown() {
    var KeyID = event.keyCode;

    switch(KeyID) {
      case 37:
      if (left) {
        break;
      }
      left = true;
      toggleCheckbox("left");
      break;
      
      case 38:
      if (up) {
        break;
      }
      up = true;
      toggleCheckbox("up");
      break

      case 39:
      if (right) {
        break;
      }
      right = true;
      toggleCheckbox("right");
      break;

      case 40:
      if (down) {
        break;
      }
      down = true;
      toggleCheckbox("down");
      break;   
     }
  }

  function KeyCheckUp() {
    var KeyID = event.keyCode;

    switch(KeyID) {
      case 37:
      toggleCheckbox("left-stop");
      left = false;
      break;
      
      case 38:
      toggleCheckbox("up-stop");
      up = false;
      break

      case 39:
      toggleCheckbox("right-stop");
      right = false;
      break;

      case 40:
      toggleCheckbox("down-stop");
      down = false;
      break;   
     }
  }

   document.onkeydown = KeyCheckDown;
   document.onkeyup = KeyCheckUp;

   window.onload = document.getElementById("photo").src = window.location.href.slice(0, -1) + ":81/stream";
  </script>
  </body>
</html>
)rawliteral";

static esp_err_t index_handler(httpd_req_t *req){
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)INDEX_HTML, strlen(INDEX_HTML));
}
