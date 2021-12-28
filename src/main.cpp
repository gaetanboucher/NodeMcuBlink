#include <Arduino.h>
#define BLYNK_PRINT Serial 
#include <ESP32Servo.h>
#include  <ESP8266WiFi.h>
#include  <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App. 
// Go to the Project Settings (nut icon). 
char auth[] = "E_Sw3sSCbge0XennQUi1JfVzUasxtiq7"; 
int carSpeed = 500;

// Your WiFi credentials. 
// Set password to "" for open networks. 
char ssid[] = "monwifi"; 
char pass[] = "15b4915b49"; 

Servo servo;

bool emergencyStop = false;

int IR_SENSOR_FRONT_R=D7;//Front IR sensor 
int IR_SENSOR_FRONT_L=D6;//Front IR sensor 
int PWMA=D1;//Right side 
int PWMB=D2;//Left side 
int DA=D3;//Right reverse 
int DB=D4;//Left reverse 
#define DIRA DA
void testMotors();


void setup(){ 
 // Debug console 
 Serial.begin(512000); 
 Serial.println("Setup.");
 Blynk.begin(auth, ssid, pass); 
//  pinMode(PWMA, OUTPUT); 
//  pinMode(PWMB, OUTPUT); 
  pinMode(DA, OUTPUT); 
  pinMode(DB, OUTPUT); 

 pinMode(16, OUTPUT); // Initialize the BUILTIN_LED2 pin as an output
 digitalWrite(16, LOW); 

 pinMode(IR_SENSOR_FRONT_R, INPUT);
 pinMode(IR_SENSOR_FRONT_L, INPUT);
 //pinMode(0, INPUT_PULLUP);
 //while (digitalRead(0) == 1)  {delay(100); }
 digitalWrite(16, HIGH); 
      delay(200);
 digitalWrite(16, LOW); 
      delay(200);
 digitalWrite(16, HIGH); 
      delay(200);
 digitalWrite(16, LOW); 
      delay(200);
 digitalWrite(16, HIGH); 
      delay(200);
 digitalWrite(16, LOW); 

     // testMotors();

     // digitalWrite(PWMA, LOW); 
     // digitalWrite(DA, LOW); 
     // digitalWrite(PWMB, LOW); 
     // digitalWrite(DA, LOW); 
     servo.attach(D8);
 } 

void loop(){ 
  servo.write(0);
  delay(500);
  delay(10000);
  servo.write(90);
  delay(500);
  delay(10000);
  servo.write(180);
  delay(500);
  delay(10000);
  servo.write(90);
  delay(500);
  delay(10000);
  servo.write(0);
  delay(500);
  delay(10000);     
 emergencyStop = (digitalRead(IR_SENSOR_FRONT_L) == LOW) || (digitalRead(IR_SENSOR_FRONT_R) == LOW);
 Blynk.virtualWrite(V18, emergencyStop);
if(emergencyStop){        //Obstacle 
  analogWrite(PWMA,1024); 
  digitalWrite(DA, HIGH); 

  analogWrite(PWMB, 1024); 
  digitalWrite(DB, HIGH);
  delay(300);
  analogWrite(PWMA, 0); 
  digitalWrite(DA, LOW); 

  analogWrite(PWMB, 0); 
  digitalWrite(DB, LOW); 
}
 Blynk.run(); 
} 

void testMotors(){ 
  pinMode(DIRA, OUTPUT);
  pinMode(DB, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  
  analogWrite(PWMA,0);
  digitalWrite(DIRA,1);
  analogWrite(PWMB,0);
  digitalWrite(DB,1);

//   analogWrite(PWMA,500);
//   delay(5000);

//    analogWrite(PWMA,1000);
//    delay(5000);

//   analogWrite(PWMA,3000);
//   delay(5000);

//   analogWrite(PWMA,1000);
//   delay(3000);

//   analogWrite(PWMA,0);
//   delay(3000);
  
   digitalWrite(DIRA,0);
   digitalWrite(DB,0);
  
//   analogWrite(PWMA,2500);
//   delay(3000);
  
  analogWrite(PWMA,700);
  analogWrite(PWMB,700);
  delay(5000);
  analogWrite(PWMA,1024);
  analogWrite(PWMB,1024);
  delay(5000);
  analogWrite(PWMA,2000);
  analogWrite(PWMB,2000);
  delay(5000);
  }


// Handling Speed slider data 
BLYNK_WRITE(V10){
int speed = param.asInt(); 
carSpeed = 100*(speed+1);
Blynk.virtualWrite(V17, carSpeed);
} 

// Handling Joystick data 
BLYNK_WRITE(V11){ 
int x = param[0].asInt(); 
int y = param[1].asInt();  
Blynk.virtualWrite(V15, x);
Blynk.virtualWrite(V16, y);
// if(emergencyStop){        //Obstacle 
//      analogWrite(PWMA,carSpeed); 
//      digitalWrite(DA, HIGH); 
     
//      analogWrite(PWMB, carSpeed); 
//      digitalWrite(DB, HIGH);
//   delay(1500);
     
// }else 
if(x==0 && y==0){        //Stay 
     analogWrite(PWMA, 0); 
     digitalWrite(DA, LOW); 
     
     analogWrite(PWMB, 0); 
     digitalWrite(DB, LOW); 
}else if(x==-10 && y==0){        //Left Turn 
     analogWrite(PWMA, carSpeed/2); 
     digitalWrite(DA, LOW); 
    
     analogWrite(PWMB, carSpeed/2); 
     digitalWrite(DB, HIGH); 
}else if(x==10 && y==0){        //Right turn 
     analogWrite(PWMA, carSpeed/2); 
     digitalWrite(DA, HIGH); 
     
     analogWrite(PWMB, carSpeed/2); 
     digitalWrite(DB, LOW); 
}else if(x<=-2  && y==-1){             //Backward and Left     
     analogWrite(PWMA, 0); 
     digitalWrite(DA, HIGH); 
     
     analogWrite(PWMB, carSpeed); 
     digitalWrite(DB, HIGH); 
}else if(x>-2 && x<2 && y==1){        //Forward 
     analogWrite(PWMA, carSpeed); 
     digitalWrite(DA, LOW); 
    
     analogWrite(PWMB, (carSpeed*100)/100); 
     digitalWrite(DB, LOW); 
}else if(x>-2 && x<2 && y==-1){        //Backward     
     analogWrite(PWMA,carSpeed); 
     digitalWrite(DA, HIGH); 
     
     analogWrite(PWMB, carSpeed); 
     digitalWrite(DB, HIGH);
}else if(x<=-2 && y==1){        //Forward and Left     
     analogWrite(PWMA, carSpeed); 
     digitalWrite(DA, LOW); 
    
     analogWrite(PWMB, (carSpeed  * (100 - abs(x*3)))/100); 
     digitalWrite(DB, LOW); 
}else if(x>=2 && y==-1){        //Backward and Right     
     analogWrite(PWMA, carSpeed); 
     digitalWrite(DA, HIGH); 
     
     analogWrite(PWMB, carSpeed); 
     digitalWrite(DB, HIGH); 
}else if(x>=2 && y==1){        //Forward and Right 
     analogWrite(PWMA, (carSpeed  * (100 - abs(x*3)))/100); 
     digitalWrite(DA, LOW); 
     
     analogWrite(PWMB, carSpeed); 
     digitalWrite(DB, LOW);
 } 
} 