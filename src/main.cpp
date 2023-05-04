/* This is a test/play file from "plant-watering" file for me to learn.... */
#include <Arduino.h>
#include <Wire.h>                    // to speak I2C
#include <RTClib.h>                  // provides all the RTC lib commands, etc.
#include <SPI.h>  
  
int runday = 0;
int runhour = 0;
int runminute =0;

RTC_DS1307 rtc;                       // initalize RTC module/chip
const TimeSpan oneMin = TimeSpan(60);  

//enum daysOfWeek {SUN, MON, TUE, WED, THU, FRI, SAT};  // a list of the days, per Harrison's help
//struct runTime {                      // I get this but not totally :(
//  enum daysOfWeek dayOfWeek;          // Data fields inside daysOfWeek enum (array?)
//  int hour; 
//  int minute;
//};

//const int SCHEDULE_SIZE = 1;            // still learning: allows an 'array' of one
//struct runTime schedule[SCHEDULE_SIZE]; // create an array called runTime
DateTime lastRun;                       // DateTime from RTClib

//void setUpSchedule() {                  // when to run pump/watering
//  schedule[0].dayOfWeek = 1;
//  schedule[0].hour = 13;
//  schedule[0].minute = 46;
//}


void setup() {
  runday = 1;
  runhour = 14;
  runminute = 11;  
  Serial.begin(9600);               // init serial monitor 
  delay(2000);                        // wait for rtc to start (one time)
  if (! rtc.begin()) {                // I found this code online, strongly suggest to use
    Serial.println("Couldn't find RTC");
    while (1);
  }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));     // sets the RTC on each compile to the PC time
}  

bool shouldRun(DateTime now) {          // checks if pump should run
  Serial.println("in shouldRun");
  //for (int i = 0; i < SCHEDULE_SIZE; i++) {
    if (
      runday == now.dayOfTheWeek() && 
      runhour == now.hour() &&
      runminute == now.minute() &&
      now > lastRun + oneMin
    ) return true;
  //}
  return false; 
} 

void runPump() {                        // runs the pump for 'pumpOnDuration'
  for(int j=0; j < 25; j++) {
    Serial.println("in run pump");
    digitalWrite(13, HIGH);              // test code to see if it this routine is called, EVER :)
    delay(250);
    digitalWrite(13, LOW);
    delay(250); 
} 
  Serial.println ("in runPump");
}
void loop() {
 
  DateTime now = rtc.now();                           // set "now" var to current
  Serial.println(String("TIME:\t")+now.timestamp(DateTime::TIMESTAMP_FULL));
  Serial.println(String("DayOfWeek:\t")+now.dayOfTheWeek());
  Serial.println(String("hour:\t")+now.hour());
  Serial.println(String("minute:\t")+now.minute());

 if (shouldRun(now)) {
    Serial.println(" met conditions in shouldrun ");
    runPump();
    lastRun = now;
  }
 
 delay(2000);

}
