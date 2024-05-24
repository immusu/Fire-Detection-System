#include<SoftwareSerial.h>

SoftwareSerial B(10,11);


void setup() {
  // put your setup code here, to run once:
  B.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  B.print('F');
  B.print(";");
  delay(20);
}
