#include <Arduino.h>
#include <Joystick.h>
#include <Keypad.h>

//colPins is OUTPUT
//rowPins is INPUT_PULLUP

#define NUMROWS 3
#define NUMCOLS 4

byte buttons[NUMROWS][NUMCOLS] = {
  {0,1,2,3},
  {4,5,6,7},
  {8,9,10,11}
};

byte rowPins[NUMROWS] = {14,15,16};
byte colPins[NUMCOLS] = {18,19,20,21};

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK,
  12, 0,
  false, false, false, false, false,
  false, false, false, false, false, false
);

Keypad keys = Keypad(
  makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS
);

void setup() {
  Serial.begin(115200);
  Joystick.begin();
}

void loop() {
  if (keys.getKeys()) {
    for (int i=0; i<LIST_MAX; i++) {
      if (keys.key[i].stateChanged) {
        char kchar = keys.key[i].kchar;
        switch (keys.key[i].kstate) {
          case PRESSED:
            Serial.print("Pressed btn");
          case HOLD:
            Joystick.setButton(kchar, 1);
            break;
          case RELEASED:
            Serial.print("Released btn");
          case IDLE:
            Joystick.setButton(kchar, 0);
            break;
        }
      }
    }
  }
}
