/*
   Сайт разработчика https://arduino-tex.ru/
   Проекты на Arduino https://portal-pk.ru/page-17/proekty-na-arduino.html
   Проекты на ESP https://arduino-tex.ru/menu/10/11/proekty-na-esp8266-esp32.html
*/

#include "designerDWIN.h"  // подключаем функции конструктора
#define DEBUG 1                        // Отладка: 1 - вкл.  0 - выкл. 
#define LED 2  // светодиод

void setup() {
  if (DEBUG) {
    Serial.begin(115200);
    Serial.println("Start program");
  }
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);  // инициализируем дисплей
  pinMode(LED, OUTPUT);

  ClearDisplayDwin();  // Уаляем все с дисплея. Можно чистить и в основном цикле loop, но однократно.


  setBtnDwin(1, 0, 0, 4, "ON");
  setBtnDwin(2, 0, 350, 4, "OK");
  setSliderDwin(0, 30, 200, 50);
  setSliderDwin(1, 30, 250, 100);

  setBtnDwin(3, 420, 10, 1, "Test");
  setBtnDwin(4, 420, 100, 4, "Test");
  setBtnDwin(9, 420, 160, 1, " ");
  setBtnDwin(10, 490, 160, 1, " ");
  setBtnDwin(11, 560, 160, 1, " ");

  cutBuzzerDwin(5);  // Звук при включении
  delay(100);
  cutBuzzerDwin(15);  // длительность звучание от 0 до 255 млс
  delay(300);
  cutBuzzerDwin(5);
  delay(100);
}

void loop() {

  setBtnTouchDwin(1, 0, 0, 0);         // нажатия на сенсор. кнопку не выводит возвращает состояние 
  static bool last_bt1;
  if (stek_bool_bt[1] && !last_bt1) {
    last_bt1 = true;
    setSliderDwin(0, 30, 200, 40);
    setBtnDwin(1, 0, 0, 5, "ON");      // выводим графическое оформление 
    cutBuzzerDwin(5);                  // Звук при нажатии на кнопку
    Serial.println("On");
  } else if (!stek_bool_bt[1] && last_bt1) {
    last_bt1 = false;
    setSliderDwin(0, 30, 200, 10);
    setBtnDwin(0, 0, 0, 3, "OFF");     // выводим графическое оформление 
    Serial.println("Off");
  }

  setBtnActivDwin(2, 2, 0, 350, 3, "OK");
  digitalWrite(LED, stek_bool_bt[2]);

  setBtnActivDwin(3, 3, 420, 10, 1, "Test");
  setBtnActivDwin(4, 4, 420, 100, 4, "Test");
  setBtnActivDwin(5, 9, 420, 160, 1, " ");


  static uint8_t bril_n;

  static bool last_bt6;
  if (stek_bool_bt[6] && !last_bt6) {
    last_bt6 = true;
    bril_n++;
    cutBrightnessDwin(bril_n);  // регулировка яркости от 0 до 64
    cutBuzzerDwin(bril_n);      // звуковое уведомление  
    setSliderDwin(1, 30, 250, bril_n);
  } else if (!stek_bool_bt[6] && last_bt6) {
    last_bt6 = false;
  }

  static bool last_bt7;
  if (stek_bool_bt[7] && !last_bt7) {
    last_bt7 = true;
    bril_n--;
    cutBrightnessDwin(bril_n);  // регулировка яркости от 0 до 64
    cutBuzzerDwin(bril_n);      // звуковое уведомление  
    setSliderDwin(1, 30, 250, bril_n);
  } else if (!stek_bool_bt[7] && last_bt7) {
    last_bt7 = false;
  }
  setBtnActivDwin(6, 10, 490, 160, 1, " ");
  setBtnActivDwin(7, 11, 560, 160, 1, " ");

  ReadSerial();  // функция для обработки данных с дисплея.
}
