//Library RTCModule

#include <SPI.h>
#include <SD.h>
#include <RTClib.h>

//Library Sensor Ultrasonic
#include <NewPing.h>

//pin yang dipakai oleh sensor
#define TRIGGER_PIN_1 6
#define ECHO_PIN_1 6
#define TRIGGER_PIN_2 7
#define ECHO_PIN_2 7

//pin untuk SD card
const int chipSelect = 10;

//nilai maximal, jika object melebihi nilai ini akan ditulis "out of range". 
#define MAX_DISTANCE 400



//define sensor
NewPing sensor1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sensor2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
float distance1, distance2;

//file untuk logging
File myFile; 


//RTCModule yang dipakai
RTC_DS1307 rtc; 

void setup() {
  Serial.begin(9600);

    while(!Serial); // for Leonardo/Micro/Zero
    if(! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }
    else {
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    if(! rtc.isrunning()) {
      Serial.println("RTC is NOT running!");
    }
    
  // setup for the SD card
  Serial.print("Initializing SD card...");

  if(!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
    
  //open file
  myFile=SD.open("DATA.txt", FILE_WRITE);

  // if the file opened ok, write to it:
  if (myFile) {
    Serial.println("File opened ok");
    // print the headings for our data
    
  }
  myFile.close();
}

  // put your setup code here, to run once:



void loggingTime() {
  DateTime now = rtc.now();
  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(now.year(), DEC);
    myFile.print('/');
    myFile.print(now.month(), DEC);
    myFile.print('/');
    myFile.print(now.day(), DEC);
    myFile.print(',');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
    myFile.print(",");
    myFile.print(" ");
  }
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.println(now.day(), DEC);
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.println(now.second(), DEC);
  myFile.close();
  delay(1000);  
}

void measure() {
  distance1 = sensor1.ping_cm();
  delay(20);
  
  // Sensor 2
  distance2 = sensor2.ping_cm();
  delay(20);


    // Sensor 1
  Serial.print("Distance 1 = ");
  if (distance1 >= 400 || distance1 <= 2) {
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance1);
    Serial.println(" cm");
    delay(500);
  }
  // Sensor 2
  Serial.print("Distance 2 = ");
  if (distance2 >= 400 || distance2 <= 2) {
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance2);
    Serial.println(" cm");
    delay(500);
  }

  delay(500);

  myFile = SD.open("DATA.txt", FILE_WRITE);
  if (myFile) { 
    Serial.println("open with succes");
    
    myFile.print("Distance 1 = ");
    myFile.print(distance1);
    myFile.print(", ");
    myFile.print("Distance 2 = ");
    myFile.print(distance2);
    myFile.println();
   

  }
  myFile.close();

}


void loop(){ 
  loggingTime(); 
  measure();
  delay(3000);
} 


