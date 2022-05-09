#include "web.h"
#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>



void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {
    return;
}



WEB::WEB() : server(80) , webSocket(81) {
   
}

void WEB::start_WebSocket() {
    webSocket.begin();                         
    webSocket.onEvent(webSocketEvent);
    Serial.println("WebSocket server started.");
}



