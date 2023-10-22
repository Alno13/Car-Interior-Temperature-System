// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
//#include <SoftwareSerial.h>

#define DHTPIN 7     // what digital pin we're connected to
int setTempPoint;
int mode;//0 if off, 1 if auto, 2 if security 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
//SoftwareSerial mySerial(10,11);


void setup() {
  pinMode(13,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
  digitalWrite(13,LOW);
  Serial.begin(9600);
  Serial3.begin(19200);
  Serial2.begin(9600);
  delay(1000);
  Serial3.println("AT");
  dht.begin();
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
  delay(100);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);
  int t = dht.readTemperature();
  
  if (isnan(t)) {
    //Serial.println("Failed to read from DHT sensor!");
    return;
  }
Serial2.println(t);
Serial.println(t);
if(Serial2.available()){
    String cmd = Serial2.readString();
    if (cmd == "ON"){
    setTempPoint = 20;
    mode = 1;
    }
    else if (cmd == "OFF"){
    digitalWrite(3,LOW);
    mode = 0;
    }
    else if (cmd == "SON")
    mode = 2;
    else{
    if (cmd.toInt()>0 || cmd.toInt()<=30)
    setTempPoint = cmd.toInt();  
    Serial.println(setTempPoint);
    }
    
  }
  if (mode == 1){
    if(setTempPoint<t)
    digitalWrite(3,HIGH);
    else
    digitalWrite(3,LOW);
  }
  if (mode == 2 && digitalRead(4) == HIGH){
  sendmessage();
  delay(1000);
  }
}

 void sendmessage()
{
  Serial3.println("AT+CMGF=1\r"); //AT command for text mode of gsm module 
  digitalWrite(13,HIGH);
  delay(1000);  
  Serial3.println("AT+CMGS=\"09283740765\"\r"); //  x is your mobile number
  digitalWrite(13,LOW);
  delay(1000);
  Serial3.println("A motion has been detected within your vehicle. Please check immediately!");
  delay(100);
  Serial3.println((char)26);
}
