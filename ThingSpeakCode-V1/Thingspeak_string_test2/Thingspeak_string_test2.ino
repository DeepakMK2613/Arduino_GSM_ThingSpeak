#include <SoftwareSerial.h>
 const long oneSecond=1000;//a second is thousand millisecond.
 const long oneMinute=oneSecond*60;
 //const long oneHour=oneMinute*60;
  //const long oneDay=oneHour*24;
//unsigned long counter;
SoftwareSerial mySerial(3,4);
 
void setup() 
{
  mySerial.begin(9600);
  Serial.begin(9600);     
}

 void loop() 
{
    Send2thingspeak();
    if (mySerial.available())
    Serial.write(mySerial.read());  
}

//int iter=6;

void Send2thingspeak()
{  
   float get_temperature=random(0,100);
   float get_humidity=random(0,100);
   float Solar_volatge=random(0,100);
   float Solar_current=random(0,100);
   float Battery_volatge=random(0,100);
   float Battery_current=random(0,100);
   String string1=String("GET /update?key=PB8X7EAPVPF3URWL&field1="+String(get_temperature));
   String string2=String("&field2="+String(get_humidity)+"&field3="+String(Solar_volatge)+"&field4="+String(Solar_current)+"&field5="+String(Battery_volatge)+"&field6="+String(Battery_current));
   String string3=String(string1+string2);
   int value=2+string3.length();
   mySerial.println("AT+CIPSHUT");//close the GPRS connection
   delay(1000);
   ShowSerialData();
  // mySerial.println("AT+CIPCLOSE");//close the TCP connection
  // delay(1000);
  // ShowSerialData();
   mySerial.println("AT");
   delay(1000);
   ShowSerialData();
   mySerial.println("AT+CGATT=1");
   delay(1000);
   ShowSerialData();
   mySerial.println("AT+CIPMUX?");
   delay(1000); 
   ShowSerialData();
   mySerial.println("AT+CSTT=\"internet\",\"\",\"\"");    //AT+CSTT="internet","",""  {where internet is APN setting}
   delay(1000);
   ShowSerialData();
   mySerial.println("AT+CIICR");//bring up wireless connection
   delay(1000);
   ShowSerialData();
   mySerial.println("AT+CIFSR");//get local IP adress
   delay(1000);
   ShowSerialData();  
   mySerial.println("AT+CIPSTART=\"TCP\",\"184.106.153.149\",\"80\""); //start up the connection,where 184.106.153.149 is IP address of ThingSpeak & port no 80
   delay(1000);
   ShowSerialData();
  // Let's begin to send data to remote server
   mySerial.print("AT+CIPSEND=");//44 is used to send 2 digit values,45 is used to send 3 digit values,43 is used to send single digit values
   mySerial.println(value);  
   delay(1500);
   ShowSerialData();
   mySerial.println(string3);
   delay(1000);
   ShowSerialData();
   mySerial.println("AT+CIPCLOSE");//close the connection
   delay(1000);
   ShowSerialData();
  // delay(1000);
   mySerial.println("AT+CIPSHUT");//close the connection
   delay(200);
   ShowSerialData();
   delay(15*oneSecond);
}

//#define CHANGE_LOOP  1
void ShowSerialData()
{  


    // In case if data is available 
    while (mySerial.available()!=0)
      Serial.write(mySerial.read());
}
