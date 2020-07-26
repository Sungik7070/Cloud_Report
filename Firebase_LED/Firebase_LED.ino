#include <ESP8266WiFi.h>                                              
#include <FirebaseArduino.h>      
#define FIREBASE_HOST "led-control-4623e.firebaseio.com"    
#define FIREBASE_AUTH "2hWm4FPdZZdly8zZxfklhpTSVo2CuTNnVRwO5P6y"
#define WIFI_SSID "U+NetE313"                                          
#define WIFI_PASSWORD "4000006482"  
 
String RED_fireStatus = "";
int RED_LED = D4;      
                                                             
void setup(){
 Serial.begin(9600);
 delay(1000);    
 pinMode(RED_LED, OUTPUT);  
               
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                              
 Serial.print("Connecting to ");
 Serial.print(WIFI_SSID);
 while (WiFi.status() != WL_CONNECTED){
   Serial.print(".");
   delay(500);
 }
 Serial.println();
 Serial.print("Connected to ");
 Serial.println(WIFI_SSID);
 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 Firebase.setString("RED_LED_STATUS", "OFF");
}
void loop(){
  //firebase child값
 RED_fireStatus = Firebase.getString("RED_LED_STATUS");    
 //RED 상태 ON일 때
 if (RED_fireStatus == "ON")  {
    //시리얼 모니터에 ON 표시
   Serial.println("RED LED Turned ON");                                                        
    // RED_LED로 설정한 D4 켜기
   digitalWrite(RED_LED, HIGH);      
 } //RED 상채 OFF일 때
 else if (RED_fireStatus == "OFF") {
    //시리얼 모니터에 OFF 표시
   Serial.println("RED LED Turned OFF");
   // RED_LED로 설정한 D4 끄기
   digitalWrite(RED_LED, LOW);    
 } else {
   Serial.println("Command Error! Please send ON/OFF");
 }
 delay(1000);
} 
