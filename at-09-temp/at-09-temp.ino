#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

int sensorPin = A0;
#define aref_voltage 5.0 

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

void writeToBLE(const char *value) {
  Serial.print("Writing :");
  Serial.println(value);
  mySerial.write(value, strlen(value));
}

float readTemperature() {
  int reading = analogRead(sensorPin);
  float voltage = (reading * aref_voltage) / 1024;
  Serial.print(voltage); 
  Serial.println(" volts");
  
  float temperatureC = voltage / 10 ;  
  Serial.print(temperatureC); Serial.println(" degrees C");
  
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); 
  Serial.println(" degrees F");
  return temperatureC;
}

char j = 0;
void loop() {
  float temp = readTemperature();
  char strFloat[20];
  dtostrf(temp, 2, 2, strFloat);
  writeToBLE(strFloat);
  j += 1;
  delay(2000);
}
