/*
   Код и графические элементы разработаны командой https://arduino-tex.ru/
   Проекты на Arduino https://portal-pk.ru/page-17/proekty-na-arduino.html
   Проекты на ESP https://arduino-tex.ru/menu/10/11/proekty-na-esp8266-esp32.html
*/
#include <SoftwareSerial.h>

#define DEBUG 0  // Отладка: 1 - вкл.  0 - выкл.
SoftwareSerial dwinSerial(10, 11); // RX, TX

static bool stek_bool_bt[51];
static bool stek_bool_sw[51];

const uint16_t array_objects[][5] = { {1, 0, 0, 400, 100}, {1, 0, 100, 400, 100}, {1, 0, 200, 400, 100}, {1, 0, 300, 400, 100}, {1, 0, 400, 400, 100}, {1, 0, 500, 400, 100}, {1, 400, 0, 200, 50},  {1, 400, 50, 200, 50}, {1, 400, 100, 200, 50}, {1, 400, 150, 200, 50}, {1, 400, 200, 200, 50}, {1, 400, 250, 200, 50}, {1, 600, 00, 100, 50}, {1, 600, 50, 100, 50}, {1, 600, 100, 100, 50}, {1, 600, 150, 100, 50}, {1, 600, 200, 100, 50}, {1, 600, 250, 100, 50}, {3, 0, 0, 400, 100}, {3, 0, 100, 400, 100}, {3, 0, 200, 400, 100}, {3, 400, 0, 200, 50}, {3, 400, 50, 200, 50}, {3, 400, 100, 200, 50}, {3, 600, 00, 100, 50}, {3, 600, 50, 100, 50}, {3, 600, 100, 100, 50}, {2, 0, 0, 50, 50}, {2, 0, 50, 50, 50}, {2, 50, 0, 50, 50}, {2, 50, 50, 50, 50}, {2, 100, 0, 50, 50}, {2, 100, 50, 50, 50}, {2, 150, 0, 50, 50}, {2, 150, 50, 50, 50}, {2, 200, 0, 50, 50}, {2, 200, 50, 50, 50}, {2, 250, 0, 50, 50}, {2, 250, 50, 50, 50}, {2, 300, 0, 50, 50}, {2, 300, 50, 50, 50}, {2, 350, 0, 50, 50}, {2, 350, 50, 50, 50}, {2, 400, 0, 50, 50}, {2, 400, 50, 50, 50}, {2, 450, 0, 50, 50}, {2, 450, 50, 50, 50}, {3, 400, 200, 200, 25}, {3, 400, 225, 200, 25}, {3, 400, 250, 200, 25}, {3, 400, 275, 200, 25}, };

const uint8_t array_btn_active[][2] = {{0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}, {10, 11}, {12, 13}, {14, 15}, {16, 17}, {27, 28}, {29, 30}, {31, 32}, {33, 34}, {35, 36}, {37, 38}, {39, 40}, {41, 42}, {43, 44}, {46, 46},};

const uint8_t array_slider[3] = {47, 48, 49,};
uint8_t num_colors_dwin = 8; 
const uint16_t colors_dwin[] = {0xF800, 0x001F, 0x07E0, 0xFFFF, 0x0000, 0xF7E1, 0xFD22, 0xADF4};

byte Buffer[10];        
byte Buffer_Len = 0;
bool flag_dwin = false;         

uint16_t x_activ_dwin;  
uint16_t y_activ_dwin;       
uint16_t x_passiv_dwin;     
uint16_t y_passiv_dwin;       
bool flag_sensor_activ = false; 

void ReadSerial()
{
  if (dwinSerial.available())
  {
    Buffer[Buffer_Len] = dwinSerial.read();

    Buffer_Len++;
    flag_dwin = true;
  }
  else
  {
    if (flag_dwin)
    {
      if (Buffer[0] == 0XAA ) {
        if (Buffer[1] == 0X73) { 
          x_activ_dwin = Buffer[2] << 8 | Buffer[3];
          y_activ_dwin = Buffer[4] << 8 | Buffer[5];
          flag_sensor_activ = true;
        }
        if (Buffer[1] == 0X72) { 
          x_passiv_dwin = Buffer[2] << 8 | Buffer[3];
          y_passiv_dwin = Buffer[4] << 8 | Buffer[5];
          flag_sensor_activ = false;
        }
      }
      Buffer_Len = 0; 
      flag_dwin = false;
    }
  }
}

void ClearDisplayDwin()
{
  byte b_cut[7] = {0XAA, 0X70, 0X00, 0XCC, 0X33, 0XC3, 0X3C};  
  dwinSerial.write(b_cut, 7);
}

