#include <Adafruit_WS2801.h>
#include <Keypad.h>
#include <Key.h>

// Keyboard Definition
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


// LED Definition
int dataPin = 13;
int clockPin = 12;

Adafruit_WS2801 strip = Adafruit_WS2801(50, dataPin, clockPin);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();

  colorWipe(Color(255, 0, 0), 50);  // red fill
  colorWipe(Color(0, 255, 0), 50);  // green fill
  colorWipe(Color(0, 0, 255), 50);  // blue fill
  
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY){
    Serial.println(key);
  }



}

void colorWipe(uint32_t c, uint8_t wait) {
  int i;
 
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */
// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}
