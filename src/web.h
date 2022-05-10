#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>


#include "math_copter.h"
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>



#define TIME_ON_CONNECT 10000
const String HOME_SSID = "OpenWrtHome";
const String HOME_PASSWORD = "cuprum22";
const String AP_SSID = "efs";
const String AP_PASSWORD = "12345678";




class WEB{
public:
    WEB();
    
    ESP8266WebServer server;
    WebSocketsServer webSocket;
    MATH *Math;
     
    void start_WebSocket();
    void loop();
    void wifi_init();
    void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght);
};

