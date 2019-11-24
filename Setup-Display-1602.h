// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int LCDrs = A4, LCDen = A5, LCDd4 = A0, LCDd5 = A1, LCDd6 = A2, LCDd7 = A3;
LiquidCrystal lcd(LCDrs, LCDen, LCDd4, LCDd5, LCDd6, LCDd7);
