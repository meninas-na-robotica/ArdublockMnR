#include "arduinoDWINbox.h"  // подключаем функции конструктора

void setup() {
  // устанавливаем скорость передачи данных для последовательного порта
  dwinSerial.begin(115200);

  ClearDisplayDwin();  // Уаляем все с дисплея.
  //cutBuzzerDwin(50);
  setIconDwin(22, 5, 5);
  cutStringDwinActiv(17, 12, 3, 0, "Block 1");
  setIconDwin(23, 5, 60);
  cutStringDwinActiv(17, 72, 3, 1, "Block 2");

  setBtnDwin(3, 215, 5, 0, "Bizer");
  setBtnDwin(10, 425, 5, 0, "");
  setBtnDwin(11, 600, 5, 0, "");
  setIconDwin(15, 490, 5);
  setNumberDwin(10, 520, 10, 3, 5);

  setSliderDwin(0, 215, 70, 50);
  setBtnDwin(10, 425, 60, 0, "");
  setBtnDwin(11, 600, 60, 0, "");
  setIconDwin(15, 490, 60);
  setNumberDwin(11, 520, 65, 3, 5);
  delay(50);
  //setIconDwin(20, 5, 115);
  setBtnDwin(3, 5, 115, 4, "ON");
  setBtnDwin(3, 5, 175, 4, "ON");
  setBtnDwin(4, 5, 235, 4, "ON");
  setBtnDwin(5, 5, 305, 4, "ON");
  setBtnDwin(1, 5, 365, 4, "ON");

  setBtnDwin(3, 215, 115, 3, "ON");
  setBtnDwin(3, 215, 175, 2, "ON");
  setBtnDwin(4, 215, 235, 1, "ON");
  setBtnDwin(5, 215, 305, 5, "ON");

  setBtnDwin(7, 425, 115, 3, "ON");
  setBtnDwin(8, 425, 175, 2, "ON");
  setBtnDwin(9, 425, 235, 1, "ON");
  setBtnDwin(10, 425, 305, 5, "");
}

void loop() {

  setBtnActivDwin(20, 3, 215, 5, 6, "Buzzer");
  static bool last_bt20;
  if (stek_bool_bt[20] && !last_bt20) {
    last_bt20 = true;
    cutBuzzerDwin(5);

  } else if (!stek_bool_bt[20] && last_bt20) {
    last_bt20 = false;
  }
  /* 
 кнопки + и - 
*/
  setBtnActivDwin(21, 10, 425, 5, 0, "");
  static bool last_bt21;
  static uint8_t num_1;
  if (stek_bool_bt[21] && !last_bt21) {
    last_bt21 = true;
    num_1++;
    setIconDwin(15, 490, 5);
    setNumberDwin(num_1, 520, 10, 3, 5);
    cutBrightnessDwin(num_1);
  } else if (!stek_bool_bt[21] && last_bt21) {
    last_bt21 = false;
  }

  setBtnActivDwin(22, 11, 600, 5, 0, "");
  static bool last_bt22;
  if (stek_bool_bt[22] && !last_bt22) {
    last_bt22 = true;
    num_1--;
    setIconDwin(15, 490, 5);
    setNumberDwin(num_1, 520, 10, 3, 5);
    cutBrightnessDwin(num_1);
  } else if (!stek_bool_bt[22] && last_bt22) {
    last_bt22 = false;
  }
  /* 
 слайдер 
*/
  setBtnActivDwin(23, 10, 425, 60, 0, "");
  static bool last_bt23;
  static uint8_t num_2;
  if (stek_bool_bt[23] && !last_bt23) {
    last_bt23 = true;
    num_2++;
    setIconDwin(16, 490, 60);
    setNumberDwin(num_2, 520, 65, 3, 5);
    setSliderDwin(2, 215, 70, num_2);
  } else if (!stek_bool_bt[23] && last_bt23) {
    last_bt23 = false;
  }

  setBtnActivDwin(24, 11, 600, 60, 0, "");
  static bool last_bt24;
  if (stek_bool_bt[24] && !last_bt24) {
    last_bt24 = true;
    num_2--;
    setIconDwin(17, 490, 60);
    setNumberDwin(num_2, 520, 65, 3, 5);
    setSliderDwin(1, 215, 70, num_2);
  } else if (!stek_bool_bt[24] && last_bt24) {
    last_bt24 = false;
  }


  setSwichActivDwin(2, 3, 5, 115, 4, "OK");
  digitalWrite(13, stek_bool_sw[2]);

  setSwichActivDwin(3, 3, 5, 175, 5, "ON");
  setSwichActivDwin(4, 4, 5, 235, 1, "ON");
  setSwichActivDwin(5, 5, 5, 305, 2, "ON");
  setSwichActivDwin(6, 1, 5, 365, 3, "ON");

  setBtnActivDwin(7, 3, 215, 115, 3, "ON");
  setBtnActivDwin(8, 3, 215, 175, 2, "ON");
  setBtnActivDwin(9, 4, 215, 235, 1, "ON");
  setBtnActivDwin(10, 5, 215, 305, 5, "ON");

  setBtnActivDwin(11, 7, 425, 115, 3, "ON");
  setBtnActivDwin(12, 8, 425, 175, 2, "ON");
  setBtnActivDwin(13, 9, 425, 235, 1, "ON");
  setBtnActivDwin(14, 10, 425, 305, 5, "");
  ReadSerial();
}
