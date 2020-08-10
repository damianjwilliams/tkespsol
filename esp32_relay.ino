#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h> 
#include <WebSocketsServer.h>

WebSocketsServer webSocket = WebSocketsServer(81);
const char *ssid = "ESP32_relay";
const char *password = "ESP32";
const int output6 = 12;
const int output7 = 13;
const int input1 = 33;
const int input2 = 27;
String led1state;
String led2state;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

    switch(type) {
        case WStype_DISCONNECTED:
            
            break;
        case WStype_CONNECTED:
         {
                IPAddress ip = webSocket.remoteIP(num);
                Serial.println("Connected");
                
                
            }
            break;
        case WStype_TEXT:

{
        Serial.println(payload[0]);
        Serial.println(payload[1]);

        
      if (payload[0] == 0)
      {
          digitalWrite(output6, LOW);
          
          
          Serial.println("LED1=off");
          
          
                 
      }
      else if (payload[0] == 1)
      {
          digitalWrite(output6, HIGH);
          
          
          Serial.println("LED1=On");
          
          
                 
      }

      if (payload[1] == 0)
      {
          digitalWrite(output7, LOW);
          Serial.println("LED2=off");
          
                 
      }
      else if (payload[1] == 1)
      {
          digitalWrite(output7, HIGH);
          Serial.println("LED2=on");
                 
      }

      if(digitalRead(input1)==HIGH)
      {Serial.println("LED 1 ON");
      led1state = "1";
      }
      else
      {Serial.println("LED 1 OFF");
      led1state = "0";
      
        }

       if(digitalRead(input2)==HIGH)
      {Serial.println("LED 2 ON");
      led2state = "1";
      }
      else
      {Serial.println("LED 2 OFF");
      led2state = "0";
        }
        


        String allledstates = "["+led2state+","+led1state+"]";
        Serial.println(allledstates);
        
        webSocket.sendTXT(num, allledstates);


        
           
           
            break;
} 
        case WStype_BIN:
     
            

            // echo data back to browser
            webSocket.sendBIN(num, payload, lenght);
            break;
    }

}


void setup() {

  pinMode(output6, OUTPUT);
  pinMode(output7, OUTPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  // Set outputs to LOW
  digitalWrite(output6, LOW);
  digitalWrite(output7, LOW);
  Serial.begin(115200);
   WiFi.softAP(ssid, password);

 IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    webSocket.loop();
    delay(50);
}
