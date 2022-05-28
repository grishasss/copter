#pragma once

#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>


#include "math_copter.h"
#include "logger.h"


#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
// #include <WebSocketsClient.h>



#define TIME_ON_CONNECT 10000
#define max_client  10
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
    LOG *Log; 
    // WebSocketsClient clients[max_client];
    // int8_t client_number;
    void check_client();
    void start_all_server();
    void loop();
    void wifi_init();
    bool handleFileRead(String path);
    void query_file();
    void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght);
    void send_string(String data);
};

