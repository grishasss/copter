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
      let DATE = new Date(Date.now());
      let date_time = new Int8Array(8);
      date_time[0] = 0;
      date_time[1] = DATE.getDate();
      date_time[2] = DATE.getMonth() + 1;
      date_time[3] = DATE.getYear() - 100;
      date_time[4] = DATE.getHours();
      date_time[5] = DATE.getMinutes();
      date_time[6] = DATE.getSeconds();
      date_time[7] = DATE.getMilliseconds() / 10;
      console.log(date_time);

      ws_source.send(date_time);
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

// console.log(websocket_started);
// ws_source.send("Message");


