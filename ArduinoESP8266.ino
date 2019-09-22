#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

//Numero de vuelta
int vuelta;

//Sensor Ultrasonico
int trig = 11;
int eco = 12;
int duracion;
int distancia;

//Sensor LCD
const int FOTOPIN = A0;
int valorSensorLCD = 0;

//Sensor Sonido
int MIC = 2;
int valorMIC;
int estado;

//Sensor de Inclinacion
int inPin = 1;
int lectura;
int previo = LOW;

//Sensor de objetos cercanos
const int PIRPin = 10;         // pin de entrada (for PIR sensor)
int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin

//Vibrador
int vib = 13;

void setup(){

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

  //pinMode(PIRPin, OUTPUT);
  pinMode(D11, OUTPUT);
  pinMode(D12, INPUT);
  pinMode(A0, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D8, INPUT);
  pinMode(D13,OUTPUT);

  delay(20000);
}

void loop(){
  
  //Imprime el numero de vuelta
  Serial.print("Vuelta #");
  Serial.println(vuelta);
  vuelta = vuelta+1;
  
  //Sensor Ultrasonico
  digitalWrite(D11, HIGH);
  delay(1);
  digitalWrite(D11, LOW);
  duracion = pulseIn(D12,HIGH);
  distancia = duracion/58.2;
  Serial.println("Sensor Distancia: " + String(distancia)+" cm");

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();

    JSONencoder["Distancia"] = String(distancia);

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
  } 
  

  //Sensor LCD con una resistencia de 1K Ohms
  valorSensorLCD =  analogRead(A0);
  Serial.print("Sensor LCD: ");
  Serial.println(valorSensorLCD);
  //delay(2000);
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();

    JSONencoder["Sensor LCD"] = String(valorSensorLCD);

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
  }

  //Sensor Sonido
  valorMIC = digitalRead(D2);
  Serial.print("Sensor Sonido: ");
  Serial.println(valorMIC);
  //delay(2000);
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();

    JSONencoder["Sonido"] = String(valorMIC);

    char JSONmessageBuffer[300];
    JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);


    HTTPClient client;
    client.begin("http://192.168.1.76:8080"); 
    client.addHeader("Content-type", "application/json");

    int httpCode = client.POST(JSONmessageBuffer); //Send the request
    String payload = client.getString(); //Get the response payload

    Serial.println(httpCode); //Print HTTP return code
    Serial.pri
ntln(payload); //Print request response payload
    
    client.end(); //Close connection
  }

  //Sensor de Inclinacion
  lectura = digitalRead(D3);
  Serial.print("Sensor Inclinacion: ");
  Serial.println(lectura);
  //delay(3000);
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();

    JSONencoder["Inclinación"] = String(lectura);

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
  }

  //Sensor de Objetos cercanos
  val = digitalRead(D8);
  Serial.print("Sensor de Objetos Cercanos: ");
  Serial.println(val);
  delay(1000);
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();

    JSONencoder["Objetos cercanos"] = String(val);

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
    
  }


  digitalWrite(D13, HIGH);
  delay (5000);
  digitalWrite(D13,LOW);
  delay(3000);
  
  Serial.println();
}
