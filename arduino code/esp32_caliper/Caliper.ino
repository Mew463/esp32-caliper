// Variables
int curClock = 1;
int lastClock = 1;
unsigned long timeStart = 0;
int out = 0;
// 
bool data[24] = {0};
int curIndex = 0;
double measurement = 0;

bool getData() { // returns true if there is a new value stored into measurement
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
      curIndex = 0;
      return true;
  }

  lastClock = curClock;
  curClock = digitalRead(clockIn);
  if (lastClock == 0 && curClock == 1){
    
    if((micros() - timeStart) > 3000) // If have not received data in the last 700 us then reset
    {    
      curIndex = 0;
    }
    else if((micros() - timeStart) > 400 && curIndex != 1){
    }
    out = digitalRead(dataIn)+digitalRead(dataIn)+digitalRead(dataIn); // Tripple sampling to remove glitches
    if (out > 1){
      data[curIndex] = 0;
    }
    else{
      data[curIndex] = 1;
    }
    curIndex++;
    timeStart = micros();
  }

  return false;
}



void sendData(bool withSpace) { // Sends measurement via bluetooth
  if (withSpace)
    setColor(0,255,0);
  else
    setColor(0,255,255);

  int numDec;
  if (inInches)
    numDec = 4;
  else
    numDec = 2;
  
  USBSerial.print("Sending over ");
  USBSerial.println(measurement, numDec);
  
  bleKeyboard.print("0");
  delay(200);
  bleKeyboard.write(KEY_BACKSPACE);
  delay(200);
  bleKeyboard.print(measurement, numDec);
  if (withSpace)
    bleKeyboard.print(" ");
  else
    bleKeyboard.write(KEY_RETURN);

  setColor(0,0,0);
  lastDataSend = millis();
}