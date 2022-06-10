let websocket_started = 0
ws_source = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);




var joy1 = new JoyStick('joy1Div',{
    // The ID of canvas element
    title: 'joystic1k',
    // width/height
    width: undefined,
    height: undefined,
    // Internal color of Stick
    internalFillColor: '#00AA00',
    // Border width of Stick
    internalLineWidth: 2,
    // Border color of Stick
    internalStrokeColor: '#003300',
    // External reference circonference width
    externalLineWidth: 2,
    //External reference circonference color
    externalStrokeColor: '#008000',
    // Sets the behavior of the stick
    autoReturnToCenter: false
    
});


var joy2 = new JoyStick('joy2Div',{
    // The ID of canvas element
    title: 'joystick2',
    // width/height
    width: undefined,
    height: undefined,
    // Internal color of Stick
    internalFillColor: '#00AA00',
    // Border width of Stick
    internalLineWidth: 2,
    // Border color of Stick
    internalStrokeColor: '#003300',
    // External reference circonference width
    externalLineWidth: 2,
    //External reference circonference color
    externalStrokeColor: '#008000',
    // Sets the behavior of the stick
    autoReturnToCenter: true
    
});

function startSocket(){
    if (websocket_started){
        ws_source.close();
    }
    ws_source.binaryType = "arraybuffer";

    ws_source.onopen = function(e){
        console.log("WS");
        websocket_started = true;
        document.getElementById("status_connected").textContent = "connected";
    };

    ws_source.onclose = function(e){
        websocket_started = false;
        console.log("~WS");
        document.getElementById("status_connected").textContent = "disconnected";
        if(!log_off) setTimeout(startSocket, 3000);
    };
    ws_source.onerror = function(e){
        console.log("WS", e);
    };
    ws_source.onmessage = function(e){
        console.log(e.data);     
        get_command(e);
    };

}

function send_joy_status(){
    if(!websocket_started) return;
    console.log("send status joy");
    let A = new Uint8Array(5);
    A[0] = 3;
    A[1] = (joy1.GetX() + 100);
    A[2] = (joy1.GetY() + 100);
    A[3] = (joy2.GetX() + 100);
    A[4] = (joy2.GetY() + 100);
    ws_source.send(A);
}


startSocket();


setInterval(send_joy_status ,100);
