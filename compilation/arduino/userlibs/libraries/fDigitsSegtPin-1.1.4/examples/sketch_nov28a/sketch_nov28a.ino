#include <fDigitsSegtPin.h>

fDigitsSegtPin Display(10, 9, 13, 8, 12, 3, 7, 4, 5, 11, 6, 2);

void setup() {
    Display.begin();
    Display.doPrint_lastDot = 1;
    Display.doPrint_firstZero = 1;
    Display.doReport_overRange = 0;
}

void loop() {
    Display.print(1234);
}
