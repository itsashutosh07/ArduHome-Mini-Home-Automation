#include <SoftwareSerial.h>

SoftwareSerial BT(0,1);

#define redPin 3
#define greenPin 5
#define bluePin 6
#define motorPin 9
#define bulbPin 10
#define sensorPin 8
#define relayPin 11
#define sensorLed 12

void setup()
{
  Serial.begin(9600);

  BT.begin(9600);
  

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(bulbPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(sensorLed, OUTPUT);
  
  deviceControl(220,60,190,0,215,0);
 
}

//creating variables globally

int redInt = 220;
int greenInt = 60;
int blueInt = 190;
int motorInt = 165;
int bulbInt = 215;
int relayInt = 0;
String voiceCommand = "empty";

void loop()
{

  
  if(!digitalRead(sensorPin))
    digitalWrite(sensorLed, HIGH);
  else
    digitalWrite(sensorLed, LOW);
    
    int i = 0;
    int arr[6];
    for(int x = 0;x<=5;x++)
      arr[x] = 0;
      
    delay(5);
    if(BT.available()){
      while(i<=5){
        if(BT.available()){
          arr[i] = BT.read();
          i++;
        }
      }
      Serial.println("input taken");
      redInt = arr[0];
      greenInt = arr[1];
      blueInt = arr[2];
      motorInt = arr[3];
      bulbInt = arr[4];
      relayInt = arr[5];
      voiceCommand = BT.readString();
  
  
      redInt = constrain(redInt, 0, 255);
      greenInt = constrain(greenInt, 0, 255);
      blueInt = constrain(blueInt, 0, 255);
      motorInt = constrain(motorInt, 0, 255);
      bulbInt = constrain(bulbInt, 0, 255);
      relayInt = constrain(relayInt,0,1);
  
        voiceCommand.toLowerCase();
        if(voiceCommand != "empty")
        {
          
    
          if(voiceCommand == "rgb off" || voiceCommand == "rgb of")
          { 
            redInt = 0;
            greenInt = 0;
            blueInt = 0;
          }
    
          if(voiceCommand == "rgb on")
          {
            redInt = 220;
            greenInt = 60;
            blueInt = 190;
          }
    
          if(voiceCommand == "bulb off" || voiceCommand == "bulb of")
            bulbInt = 0;
  
          if(voiceCommand == "bulb on")
            bulbInt = 215;
          
          if(voiceCommand == "fan off" || voiceCommand == "fan of")
            motorInt = 0;
  
          if(voiceCommand == "fan on")
            motorInt = 165;
          
          if(voiceCommand == "ac bulb off" || voiceCommand == "ac bulb of")
            relayInt = 0;
          
          if(voiceCommand == "ac bulb on")
            relayInt = 1;
          
          if(voiceCommand == "all on"){
            redInt = 220;
            greenInt = 60;
            blueInt = 190;
            motorInt = 255;
            bulbInt = 215;
            relayInt = 1;
            
          }
          
          if(voiceCommand == "all off" || voiceCommand == "all of"){
            redInt = 0;
            blueInt = 0;
            greenInt = 0;
            motorInt = 0;
            bulbInt = 0;
            relayInt = 0;
            
          }
          
        
      }
  
      Serial.print("R : ");
      Serial.println(redInt);
      Serial.print("G : ");
      Serial.println(greenInt);
      Serial.print("B : ");
      Serial.println(blueInt);
      Serial.print("Motor : ");
      Serial.println(motorInt);
      Serial.print("Bulb : ");
      Serial.println(bulbInt);
      Serial.print("Relay : ");
      Serial.println(relayInt);
      Serial.print("Command : ");
      Serial.println(voiceCommand);
      Serial.println("------------------------");
      
      voiceCommand = "empty";
      deviceControl(redInt, greenInt, blueInt, motorInt, bulbInt, relayInt);

    }
}

void deviceControl(int red, int green, int blue, int motor, int bulb, int relay)
{
  Serial.println("writing on pins");
  Serial.print("red : ");
  Serial.println(red);
  Serial.print("green : ");
  Serial.println(green);
  Serial.print("blue : ");
  Serial.println(blue);
  
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  analogWrite(bulbPin, bulb);
  analogWrite(motorPin, motor);
  digitalWrite(relayPin, relay);
}
