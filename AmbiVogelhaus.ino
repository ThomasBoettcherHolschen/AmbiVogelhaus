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
int dataPin = 12;
int clockPin = 13;
char lastKey;

Adafruit_WS2801 strip = Adafruit_WS2801(50, dataPin, clockPin);

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show();
  colorSwitch(Color(255, 255, 255));  // white fill
}

void loop() {
  checkKey();
  delay(100);
}

void checkKey(){
  char key = keypad.getKey();
  if (key != NO_KEY){
    lastKey = key;
    PerformAction(key);
  }
}

void PerformAction(char key){
  switch (key) {
    case '1':
      colorWipe(Color(255, 0, 0), 50);  // red fill
      break;
    case '2':
      colorWipe(Color(0, 255, 0), 50);  // green fill
      break;
    case '3':
      colorWipe(Color(0, 0, 255), 50);  // blue fill
      break;        
    case '4':
      colorSwitch(Color(255, 0, 0));  // fast Red
      break;
    case '5':
      colorSwitch(Color(0, 255, 0));  // fast Green
      break;
    case '6':
      colorSwitch(Color(0, 0, 255));  // Fast Blue
      break;
    case '7':
      colorRun(Color(255, 0, 0), 50);  // blue fill
      break;                
    case '8':
      colorRun(Color(0, 255, 0), 50);  // blue fill
      break;        
    case '9':
      colorRun(Color(0, 0, 255), 50);  // blue fill
      break;        
    case '0':
      colorSwitch(Color(255, 255, 255));  // white fill
      break;        
    case '#':
      rainbow(20);
      break;        
    case '*':
      rainbowCycle(20);
      break;        
    default:
      colorSwitch(Color(255, 255, 255));  // white fill
      break;
  }  
}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
    char key = keypad.getKey();
    if (key != NO_KEY){
      if(key != lastKey){
        break;
      }
    }
  }
}

void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 256 * 5; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
    char key = keypad.getKey();
    if (key != NO_KEY){
      if(key != lastKey){
        break;
      }
    }    
  }
}

void colorSwitch(uint32_t c) {
  int i;
 
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
  }
  strip.show();
}


void colorWipe(uint32_t c, uint8_t wait) {
  int i;
 
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorRun(uint32_t c, uint8_t wait) {
  int i;
 
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      if(i != 0)
      {
        strip.setPixelColor(i-1, 0);  
      }
      strip.show();
      delay(wait);
  }
  colorSwitch(0);
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

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
