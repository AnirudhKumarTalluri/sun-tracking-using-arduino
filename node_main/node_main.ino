#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>
#include<ESP8266WiFi.h>

#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU
SoftwareSerial s(D5,D6);


WiFiClient Client1;
HTTPClient http;

String response,result;
int begin_str,end_str;

String read_url="http://api.thingspeak.com/channels/1858930/feeds.json?api_key=NB42FK2OE6Z14452&results=1";
String url="http://api.thingspeak.com/update?api_key=VG77E3Y4YYZQ6WIF&field1=";

String read_api_data(String url1)
{
  http.begin(Client1,url1);
  if(http.GET()>0)
  {
    Serial.println("connected successfully");
    response= http.getString();
    begin_str=response.indexOf("\"entry_id");
    end_str=response.indexOf("}]}"); 
    result=response.substring(begin_str+24,end_str-1);
    Serial.println(response);
    return result;
    
  }
  else{
    Serial.println("failure in connection");
  }
  
}

void write_data_api(int data)
{
  url=url+data;
  http.begin(Client1,url);
  if(http.GET()>0)
  {
    Serial.println("connected successfully");
  }
  else{
    Serial.println("failure");
  }
  url="http://api.thingspeak.com/update?api_key=VG77E3Y4YYZQ6WIF&field1=";

  delay(10000);
  
}

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
  s.begin(115200);
  pinMode(D1,OUTPUT);
  

}

void loop() {

  String res=read_api_data(read_url);
  if(res=="1")
  {
    Serial.println(1);
    s.write("1");
    write_data_api(0);  
  }
  else{
    Serial.println(0);
    s.write(0);
  }
  digitalWrite(D1,LOW);
  delay(15000);
  digitalWrite(D1,HIGH);
  delay(1000);
  
  /*String res=read_api_data(read_url);
  Serial.println(res);
  delay(1000);
  //write_data_api(10);*/
  
  
}
