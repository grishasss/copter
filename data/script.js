let websocket_started = 0
let FILE_LIST = [];
var body = document.getElementsByTagName("body")[0];



ws_source = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);

function gen_file_list(){
  var tbl = document.createElement("table");
  var tblBody = document.createElement("tbody");

  for(let i = 0 ; i < FILE_LIST.length ; i++){
    var row = document.createElement("tr");


    var c = document.createElement("td");
    var cell = document.createElement("a");
    var cellText = document.createTextNode(FILE_LIST[i].name);
    cell.appendChild(cellText);
    c.appendChild(cell);
    row.appendChild(c);

    c = document.createElement("td");
    cell = document.createElement("a");
    cellText = document.createTextNode(FILE_LIST[i].size);
    cell.appendChild(cellText);
    c.appendChild(cell);
    row.appendChild(c);

    c = document.createElement("td");
    cell = document.createElement("a");
    cellText = document.createTextNode("view");
    cell.setAttribute("href" , FILE_LIST[i].name);
    cell.appendChild(cellText);
    c.appendChild(cell);
    row.appendChild(c);

    c = document.createElement("td");
    cell = document.createElement("a");
    cellText = document.createTextNode("download");
    cell.setAttribute("href" , FILE_LIST[i].name);
    cell.setAttribute("download" , FILE_LIST[i].name);
    cell.appendChild(cellText);
    c.appendChild(cell);
    row.appendChild(c);

    c = document.createElement("td");
    cell = document.createElement("a");
    cellText = document.createTextNode("delete");
    cell.setAttribute("href" , "http://google.com");
    cell.appendChild(cellText);
    c.appendChild(cell);

    row.appendChild(c);
    
    tblBody.appendChild(row);
  }
  tbl.setAttribute("border", "1" );


  tbl.appendChild(tblBody);
  body.appendChild(tbl);
}

function get_command(e){
  let D = new Int8Array(e.data); 
  switch (D[0]){
    case 0:
      console.log("read file name");
      FILE_LIST = [];
      let cnt = D[1];
      let it = 2;
      for(let i = 0 ; i < cnt ; i++){
        let tec = "";
      
        for(let j = it  + 3; j < it + D[it] + 3 ; j++){
          tec += String.fromCharCode(D[j]);
        }
        FILE_LIST.push({name: tec , size : ((D[it + 1] << 8) + D[it + 2])});
        console.log(tec);
        it = it + D[it] + 3;
      }
    gen_file_list();
    break;

  }
}




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
      

      let c1 = new Int8Array(1);
      c1[0] = 1;
      ws_source.send(c1);
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
      console.log(e.data);     
      get_command(e);
    };

}

startSocket();

// console.log(websocket_started);
// ws_source.send("Message");


