#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>


class WEB{
public:
    WEB();
    
    ESP8266WebServer server;
    WebSocketsServer webSocket;

     
    void start_WebSocket();
    
};

