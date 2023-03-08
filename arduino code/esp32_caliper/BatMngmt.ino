void enterDeepSleep() {
  USBSerial.println("entering deep sleep");

  esp_deep_sleep_enable_gpio_wakeup(1 << 4, ESP_GPIO_WAKEUP_GPIO_LOW);
  esp_deep_sleep_enable_gpio_wakeup(1 << 5, ESP_GPIO_WAKEUP_GPIO_LOW);
  
  for (int i = 255; i >= 0; i--) {
    setColor(i,0,0);
    delay(5);
  }
  
  esp_deep_sleep_start();
}

int getBatPerc() {
  int batAvgResult = batAvg() * 100;
  static int lastAvg = batAvgResult;
  static bool charging = 0;
  int chargConst = 0;
  int step = 1;
  if (batAvgResult < lastAvg - step) {
    charging = 0;
    lastAvg = batAvgResult;
  }
  if (batAvgResult > lastAvg + step) {
    charging = 1;
    lastAvg = batAvgResult;
  }
  
  if (charging)
    chargConst = 50;
  else
    chargConst = 0;

  int batPercent = map(batAvgResult, 300 + chargConst, 400 + chargConst, 0, 100);
  if (batPercent > 100 || batPercent < -100)
    batPercent = 100;
  else if (batPercent < 1)
    batPercent = 1;

  return batPercent;
}

float batAvg() {
  static float batVolts[10] = {};
  static int index = 0;
  digitalWrite(batMos, HIGH);
  batVolts[index++] = float(analogRead(0) - 200)/(4096) * 3.3*2;
  if (index > 9)
    index = 0;
  digitalWrite(batMos, LOW);
  float sum;
  for (int i = 0; i < 10; i++) {
    sum += batVolts[i];
  }
  return sum/10;
}
