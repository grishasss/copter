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



void WEB::webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
    switch (type){
        case WStype_CONNECTED:
            Serial.println("WebSocket is Connected");
            break;
        case WStype_DISCONNECTED:
            Serial.println("WebSocket is Disonnected");
            break;
        case  WStype_TEXT:
            Serial.println("read data to server!!!");
            Serial.write(payload, lenght);
            // for(int i = 0 ; i  < 8 ; i+=2){
            //     Math->state_joy[i >> 1] = payload[i + 1];
            //     Math->state_joy[i >> 1] |= (payload[i + 1] << 8);
            // }
            Serial.println(num);
            webSocket.sendTXT(num , "hi comp");
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
            Serial.println("Connected!!! \n HOME MODE");
            Serial.print("IP address:\t");
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


