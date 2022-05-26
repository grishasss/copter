let websocket_started = 0




function startSocket(){
    if (websocket_started){
        ws_source.close();
    }
    ws_source = new WebSocket('ws://'+websocket_IP + ':' + websocket_port +'/ws',['arduino']);
    // if(async_webcommunication){
      
    //   }
    // else {
        //console.log("Socket port is :" + websocket_port);
        // ws_source = new WebSocket('ws://'+websocket_IP + ':' + websocket_port,['arduino']);
    // }
    ws_source.binaryType = "arraybuffer";
    ws_source.onopen = function(e){
      console.log("WS");
      websocket_started = true;
    };
    ws_source.onclose = function(e){
      websocket_started = false;
      console.log("~WS");
      //seems sometimes it disconnect so wait 3s and reconnect
      //if it is not a log off
      if(!log_off) setTimeout(startSocket, 3000);
    };
    ws_source.onerror = function(e){
      console.log("WS", e);
    };
    ws_source.onmessage = function(e){
      var msg = "";
      //bin
      if(!(e.data instanceof ArrayBuffer)){
        msg = e.data;
        var tval = msg.split(":");
        if (tval.length >= 2) {
        if (tval[0] == 'currentID') {
            page_id = tval[1];
            console.log("ID " + page_id); 
        }
        if (tval[0] == 'activeID') {
            if(page_id != tval[1]) {
              HideAll("It seems you are connect from another location, your are now disconnected");
              }
          }
       if (tval[0] == 'ERROR') {
            esp_error_message = tval[2];
            esp_error_code = tval[1];
            console.log(tval[2] + " code:" +  tval[1]);
            uploadError();
            xmlhttpupload.abort();
          }
        }
        
      }
      //console.log(msg);
      
    };
}

startSocket();
