#include <LiquidCrystal.h> //Dołączenie bilbioteki
#include <Servo.h>
LiquidCrystal lcd(8, 10, 4, 7, 12, 13);
Servo servo;

int sensorPin = 9;
int buttonPin = 2;
int pwmX, pwmY;

int oX = 0;
int oY = 1;

int valX = 0;
int valY = 0;

int offsetX = 0;
int offsetY = 0;

int mean = 8;
int tmp;

int directionFlag = 0;
volatile int cnt = 0;
volatile int servoState = 0, servoFlag = 0;


void setup() {

  servo.attach(16);
  servo.write(1500);
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("initialization..."); //Wyświetlenie tekstu

   pinMode(sensorPin, INPUT);
   pinMode(buttonPin, INPUT);
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  
  Serial.begin(9600);

  for(int i = 0; i < 8; i++){
    offsetX += analogRead(oX);
    offsetY += analogRead(oY); 
    delay(10);
   
   }
    offsetX /= 8;
    offsetY /= 8;
    Serial.println(offsetY);
    Serial.println(offsetY);
  int valX = offsetX;
  int valY = offsetY;
  
  attachInterrupt(digitalPinToInterrupt(sensorPin), cunter, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), servoSet, RISING);

  
cnt = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

  tmp = analogRead(oX);
  valX = ((valX*(mean-1))+tmp)/mean;
  tmp = analogRead(oY);
  valY = ((valY*(mean-1))+tmp)/mean;

  delay(10);
if (valY > 650) {
  //  directionFlag = 0;
   pwmY = map(abs(valY-512),0,512,96,256);
  analogWrite(11,pwmY);
  analogWrite(3,0);

  
  }
  else if (valY < 450){
    
//    directionFlag = 1;
  pwmY = map(abs(valY-512),0,512,96,256);
  analogWrite(3,pwmY);
  analogWrite(11,0);

  }
  else {
  analogWrite(3,0);
  analogWrite(11,0);
  }

  if (valX > 650) {
    directionFlag = 0;
   pwmX = map(abs(valX-512),0,512,96,128);
  analogWrite(6,pwmX);
  analogWrite(5,0);

  lcd.setCursor(0, 0); 
  lcd.clear();
  lcd.print("PWM X: ");
  lcd.setCursor(8,0);
  lcd.print( pwmY); 
  lcd.setCursor(0, 1); 
  lcd.print("CNT: -");
  lcd.setCursor(8,1);
  lcd.print( cnt); 
  }
  else if (valX < 450){
    
    directionFlag = 1;
  pwmX = map(abs(valX-512),0,512,96,128);
  analogWrite(5,pwmX);
  analogWrite(6,0);

  lcd.setCursor(0, 0); 
  lcd.clear();
  lcd.print("PWM X: -");
  lcd.setCursor(8,0);
  lcd.print( pwmY); 
  lcd.setCursor(0, 1); 
  lcd.print("CNT: -");
  lcd.setCursor(8,1);
  lcd.print( cnt); 
  }
  else {
  analogWrite(6,0);
  analogWrite(5,0);

  lcd.setCursor(0, 0); 
  lcd.clear();
  lcd.print("PWM X:   0");
  lcd.setCursor(0, 1); 
  lcd.print("CNT: -");
  lcd.setCursor(8,1);
  lcd.print( cnt); 

}

lcd.setCursor(0, 0); 
  lcd.clear();
  lcd.print("PWM X: -");
  lcd.setCursor(8,0);
  lcd.print( valY); 
  lcd.setCursor(0, 1); 
  lcd.print("CNT: -");
  lcd.setCursor(8,1);
  lcd.print( pwmY); 

if (servoFlag == 1){
  servoFlag = 0;  

  if (servoState == 0) servo.write(1400);
else servo.write(2000);
  }
    
}

void cunter (){
  if(directionFlag == 0 )
  cnt++;
  else cnt--;
}

void servoSet(){
servoState = !servoState;
servoFlag = 1;


}



