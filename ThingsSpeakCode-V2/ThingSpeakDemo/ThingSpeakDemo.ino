#include "thingspeak.h"

// For periodic timer
//#include "TimerOne.h"

void setup() {
  // put your setup code here, to run once:
  thingsSpeakGsmSetup();
  thingsSpeakSetPrivateSendKey("DQ54UA3WKJ50G4R6");

  // For periodic timer
  //Timer1.initialize(30000000);
  //Timer1.attachInterrupt(periodicLogFunc);

}

static unsigned short int dataUploadCount = 0;
void loop() {
  // put your main code here, to run repeatedly:

  float temperature=random(0,100);
  float humidity=random(0,100);
  Serial.print("Temp=");
  Serial.println(temperature);
  Serial.print("Humid=");
  Serial.println(humidity);
  delay(1000);

  float parameters[2] = { temperature, humidity};

  Serial.print("dataUploadCount: ");
  Serial.println(dataUploadCount);
  dataUploadCount++;
  thingsSpeakSend(parameters,  2);
  delay(30000);


}

/* For periodic timer
void periodicLogFunc()
{

    Serial.println("TestTimer");

}*/
