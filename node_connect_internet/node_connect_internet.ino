#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>
#include<ESP8266WiFi.h>
WiFiClient Client1;
HTTPClient http;

void connectToInternet(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin("AK","123456789");
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
}
void setup() {
  Serial.begin(9600);
  connectToInternet();
  
  // put your setup code here, to run once:

}

void loop() {
  http.begin(Client1,"http://api.thingspeak.com/update?api_key=VG77E3Y4YYZQ6WIF&field1=52");
  if(http.GET()>0)
  {
    Serial.println("connected successfully");
  }
  else{
    Serial.println("failure");
  }
  delay(10000);
  
}
