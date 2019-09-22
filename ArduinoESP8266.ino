#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setup()
{
  Serial.begin(9600);
  Serial.println();

  WiFi.begin("Nontraf", "jmmg1403");

  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Conectado, dirección IP: ");
  Serial.println(WiFi.localIP());

  delay(20000);
}

void loop() {
  
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient Post;
    Post.begin("http://192.168.1.76:8080"); 
    Post.addHeader("Content-type", "application/json");
 
    Post.POST("{Key:984984}");
    String payload = Post.getString();
    Post.end();
    Serial.println("Si entro.....");
  } 
  delay(2000);  
  
}
