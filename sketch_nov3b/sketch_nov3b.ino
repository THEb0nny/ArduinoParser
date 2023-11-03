// https://github.com/GyverLibs/GParser
// https://www.youtube.com/watch?v=Ul03Vkg9A40

#include <GParser.h>

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(1000);
}

void loop() {
  ParseSerialInputValues();
}

// Парсинг значений из Serial
void ParseSerialInputValues() {
    if (Serial.available()) {
    char inputStr[30];
    int amount = Serial.readBytesUntil(';', inputStr, 30);
    inputStr[amount] = NULL;

    GParser data(inputStr, ',');
    int am = data.split();

    for (int i = 0; i < am; i++) {
      Serial.println(data[i]);
    }
  }
}