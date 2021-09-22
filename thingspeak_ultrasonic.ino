//#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>
// defines variables

String apiKey = "UDP38SKM6VIA549C";   
const char* server = "api.thingspeak.com";
const char *ssid =  "ASR"; 
const char *pass =  "123456789";
const int trigPin = D4;  //D4
const int echoPin = D3;  //D3
long duration , distance;

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       Serial.println("Connecting to ");
       Serial.println(ssid);
       WiFi.begin(ssid, pass);
       pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
       pinMode(echoPin, INPUT); // Sets the echoPin as an Inpu
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    Serial.println(duration);
    
      // Convert the time into a distance
    distance = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
    Serial.println(distance);
     
    Serial.print(distance);
    Serial.print("cm");


                        if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {
                             String postStr = apiKey;
                             postStr +="&field2=";
                             postStr += String(distance);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                             Serial.print("Distance: ");
                             Serial.print(distance);                       
                             Serial.println("cm. Send to Thingspeak.");
                        }
       
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10);
}
