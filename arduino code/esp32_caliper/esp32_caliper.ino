#include <USB.h>
#include <BleKeyboard.h>
#include <Adafruit_NeoPixel.h>
#include <MyButton.h>

#define LED_PIN 6

Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);

// Pin definitions
int batPin = 0;
int dataIn = 1;
int clockIn = 3;
MyButton enterEntry = MyButton(4);
MyButton regEntry = MyButton(5);
int batMos = 7;

// Caliper settings
bool inInches = 0;

// Battery stuff
float timeOutMins = 3;
unsigned long lastBatUpdate = millis();
unsigned long lastDataSend = millis();

BleKeyboard bleKeyboard("ESP32 Caliper", "", 100);

void setup() {
  pinMode(dataIn, INPUT);
  pinMode(clockIn, INPUT);
  pinMode(batMos, OUTPUT);

  USBSerial.begin(115200);

  pixels.begin();

  if (enterEntry.updateButton() && regEntry.updateButton() ){
    inInches = 1;
    for (int i = 0; i < 3; i++) {
      setColor(221,160,221);
      delay(250);
      setColor(0,0,0);
      delay(250);
    } 
  }
  

  setColor(0, 0, 255);
  bleKeyboard.begin(); 

  for (int i = 0; i < 10; i++)
    batAvg();

}
void loop() {
  if (millis() - lastDataSend > 1000 * 60 * timeOutMins) {
    enterDeepSleep();
  }

  if (bleKeyboard.isConnected()) {
    if (millis() - lastBatUpdate > 1000) {
      lastBatUpdate = millis();
      bleKeyboard.setBatteryLevel(getBatPerc());
    }
      
    if (regEntry.getInitialPress()) { // Space at the end
      while (!getData()) ;
      sendData(1);
    } 

    if (enterEntry.getInitialPress()) {  // Press enter at the end
      while (!getData()) ;
      sendData(0);
    }
  } else {

    USBSerial.println("No device connected");

    setColor(0,0,255);
    delay(250);
    setColor(0,0,0);
    delay(250);
  }
}

