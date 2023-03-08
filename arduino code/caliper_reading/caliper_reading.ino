#include <USB.h>
int dataIn = 1;
int clockIn = 3;

// Variables
int curClock = 1;
int lastClock = 1;
unsigned long timeStart = 0;
int out = 0;
// 
bool data[24] = {0};
int curIndex = 0;
double measurement = 0;

bool inInches = 0;

void setup() {
  // Pi  Set Up
  pinMode(dataIn, INPUT);     
  pinMode(clockIn, INPUT);

  USBSerial.begin(115200);
  delay(500);
  USBSerial.println("Ready!");
}


void loop(){
  if (curIndex == 23) {
    measurement = 0;
    int placeholder;
      if (inInches) {// Inches
        for (int a = 1; a < 15; a++) {
          if (data[a]) 
            placeholder = 1;
          else
            placeholder = 0;

          measurement += placeholder * pow(2, a-1);
        }
        measurement = (measurement * .0005);
        if (data[21])
          measurement *= -1;
        USBSerial.println(measurement, 4);
      }
      else {
        for (int a = 1; a < 15; a++) { // Millimeters
          if (data[a]) 
            placeholder = 1;
          else
            placeholder = 0;

          measurement += placeholder * pow(2, a-1);
        }
        
        measurement = measurement / 100;
        if (data[21])
          measurement *= -1;
        USBSerial.println(measurement,2);
      }
      
      
      // for (int i = 0; i < 24; i++) {
      //   if (i % 4 == 0)
      //     USBSerial.print(" "); 
      //   USBSerial.print(data[i]);
      // }
      // USBSerial.println();

      delay(50); // Makes it more readeable
  }

  lastClock = curClock;
  curClock = digitalRead(clockIn);
  if (lastClock == 0 && curClock == 1){
    
    if((micros() - timeStart) > 3000) // If have not received data in the last 700 us then reset
    {    
      // Serial.println("");
      curIndex = 0;
    }
    else if((micros() - timeStart) > 400 && curIndex != 1){
      // Serial.print(" ");
    }
    out = digitalRead(dataIn)+digitalRead(dataIn)+digitalRead(dataIn); // Tripple sampling to remove glitches
    if (out > 1){
      data[curIndex] = 0;
      // Serial.print("0");
    }
    else{
      data[curIndex] = 1;
      // Serial.print("1");
    }
    curIndex++;
    timeStart = micros();
    // Serial.println(curIndex);
  }
}