void cutIconDwin(byte pic_id, uint16_t Xs, uint16_t Ys, uint16_t Xe, uint16_t Ye, uint16_t X, uint16_t Y)
{
  byte b_cut[19] = {0XAA, 0X71, pic_id, Xs >> 8, Xs, Ys >> 8, Ys, Xe >> 8, Xe, Ye >> 8, Ye, X >> 8, X, Y >> 8, Y, 0XCC, 0X33, 0XC3, 0X3C};
  dwinSerial.write(b_cut, 19);
}


void convert(const char* in)
{
  uint32_t codepoint = 0;
  while (*in != 0)
  {
    uint8_t ch = (uint8_t) (*in);
    if (ch <= 0x7f)
      codepoint = ch;
    else if (ch <= 0xbf)
      codepoint = (codepoint << 6) | (ch & 0x3f);
    else if (ch <= 0xdf)
      codepoint = ch & 0x1f;
    else if (ch <= 0xef)
      codepoint = ch & 0x0f;
    else
      codepoint = ch & 0x07;
    ++in;
    if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff))
    {
      if (codepoint <= 255)
      {
        dwinSerial.write( (char) codepoint);
      }
      else
      {
        if (codepoint > 0x400)
          dwinSerial.write((char) (codepoint - 0x350));
      }
    }
  }
}

void cutStringDwinActiv(uint16_t X, uint16_t Y, byte Dots, uint16_t color_565, String txt )
{
  if (Dots < 3) Dots = 3;
  else if (Dots > 8) Dots = 8;
  if (color_565 < 0) color_565 = 0;
  else if (color_565 > num_colors_dwin) color_565 = num_colors_dwin;
  uint16_t FC = colors_dwin[color_565];
  const char *ch = new char[txt.length()];
  ch = txt.c_str();
  byte b_text[13] = {0XAA, 0X98, X >> 8, X, Y >> 8, Y, 0X04, 0X31, Dots, FC >> 8, FC, 0X00, 0X1F};
  dwinSerial.write(b_text, 13);
  convert(ch); 
  byte b_text_c[4] = {0XCC, 0X33, 0XC3, 0X3C};
  dwinSerial.write(b_text_c, 4);
}

void setIconDwin(byte pic_id, uint16_t X, uint16_t Y)
{
  cutIconDwin(array_objects[pic_id][0], array_objects[pic_id][1], array_objects[pic_id][2], array_objects[pic_id][1] + array_objects[pic_id][3], array_objects[pic_id][2] + array_objects[pic_id][4], X, Y);
}

void setSwichActivDwin(byte id, byte btn_id, uint16_t X, uint16_t Y, uint16_t color_565, String txt)
{
  static bool flag_element_activ;

  if (!flag_element_activ && flag_sensor_activ)
  {
    if (x_activ_dwin > X && x_activ_dwin < (X + array_objects[array_btn_active[btn_id][0]][3]) && y_activ_dwin > Y && y_activ_dwin < (Y + array_objects[array_btn_active[btn_id][0]][4]))
    {
      stek_bool_sw[id] = !stek_bool_sw[id];
      byte pic_id = array_btn_active[btn_id][stek_bool_sw[id]];
      setIconDwin(pic_id, X, Y);                
      if (btn_id < 3)
        cutStringDwinActiv(X + 15, Y + 25, 6, color_565, txt);    
      else if (btn_id < 6)
        cutStringDwinActiv(X + 7, Y + 5, 4, color_565, txt);    
      else if (btn_id < 9)
        cutStringDwinActiv(X + 7, Y + 7, 3, color_565, txt);    
      flag_element_activ = true;
    }
  }
  else if (flag_element_activ && !flag_sensor_activ)
  {
    flag_element_activ = false; 
  }
}

void setSliderDwin(uint8_t pic_id, uint16_t X, uint16_t Y, uint8_t percent )
{
  if (percent < 0)
    percent = 0;
  if (percent > 100)
    percent = 100;
  cutIconDwin(array_objects[array_slider[pic_id]][0], array_objects[array_slider[pic_id]][1] + array_objects[array_slider[pic_id]][3] - percent * 2, array_objects[array_slider[pic_id]][2],  array_objects[array_slider[pic_id]][1] + array_objects[array_slider[pic_id]][3], array_objects[array_slider[pic_id]][2] + array_objects[array_slider[pic_id]][4], X, Y);
  cutIconDwin(array_objects[50][0], array_objects[50][1], array_objects[50][2], array_objects[50][1] + array_objects[50][3] - percent * 2, array_objects[50][2] + array_objects[50][4], X + percent * 2, Y);

}

