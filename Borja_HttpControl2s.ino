#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
ESP8266WebServer servidor_web(80);

char* Red_WIFI      = "ABAI_MIR_guest";
char* password_WIFI = "lavidasabemejor";

void setup(){
  Serial.begin(115200);
  Serial.println("\n\n Iniciando...");

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("ESP");
  WiFi.begin(Red_WIFI, password_WIFI);//intenta conectarse al wifi
  
  servidor_web.on("/LedOn"  , D4a0         );//en el WEMOS d1 mini 
  servidor_web.on("/LedOff" , D4a1         );//el led esta conectado a D4
  servidor_web.on("/leerA0" , leerA0       );
  servidor_web.on("/"       , pag_principal);

  servidor_web.begin();
  Serial.println("http://192.168.4.1");
  delay(5000);  //tiempo para que conecte al WIFI
  Serial.print("http://"); Serial.println(WiFi.localIP().toString());
}

void loop(){
  servidor_web.handleClient();
  yield();delay(1);
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

void leerA0() {
  servidor_web.send(200, "text/plain", "A0="+String(analogRead(A0)) );
}

PROGMEM const char Texto_html_pagina_principal[] = 
R"=====(
<a href=/LedOn > Encener LED </a> | 
<a href=/LedOff> Apagar  LED </a> |
<a href=/leerA0> Leer A0     </a> 
)=====";

void pag_principal() {
    servidor_web.send(200, "text/html", Texto_html_pagina_principal );
}
