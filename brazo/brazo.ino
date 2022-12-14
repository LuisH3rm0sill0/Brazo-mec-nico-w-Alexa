#include <Arduino.h>
#include <WiFi.h>
#include <SocketIoClient.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>
#include <fauxmoESP.h>

fauxmoESP fauxmo;

const char* ssid     = "INFINITUM899C_2.4"; // Nombre de la red
const char* password = "kkBwh4Vy43";
const char* server = "34.125.8.32"; // Dirección IP del servidor
const uint16_t port = 5001; // Puerto del servidor
int payload_entero;

SocketIoClient socketIO;
#define ONBOARD_LED  2
String str;
int a;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

String resmsg;
StaticJsonDocument<256> doc;

int pinServo1 = 13;
int pinServo2 = 12;
int pinServo3 = 14;
int pinServo4 = 27;
int pinServo5 = 26;

float ANGULO1 = 180;
float ANGULO2 = 90;
float ANGULO3 = 50;
float ANGULO4 = 120;
float ANGULO5 = 180;

float ANGULOB1 = 100;
float ANGULOB2 = 120;
float ANGULOB3 = 10;
float ANGULOB4 = 170;
float ANGULOB5 = 180;

float ANGULOP1 = 70;
float ANGULOP2 = 120;
float ANGULOP3 = 10;
float ANGULOP4 = 170;
float ANGULOP5 = 180;

float ANGULOT1 = 130;
float ANGULOT2 = 120;
float ANGULOT3 = 10;
float ANGULOT4 = 170;
float ANGULOT5 = 180;

float ANGULOR1 = 180;
float ANGULOR2 = 90;
float ANGULOR3 = 20;
float ANGULOR4 = 170;
float ANGULOR5 = 60;

void setup() {
  
  Serial.begin(115200);
  connectWiFi_STA();
  socketIO.begin(server, port);

  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  servo5.attach(pinServo5);

  Serial.begin(115200);
  connectWiFi_STA();
    
    fauxmo.addDevice("bisturi");
    fauxmo.addDevice("pinzas");
    fauxmo.addDevice("tijeras");

    fauxmo.setPort(80);
    fauxmo.enable(true);

    fauxmo.onSetState([](unsigned char device_id, const char* device_name, bool state, unsigned char value) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
        
        switch (device_name[0]){
          
          case 'b':
            if (state){
              posicion_bisturi();
              delay(200);
              posicion_entrega();
            } else {
              posicion_reposo();
            }
            digitalWrite(2,state);
            resmsg = state ? "\"ON Bisturi\"" : "\"OFF Bisturi\"";
            Serial.println(resmsg);
            socketIO.emit("nuevo_mensaje", resmsg.c_str() );
          break;
          case 'p':
            if (state){
              posicion_pinzas();
              delay(200);
              posicion_entrega();
            } else {
              posicion_reposo();
            }
            digitalWrite(2,state);
            resmsg = state ? "\"ON Pinzas\"" : "\"OFF Pinzas\"";
            Serial.println(resmsg);
            socketIO.emit("nuevo_mensaje", resmsg.c_str() );
          break;
          case 't':
            if (state){
              posicion_tijeras();
              delay(200);
              posicion_entrega();
            } else {
              posicion_reposo();
            }
            digitalWrite(2,state);
            resmsg = state ? "\"ON Tijeras\"" : "\"OFF Tijeras\"";
            Serial.println(resmsg);
            socketIO.emit("nuevo_mensaje", resmsg.c_str() );
          break;
          default:
            posicion_reposo();
          break;
        }
    });

  posicion_reposo();
}

void loop() {
  fauxmo.handle();
  socketIO.loop();
}

void connectWiFi_STA()
{
   delay(10);
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid,password);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
   Serial.println("");
   Serial.print("Iniciado STA:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());
}

void posicion_entrega(void)
{
  servo1.write(ANGULO1);
  delay(100);
  servo2.write(ANGULO2);
  delay(100);
  servo3.write(ANGULO3);
  delay(100);
  servo4.write(ANGULO4);
  delay(1800);
  servo5.write(100);
}

void posicion_bisturi(void)
{
  servo5.write(180);
  servo1.write(ANGULOB1);
  delay(400);
  servo2.write(ANGULOB2);
  delay(100);
  servo3.write(ANGULOB3);
  delay(100);
  servo4.write(ANGULOB4);
  delay(100);
  servo5.write(10);
  delay(600);
}

void posicion_pinzas(void)
{
  servo5.write(180);
  servo1.write(ANGULOP1);
  delay(400);
  servo2.write(ANGULOP2);
  delay(100);
  servo3.write(ANGULOP3);
  delay(100);
  servo4.write(ANGULOP4);
  delay(100);
  servo5.write(10);
  delay(600);
}

void posicion_tijeras(void)
{
  servo5.write(180);
  servo1.write(ANGULOT1);
  delay(400);
  servo2.write(ANGULOT2);
  delay(100);
  servo3.write(ANGULOT3);
  delay(100);
  servo4.write(ANGULOT4);
  delay(100);
  servo5.write(10);
  delay(600);
}

void posicion_reposo(void)
{
  servo5.write(180);
  servo1.write(ANGULOR1);
  delay(100);
  servo2.write(ANGULOR2);
  delay(100);
  servo3.write(ANGULOR3);
  delay(100);
  servo4.write(ANGULOR4);
  delay(100);
  servo5.write(ANGULOR5);
}