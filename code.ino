#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
SoftwareSerial mySerial(9, 10);
const int red = 3;
const int green = 4;
const int buzzer = 13;
const int flame = 6;
const int smoke = A0;

int thresh= 200;
int status = true;
String alertMsg;

SoftwareSerial B(10,11); // 10 need to connect TX, 11 need to connect TX

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(smoke,INPUT);
  pinMode(flame,INPUT);
  pinMode(buzzer, OUTPUT);

  B.begin(9600);
  
  lcd.begin();                      // initialize the lcd 
  lcd.clear();  
  lcd.backlight();

  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}
void siren(int buzzer){
  for(int hz = 440; hz < 1000; hz++){
    tone(buzzer, hz, 50);
    delay(5);
  }

  for(int hz = 1000; hz > 440; hz--){
    tone(buzzer, hz, 50);
    delay(5);
  }
}

void loop()
{
  Serial.println("Gas Val: "+String(analogRead(smoke))+", Flame state: "+String(!digitalRead(flame)));
  if (digitalRead(flame)== LOW || analogRead(smoke)>thresh)  //Flame or Smoke or Button detected
  {
    if(digitalRead(flame)== LOW){
    lcd.setCursor(5,0);
    lcd.print("Fire!");
    lcd.setCursor(3,1);
    lcd.print("SMOKE:"+String(analogRead(smoke)));

    
    B.print('F');
    B.print(";");
    delay(20);
    
    digitalWrite(red, HIGH);
    siren(buzzer);
    digitalWrite(buzzer, HIGH);
    digitalWrite(green, LOW);
    }
    if(analogRead(smoke)>thresh){
    lcd.setCursor(5,0);
    lcd.print("Smoke!");
    lcd.setCursor(3,1);
    lcd.print("SMOKE:"+String(analogRead(smoke)));

    
    B.print('S');
    B.print(";");
    delay(20);
    
    digitalWrite(red, HIGH);
    siren(buzzer);
    digitalWrite(buzzer, HIGH);
    digitalWrite(green, LOW);
    }
    if(digitalRead(flame)== LOW && analogRead(smoke)>thresh){
    lcd.setCursor(3,0);
    lcd.print("Fire Smoke!");
    lcd.setCursor(3,1);
    lcd.print("SMOKE:"+String(analogRead(smoke)));

    
    B.print('B');
    B.print(";");
    delay(20);
    
    digitalWrite(red, HIGH);
    siren(buzzer);
    digitalWrite(buzzer, HIGH);
    digitalWrite(green, LOW);
    }
  }
  else{
    status = true;
    lcd.setCursor(4,0);   
    lcd.print("SMOKE:"+String(analogRead(smoke)));
    lcd.setCursor(4,1);   
    lcd.print("FIRE:"+String(digitalRead(flame)==LOW?"HIGH":"LOW"));
    digitalWrite(red, LOW);
    digitalWrite(buzzer, LOW);
    noTone(buzzer);
    digitalWrite(green, HIGH);
    B.print('0');
    B.print(";");
    delay(20);
  }
  delay(200);
  lcd.clear();
}
 
