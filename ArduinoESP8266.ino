#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("Nontraf", "jmmg1403");
  
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(5000);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Conectado, dirección IP: ");
  Serial.println(WiFi.localIP());

  delay(20000);
}

void loop() {
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();

    JSONencoder["temperatura"] = "muyCaliente";

    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);


    HTTPClient client;
    client.begin("http://192.168.1.76:8080"); 
    client.addHeader("Content-type", "application/json");

    int httpCode = client.POST(JSONmessageBuffer); //Send the request
    String payload = client.getString(); //Get the response payload

    Serial.println(httpCode); //Print HTTP return code
    Serial.println(payload); //Print request response payload
    
    client.end(); //Close connection

    Serial.println("Si entro.....");
  } 
  delay(2000);  
  
}
