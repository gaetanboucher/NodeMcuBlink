#include <Arduino.h>

const short int BUILTIN_LED1 = 2; //GPIO2
const short int BUILTIN_LED2 = 16; //GPIO16
//const short int BUILTIN_LED2 = 0; //GPIO0
void setup() {
pinMode(BUILTIN_LED1, OUTPUT); // Initialize the BUILTIN_LED1 pin as an output
pinMode(BUILTIN_LED2, OUTPUT); // Initialize the BUILTIN_LED2 pin as an output
//pinMode(BUILTIN_LED2, OUTPUT); // Initialize the BUILTIN_LED2 pin as an output
}

void loop() {
digitalWrite(BUILTIN_LED1, LOW); // Turn the LED ON by making the voltage LOW
digitalWrite(BUILTIN_LED2, HIGH); // Turn the LED ON by making the voltage LOW
//digitalWrite(BUILTIN_LED2, LOW); // Turn the LED ON by making the voltage LOW
delay(250); // Wait for a second
digitalWrite(BUILTIN_LED1, HIGH); // Turn the LED off by making the voltage HIGH
digitalWrite(BUILTIN_LED2, LOW); // Turn the LED off by making the voltage HIGH
//digitalWrite(BUILTIN_LED2, HIGH); // Turn the LED off by making the voltage HIGH
delay(500); // Wait for a seconds

}