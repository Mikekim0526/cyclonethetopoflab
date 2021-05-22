#include <FastLED.h>

#define LED_PIN     13
#define NUM_LEDS    22

#define RED_PIN     10
#define BLUE_PIN    11
#define GREEN_PIN   12

#define EN1 3
#define EN2 4
#define WTP 5

#define pumpPower 150
#define potWTP A3


#define COLOR       { 255, 255, 0 }
#define pot A1

struct RGBval{
  int r;
  int g;
  int b;
};

int inputNum = 0;
int loopDelay = 0;

unsigned long time_;
int anal;
int wtd;
bool turnON = true;

void ON(int n, RGBval col);
void OFF(int n);

CRGB leds[NUM_LEDS];

//  pre declaration ===============================================================

void setup() {
  
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  pinMode(pot, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(WTP, OUTPUT);
  pinMode(potWTP, INPUT);

  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(WTP, pumpPower);
  
  Serial.begin(9600);
  
}

//  main LOOP context ===============================================================

void loop() {

  time_ = micros();
  loopDelay += 1;
  
  wtd = analogRead(potWTP)/2;
  anal = map(analogRead(pot), 0, 1023, 0, 10);

  if (Serial.available()) {
    inputNum = Serial.read() - '0';
    Serial.println(inputNum);
  }
  
  if(time_ % inputNum == 0)
  {
    analogWrite(RED_PIN, 255);
    analogWrite(GREEN_PIN, 255);
    analogWrite(BLUE_PIN, 255);
  }
  else
  {
    analogWrite(RED_PIN, 0);
    analogWrite(GREEN_PIN, 0);
    analogWrite(BLUE_PIN, 0);
  }

  if(loopDelay >= wtd)
  {
    if(turnON)
    {
      analogWrite(WTP, pumpPower);
      turnON = false;
    }
    else
    {
      turnON = true;
    }

    loopDelay = 0;
  }
  //Serial.println(anal);
  //Serial.println(analogRead(potWTP));
  
}

//  post declaration ===============================================================

void ON(int n, RGBval col)
{
  leds[n] = CRGB(col.r, col.g, col.b);
  FastLED.show();
}

void OFF(int n)
{
  leds[n] = CRGB(0, 0, 0);
  FastLED.show();
}
