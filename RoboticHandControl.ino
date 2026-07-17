#include <Servo.h>

const int NUM_FINGERS = 5;

// Servo objects
Servo fingers[NUM_FINGERS];

// Flex sensor analog pins
const int flexPins[NUM_FINGERS] = {A0, A1, A2, A3, A4};

// Servo output pins
const int servoPins[NUM_FINGERS] = {2, 3, 4, 5, 6};

// Filter parameters
float alpha = 0.1;
float filteredFlex[NUM_FINGERS] = {0, 0, 0, 0, 0};

int flexMin[5] = {130, 130, 400, 150, 950};   // Sensor reading when fully bent
int flexMax[5] = {950, 600, 150, 950, 180}; // Sensor reading when flat

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < NUM_FINGERS; i++) {
    fingers[i].attach(servoPins[i]);
    pinMode(flexPins[i], INPUT);
    filteredFlex[i] = analogRead(flexPins[i]); // initialize filtered values
  }
}

void loop() {
  int angles[NUM_FINGERS];

  for (int i = 0; i < NUM_FINGERS; i++) {
    int raw = analogRead(flexPins[i]);

    // Low-pass filter
    filteredFlex[i] = alpha * raw + (1 - alpha) * filteredFlex[i];

    // Map and constrain to servo angle
    angles[i] = map(filteredFlex[i], flexMax[i], flexMin[i], 0, 180);
    angles[i] = constrain(angles[i], 0, 180);
  }

  for (int i=0; i< NUM_FINGERS; i++){
    fingers[i].write(angles[i]);
  }
    
  Serial.print("Flex: ");
  for (int i = 0; i < 5; i++) {
      Serial.print((int)filteredFlex[i]);
      Serial.print(" ");
    }
  Serial.println();
  
  delay(30);
  }
  
  

 



