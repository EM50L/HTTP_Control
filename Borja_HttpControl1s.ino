#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
ESP8266WebServer servidor_web(80);

void setup(){
  Serial.begin(115200);
  Serial.println("\n\nIniciando WIFI ESP...");

  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP");
  
  servidor_web.on("/LedOn"  , D4a0         );//en el WEMOS d1 mini el led  
  servidor_web.on("/LedOff" , D4a1         );//el led se enciende cuando Pongo a D4
  servidor_web.on("/"       , pag_principal);

  servidor_web.begin();
  Serial.println("http://192.168.4.1");
}

void loop(){
  servidor_web.handleClient();
  yield();delay(1);//yield() ayuda a manejar la gestion wifi
}

void D4a0() {
  pinMode(D4, OUTPUT);
  digitalWrite(D4, 0);
  servidor_web.send(200, "text/plain", "Ok D4=0");
}

void D4a1() {
  pinMode(D4, OUTPUT);
  digitalWrite(D4, 1);
  servidor_web.send(200, "text/plain", "Ok D4=1");
}

PROGMEM const char Texto_html_pagina_principal[] = 
R"=====(
<a href=/LedOn > Encener LED </a> | 
<a href=/LedOff> Apagar  LED </a>
)=====";

void pag_principal() {
    servidor_web.send(200, "text/html", Texto_html_pagina_principal );
}