void setNumberDwin(int number, uint16_t X, uint16_t Y, uint16_t color_565, uint8_t size_n )
{
  String txt = String(number);
  cutStringDwinActiv(X, Y, size_n, color_565, txt);
}

void setBtnDwin(byte btn_id, uint16_t X, uint16_t Y, uint16_t color_565, String txt)
{
  byte pic_id = array_btn_active[btn_id][0];  
  setIconDwin(pic_id, X, Y);             
  if (btn_id < 3)
    cutStringDwinActiv(X + 15, Y + 25, 6, color_565, txt);   
  else if (btn_id < 6)
    cutStringDwinActiv(X + 7, Y + 5, 4, color_565, txt);   
  else if (btn_id < 9)
    cutStringDwinActiv(X + 7, Y + 7, 3, color_565, txt);  
}

void setBtnActivDwin(byte id, byte btn_id, uint16_t X, uint16_t Y, uint16_t color_565, String txt)
{
  static bool flag_element_activ; 

  if (!flag_element_activ && flag_sensor_activ)
  {
    if (x_activ_dwin > X && x_activ_dwin < (X + array_objects[array_btn_active[btn_id][0]][3]) && y_activ_dwin > Y && y_activ_dwin < (Y + array_objects[array_btn_active[btn_id][0]][4]))
    {
      byte pic_id = array_btn_active[btn_id][1];  
      setIconDwin(pic_id, X, Y);                  
      if (btn_id < 3)
        cutStringDwinActiv(X + 15, Y + 25, 6, color_565, txt);   
      else if (btn_id < 6)
        cutStringDwinActiv(X + 7, Y + 5, 4, color_565, txt);  
      else if (btn_id < 9)
        cutStringDwinActiv(X + 7, Y + 7, 3, color_565, txt);    
      stek_bool_bt[id] = true;
      flag_element_activ = true; 
    }
  }
  else if (flag_element_activ && !flag_sensor_activ)
  {
    if (x_activ_dwin > X && x_activ_dwin < (X + array_objects[array_btn_active[btn_id][0]][3]) && y_activ_dwin > Y && y_activ_dwin < (Y + array_objects[array_btn_active[btn_id][0]][4]))
    {
      byte pic_id = array_btn_active[btn_id][0]; 
      setIconDwin(pic_id, X, Y);                 
      if (btn_id < 3)
        cutStringDwinActiv(X + 15, Y + 25, 6, color_565, txt);    
      else if (btn_id < 6)
        cutStringDwinActiv(X + 7, Y + 5, 4, color_565, txt);   
      else if (btn_id < 9)
        cutStringDwinActiv(X + 7, Y + 7, 3, color_565, txt);  
      stek_bool_bt[id] = false;
      flag_element_activ = false; 
    }
  }

}

void cutBrightnessDwin(uint8_t num_pwm)
{
  if (num_pwm < 0) num_pwm = 0;
  else  if (num_pwm > 64) num_pwm = 64;
  byte b_cut[7] = {0XAA, 0X5F, num_pwm, 0XCC, 0X33, 0XC3, 0X3C};
  dwinSerial.write(b_cut, 7);
}

void setBtnTouchDwin(byte id, byte btn_id, uint16_t X, uint16_t Y)
{
  static bool flag_element_activ; 
  if (!flag_element_activ && flag_sensor_activ)
  {
    if (x_activ_dwin > X && x_activ_dwin < (X + array_objects[array_btn_active[btn_id][0]][3]) && y_activ_dwin > Y && y_activ_dwin < (Y + array_objects[array_btn_active[btn_id][0]][4]))
    {
      stek_bool_bt[id] = true;
      flag_element_activ = true; 
    }
  }
  else if (flag_element_activ && !flag_sensor_activ)
  {
    if (x_activ_dwin > X && x_activ_dwin < (X + array_objects[array_btn_active[btn_id][0]][3]) && y_activ_dwin > Y && y_activ_dwin < (Y + array_objects[array_btn_active[btn_id][0]][4]))
    {
      byte pic_id = array_btn_active[btn_id][0];  
      setIconDwin(pic_id, X, Y);                
      stek_bool_bt[id] = false;
      flag_element_activ = false; 
    }
  }
}

void cutBuzzerDwin(uint8_t time_s)
{
  byte b_cut[7] = {0XAA, 0X79, time_s, 0XCC, 0X33, 0XC3, 0X3C};
  dwinSerial.write(b_cut, 7);
}
