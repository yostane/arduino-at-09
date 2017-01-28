#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);

  mySerial.println("AT");
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}

void loop() {
  
}
