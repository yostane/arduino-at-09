#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
int PIN_EN_OUT = 4;
int PIN_STATE_IN = 5;


void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(9600);

  sendCommand("AT");
  sendCommand("AT+ROLE0");
  sendCommand("AT+UUID0xFFE0");
  sendCommand("AT+CHAR0xFFE1");
  sendCommand("AT+NAMEbluino");
}

void sendCommand(const char * command) {
  Serial.print("Command send :");
  Serial.println(command);
  mySerial.println(command);
  //wait some time
  delay(100);

  char reply[100];
  int i = 0;
  while (mySerial.available()) {
    reply[i] = mySerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.print(reply);
  Serial.println("Reply end");
  delay(50);
}

void writeSerialToBLE(int value) {
  mySerial.println(value);
}

void writeToBLE(char value) {
  Serial.print("Writing hex :");
  Serial.println(value, HEX);
  mySerial.write(value);
}

char j = 0;
void loop() {
  writeToBLE(j);
  j += 1;
  delay(500);
}
