////////////////////////////////////////////
//  Keypad Setup
////////////////////////////////////////////
#include <Keypad.h>

#ifdef KeyPadNano
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//  define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
/* Arduino Pro Mini */
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
#endif

#ifdef KeyPadUNO
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//  define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
/* Arduino Pro Mini */
byte rowPins[ROWS] = {2, 3, 5, 6};  //connect to the row pinouts of the keypad
                                    //  Pin 4 is used by the SD card
byte colPins[COLS] = {7, 8, 9};     //connect to the column pinouts of the keypad
#endif

//  initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
