let websocket_started = 0

ws_source = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);

function startSocket(){
    if (websocket_started){
        ws_source.close();
    }
   
    ws_source.binaryType = "arraybuffer";
    ws_source.onopen = function(e){
      console.log("WS");
      websocket_started = true;
    };
    ws_source.onclose = function(e){
      websocket_started = false;
      console.log("~WS");
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
        console.log(msg);        
      }
    };
}

startSocket();
ws_source.onopen = () => ws_source.send("Message");
