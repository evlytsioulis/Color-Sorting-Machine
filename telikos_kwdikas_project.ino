#include <Servo.h>
Servo pickServo;
Servo dropServo;

#define S0 4 
#define S1 5
#define S2 7
#define S3 6
#define sensorOut 8    
int frequency = 0;
int color=0;

int detectColor() {
  // activating red photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("Red = ");
  Serial.print(frequency);//printing RED color frequency
  Serial.print("   ");
  delay(50);

   // activating blue photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("Blue = ");
  Serial.print(frequency);
  Serial.println("   ");
  
  // activating green photodiodes to read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("Green = ");
  Serial.print(frequency);
  Serial.print("   ");
  delay(50);

  delay(50);

//Readings are different for different setup
//change the readings according your project and readings detected
  if(R<400 & R>175 & G<600 & G>220 & B<600 & B>200){
    color = 1; // Red
    Serial.print("Detected Color is = ");
    Serial.println("RED");
  }
  if(R<550 & R>310 & G<500 & G>250 & B<400 &B>350){
    color = 5; // Green
      Serial.print("Detected Color is = ");
    Serial.println("GREEN");
  }
  if(R<150 & R>100 & G<150 & G>110 & B<100 & B>50 ){
    color = 4; // White
       Serial.print("Detected Color is = ");
    Serial.println("WHITE");
  }
  if (G<650 & G>200 & B<450 & B>250 & R<650 & R>400){
    color = 3; // Blue
     Serial.print("Detected Color is = ");
    Serial.println("BLUE");
  }
  return color;  
}

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  //frequency-scaling to 20% selected
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);

  pickServo.attach(9);
  dropServo.attach(10);

  Serial.begin(9600);
}

void loop() {
  //initial position of servo motor
  pickServo.write(115);
  delay(600);
  
  for(int i = 115; i > 65; i--) {
    pickServo.write(i);
    delay(2);
  }
  delay(500);
  //read color values by calling function. save the values for conclusion in variable
  color = detectColor();
  delay(1000);  

  switch (color) {
    case 1:
    dropServo.write(50);
    
    break;

    case 2:
    dropServo.write(80);
    break;

    case 3:
    dropServo.write(110);
    break;

    case 4:
    dropServo.write(140);
    break;

    case 5:
    dropServo.write(170);
    break;
    
    case 0:
    break;
  }
  delay(500);
  
  for(int i = 65; i > 29; i--) {
    pickServo.write(i);
    delay(2);
  } 
  delay(300);
  
  for(int i = 29; i < 115; i++) {
    pickServo.write(i);
    delay(2);
  }
  color=0;
}
