#include <Adafruit_NeoPixel.h>

int LED = 2;
int BUTTON = 3;
int LED_NUM;
int RED;
int GREEN;
int BLUE;
int BRIGHT;
int BUTTON_STATE = 1;
int BUTTON_HOLD_STATE = 1; 
bool BUTTON_HOLD_FLAG= true; 
bool BUTTON_PRESS_FLAG; 
bool TOKEN_PRESS = true; 
bool TOKEN_HOLD = true;
bool TOKEN_UP = true;
bool TOKEN_DOWN = true;
unsigned long DEBOUNCE;
#define debouncetime 200
#define HOLD_TIME 1000
unsigned long next_delay;
unsigned long button_start; 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(45, LED, NEO_KHZ800 + NEO_GRBW); //Sets how many LEDs you have

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); 
  //attachInterrupt(0, BUTTON_PRESS, LOW);
  Serial.begin(9600);
  LED_NUM = 0;
  strip.begin();
  strip.setBrightness(255); 
  strip.setPixelColor(0, 255, 0, 0);
  strip.show(); // Initialize all pixels to 'off'
  next_delay = millis()+1000;
  DEBOUNCE = millis();   

}

void loop() {
 //Serial.println(TOKEN_PRESS);
//Serial.print("Button state = "); 
//Serial.println(BUTTON_STATE);
//Serial.print("Button hold =");
//Serial.println(BUTTON_HOLD_STATE);


  BUTTON_PRESS();


 

  switch (BUTTON_STATE) {  // Turns LEDs on or OFF 
    case 1:
      switch (BUTTON_HOLD_STATE) {
        case 1: //RED
          COLOR_LED_DOWN(255,0,0,0,255);
          break;
        case 2: //WHITE
          COLOR_LED_DOWN(0,0,0,255,55);
          break; 
        case 3: 
          COLOR_LED_DOWN(0,0,0,255,255); 
          break;
        default:
          BUTTON_HOLD_STATE = 1;
          break;
      }
      break;
    case 2:
      COLOR_LED_UP(0,0,0,0,100); //Off
      break;
    default:
      BUTTON_STATE = 1; 
      TOKEN_UP = true; 
      TOKEN_DOWN = true; 
      break;
}
  }


void BUTTON_PRESS() {

  
  if(digitalRead(BUTTON) == HIGH)
  { 
    //Serial.println(BUTTON_PRESS_FLAG);
    //restart timer when button is not press
    button_start = millis();
    BUTTON_HOLD_FLAG= true; 
    //BUTTON_PRESS_FLAG= true;
    if(BUTTON_PRESS_FLAG)
    {
      BUTTON_STATE++;
      BUTTON_PRESS_FLAG= false; 
      delay(500);
    }
  }
  
  if(digitalRead(BUTTON) == LOW)
  {
    if(BUTTON_HOLD_FLAG)
    {
      BUTTON_PRESS_FLAG= true;  
      Serial.println("hello");
    }
    
    if((millis() > (button_start + HOLD_TIME)) && BUTTON_HOLD_FLAG)
    {
      BUTTON_HOLD_STATE++;
      TOKEN_DOWN = true; 
      BUTTON_HOLD_FLAG= false;
      BUTTON_PRESS_FLAG= false;
      Serial.println(BUTTON_HOLD_STATE);
       delay(500);
    }
  }
}
 

void COLOR_LED_UP(int RED, int GREEN, int BLUE, int WHITE, int BRIGHT) {
 
  strip.setBrightness(BRIGHT);
  if(TOKEN_UP == true){
    for(int i =0; i < 45;){
      if (next_delay < millis()){
        strip.setPixelColor(i,RED,GREEN,BLUE,WHITE); 
        strip.show();
         i++;
        next_delay = millis() + 25; 
      }
    }
    TOKEN_UP = false;
  }
}
void COLOR_LED_DOWN(int RED, int GREEN, int BLUE, int WHITE, int BRIGHT) {
  strip.setBrightness(BRIGHT);
  if(TOKEN_DOWN == true){ 
    for (int i=45; i > 0;){
      if (next_delay < millis()){
        i--;
        strip.setPixelColor(i,RED,GREEN,BLUE,WHITE); 
        strip.show();
        next_delay = millis() + 25; 
        Serial.println("here");
        }
      }
    }
  TOKEN_DOWN = false;
}

void COLOR_LED_OI(int RED, int GREEN, int BLUE, int WHITE, int BRIGHT) {
  strip.setBrightness(BRIGHT);
  int j= 45; 
  for (int i=0; i <= 23; ){ 
    if(next_delay < millis()){
      strip.setPixelColor(i, RED,GREEN, BLUE, WHITE);
      strip.setPixelColor(j, RED,GREEN, BLUE, WHITE);
      strip.show(); 
      next_delay = millis() + 25;
      i++;
      j--;
    }
  }
}

void COLOR_LED_IO(int RED, int GREEN, int BLUE, int WHITE, int BRIGHT) {
  strip.setBrightness(BRIGHT);
  int j= 23; 
  for (int i=22; i <= 45; ){ 
    if(next_delay < millis()){
      strip.setPixelColor(i, RED,GREEN, BLUE, WHITE);
      strip.setPixelColor(j, RED,GREEN, BLUE, WHITE);
      strip.show(); 
      next_delay = millis() + 25;
      i++;
      j--;
    }
  }
}
/*notes
Press button to turn on and off 
hold button to toggle between RED and WHITE 1 sec hold
each button will increase interval ++ 
case 1: off
case 2: on (default to red)
case 3: white
*/

