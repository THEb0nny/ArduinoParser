// https://github.com/GyverLibs/GParser
// https://www.youtube.com/watch?v=Ul03Vkg9A40

#include <GParser.h>

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(5); // Позволяет задать время ожидания данных
}

void loop() {
  ParseFromSerialInputValues(true); // Парсим данные по Serial
}

// Парсинг значений из Serial
void ParseFromSerialInputValues(bool debug) {
  if (Serial.available() > 2) { // Если что-то прислали
    char inputStr[64]; // Массив символов для записи из Serial
    int amount = Serial.readBytesUntil(';', inputStr, 64); // Считать посимвольно до символа конца пакета точки с запятой и записать количество полученных байт в переменную
    inputStr[amount] = NULL; // Если отправляющее устройство не отправит нулевой символ, то он не запишется в буффер и вывод строк будет некорректным, решение дописать вручную и т.о. закрываем строку
    GParser data(inputStr, ','); // Парсим массив символов по символу запятой
    int am = data.split(); // Получаем количество данных, внимание, ломает строку!
    for (int i = 0; i < am; i++) {
      String tmpStr = data[i];
      tmpStr.replace(" ", ""); // Удалить пробел, если он был введёт по ошибке
      tmpStr.trim(); // Удаление ведущими и конечные пробелы
      char tmpCharArr[tmpStr.length()];
      tmpStr.toCharArray(tmpCharArr, tmpStr.length() + 1);
      if (debug) Serial.println(String(i) + ") " + tmpStr); // Вывести начальную строку
      GParser data2(tmpCharArr, ':'); // Парсим массив символов по символу запятой
      int am2 = data2.split(); // Получаем количество данных, внимание, ломает строку!
      if (am2 > 1) { // Если существует не только ключ, а ещё и значение
        String key = data2[0]; // Ключ - первое значение
        float value = data2.getFloat(1); // Значение - второе, или data.getInt(1), чтобы получить целое число
        if (debug) Serial.println("key: " + key + ", value: " + String(value)); // Вывод
        // Присваивание значений
      }
    }
    if (debug) Serial.println(); // Перевод на новую строку для разделения значений, которые были введены
  }
}