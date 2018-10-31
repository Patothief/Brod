#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>

#define INPUT_1_PIN   16     // D0
#define INPUT_2_PIN   5      // D1
#define ENABLE_A_PIN  4      // D2

#define INPUT_3_PIN   14     // D5
#define INPUT_4_PIN   12     // D6
#define ENABLE_B_PIN  13     // D7

ESP8266WebServer server(80);
ESP8266WiFiMulti wifiMulti;

const char *webpage = 
#include "WebPage.h"
;

void setup() {
  Serial.begin(9600);
  
  delay(10);

  wifiMulti.addAP("Infoart", "Iart236WEP707");
  wifiMulti.addAP("AMIS-1-002196675318", "malamerica");
  wifiMulti.addAP("HUAWEI P smart", "1346776aec86");
  
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  } 

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); 

  if (MDNS.begin("WifiBoat")) {
    Serial.println("MDNS Responder Started");

    MDNS.addService("nodeMcuBoat", "tcp", 23);
  }
 
  // Start the server

  server.on("/", handleRoot);

  server.on("/forward", []() {
    Serial.println("forward");
    
    digitalWrite(INPUT_1_PIN, LOW);
	digitalWrite(INPUT_2_PIN, HIGH);
	    
	digitalWrite(INPUT_3_PIN, LOW);
    digitalWrite(INPUT_4_PIN, HIGH);
    
    server.send(200, "text/plain", "forward");
  });

  server.on("/stop", [](){
    Serial.println("stop");
    
    digitalWrite(INPUT_1_PIN, LOW);
    digitalWrite(INPUT_2_PIN, LOW);
    
    digitalWrite(INPUT_3_PIN, LOW);
    digitalWrite(INPUT_4_PIN, LOW);
    
    server.send(200, "text/plain", "stop");
  });

  server.on("/backward", [](){
    Serial.println("backward");
    
    digitalWrite(INPUT_1_PIN, HIGH);
    digitalWrite(INPUT_2_PIN, LOW);
    
    digitalWrite(INPUT_3_PIN, HIGH);
    digitalWrite(INPUT_4_PIN, LOW);
    
    server.send(200, "text/plain", "backward");
  });
  
  server.on("/left", []() {
    Serial.println("left");
    
    digitalWrite(INPUT_1_PIN, LOW);
	digitalWrite(INPUT_2_PIN, LOW);
	    
	digitalWrite(INPUT_3_PIN, LOW);
    digitalWrite(INPUT_4_PIN, HIGH);
    
    server.send(200, "text/plain", "left");
  });

  server.on("/right", []() {
    Serial.println("right");
    
    digitalWrite(INPUT_1_PIN, LOW);
	digitalWrite(INPUT_2_PIN, HIGH);
	    
	digitalWrite(INPUT_3_PIN, LOW);
    digitalWrite(INPUT_4_PIN, LOW);
    
    server.send(200, "text/plain", "left");
  });
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  Serial.println("==========================================");
  
  pinMode(INPUT_1_PIN, OUTPUT);
  pinMode(INPUT_2_PIN, OUTPUT);
  pinMode(ENABLE_A_PIN, OUTPUT);

  pinMode(INPUT_3_PIN, OUTPUT);
  pinMode(INPUT_4_PIN, OUTPUT);
  pinMode(ENABLE_B_PIN, OUTPUT);
  
  digitalWrite(INPUT_1_PIN, LOW);
  digitalWrite(INPUT_2_PIN, LOW);
  digitalWrite(ENABLE_A_PIN, HIGH);

  digitalWrite(INPUT_3_PIN, LOW);
  digitalWrite(INPUT_4_PIN, LOW);
  digitalWrite(ENABLE_B_PIN, HIGH);
}

void loop() {
	server.handleClient();
}

void handleRoot() {
	server.send(200, "text/html", webpage);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
