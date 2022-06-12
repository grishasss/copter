#include "web.h"
#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>


String getContentType(String filename){
  if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  return "text/plain";
}

 void WEB::send_file_name(uint8_t client_num){
    Serial.println("send_file_name");
    Dir dir = SPIFFS.openDir("/log");
    size_t sz = 2;
    int8_t cnt_file = 0; 
    while(dir.next()){
        File tmpf = dir.openFile("r");
        String tec = tmpf.fullName();
        sz = sz + 3 + tec.length();
        cnt_file++;
    }

    uint8_t data[sz];
    data[0] = 0; 
    data[1] = cnt_file;
    int it = 2;
    dir = SPIFFS.openDir("/log");
    while(dir.next()){
        File tmpf = dir.openFile("r");
        String tec = tmpf.fullName();
        
        Serial.println(tmpf.size() >> 10);
        data[it++] = tec.length();
        data[it++] = (tmpf.size() >> 10) >> 8;
        data[it++] = (tmpf.size() >> 10) & ((1 << 8) - 1);
        

        for(uint8_t x : tec){
            data[it++] = x;
        }
    }
    Serial.println("file cnt: " + String(cnt_file));
    webSocket.sendBIN(client_num ,(const uint8_t *)data , sz);
}


void WEB::del_file(uint8_t * payload, size_t lenght){
    String name;
    for(uint8_t i = 0 ; i < payload[1] ;  i++){
        name+=((char)payload[i + 2]);
    }
    Serial.println("delete file: " + name);
    SPIFFS.remove(name);
}

void WEB::set_status_joy(uint8_t * payload, size_t lenght){
    Serial.println("set status joy");
    assert(lenght == 5);
    // Serial.println(((int16_t)(payload[1]) - 100));
    // Serial.println(((int16_t)(payload[2]) - 100));
    // Serial.println(((int16_t)(payload[3]) - 100));
    // Serial.println(((int16_t)(payload[4]) - 100));
    


    Sensors->joy1X = ((int16_t)(payload[1]) - 100);
    Sensors->joy1Y = ((int16_t)(payload[2]) - 100);
    Sensors->joy2X = ((int16_t)(payload[3]) - 100);
    Sensors->joy2Y = ((int16_t)(payload[4]) - 100);
}

void WEB::set_date(uint8_t * payload, size_t lenght){
    Serial.println("Set global time on client");
    assert(lenght == 8);
    Sensors->amendment =  (int32_t)payload[4] * 3600000 + (int32_t)payload[5] * 60000 + (int32_t)payload[6] * 1000 + (int32_t)payload[7] * 10 - millis();
    Sensors->date.day = payload[1];
    Sensors->date.mounth = payload[2];
    Sensors->date.year = payload[3];
    Sensors->time_recalc_big();
    if(!Sensors->date_is_ccorrect){
        Sensors->date_is_ccorrect = true;
        Log->open_file();
    }
}


void WEB::webSocketEvent(uint8_t client_num, WStype_t type, uint8_t * payload, size_t lenght) {
    switch (type){
        case WStype_CONNECTED:
            Serial.println("WebSocket is Connected");
            webSocket_it_connect = true;
            break;
        case WStype_DISCONNECTED:
            Serial.println("WebSocket is Disonnected");
            break;
        case  WStype_BIN:
            Serial.println("read BIN data to server!!!");
            get_command(client_num ,payload , lenght);
            break;
    }
}

bool WEB::handleFileRead(String path) {
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";
  String contentType = getContentType(path); 
  if (SPIFFS.exists(path)) { 
    File file = SPIFFS.open(path, "r"); 
    size_t sent = server.streamFile(file, contentType);
    Serial.println(sent);
    file.close(); 
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;
}

void WEB::query_file(){
    if (!handleFileRead(server.uri()))
        server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error

}

WEB::WEB() : server(80) , webSocket(81) {

}

void WEB::start_all_server() {
    server.begin(); 
    server.onNotFound(std::bind(&WEB::query_file, this));
    Serial.println("webserver started.");
    webSocket.begin();               
    webSocket.onEvent( std::bind(&WEB::webSocketEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4) );
    Serial.println("WebSocket server started.");
   
}

void WEB::loop(){
    server.handleClient();
    webSocket.loop(); 
}

void WEB::wifi_init(){
    int number_network = WiFi.scanNetworks();
    bool find_home = 0;
    Serial.println("start connect");
    for(int i = 0; i < number_network ; i++){
        if(HOME_SSID == WiFi.SSID(i)){
            find_home = 1;
            break;
        }
    }
    if(find_home){
        long start_time = millis();
        while(!WiFi.begin(HOME_SSID , HOME_PASSWORD) && millis() - start_time < TIME_ON_CONNECT) {
            delay(250);
            Serial.println("TRY");
            }
        if(!WiFi.begin(HOME_SSID , HOME_PASSWORD)){
            find_home = 0;
            Serial.println("FAIL");
        }
        else{
            Serial.println("Connected!!! \nHOME MODE");
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP()); 
        }
    }
    if(!find_home){
        WiFi.softAP(AP_SSID, AP_PASSWORD);
        Serial.println("AP MODE");
        Serial.print("IP address:\t");
        Serial.println(WiFi.softAPIP());
    }
    
}

void WEB::log_change_status(bool f){
    if(f) Serial.println("log write");
    else Serial.println("log no write");

    Log->log_is_write = f;
    Memory->write_bit(f , 0);
}


 void WEB::get_command(uint8_t client_num , uint8_t * payload, size_t lenght){
    assert(lenght);
    switch (payload[0]){
    case 0:
        set_date(payload , lenght);
        break;
    case 1:
        send_file_name(client_num);
        break;
    case 2:
        del_file(payload, lenght);
        break;
    case 3:
        set_status_joy(payload, lenght);
        break;
    case 4:
        log_change_status(1);
        break;
    case 5:
        log_change_status(0);
        break;
    
    default:
        assert(0);
        break;
    }
 }

