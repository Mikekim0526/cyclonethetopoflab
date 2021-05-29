#include <FastLED.h>

#define LED_PIN     13  // 단일 입력 LED 사용시 쓰는 pin
#define NUM_LEDS    22  // 단일 입력 LED 사용 개수

#define RED_PIN     10  // RGB pin 설정
#define BLUE_PIN    11
#define GREEN_PIN   1
#define pumpPower 106   //  
#define potWTP A3


#define COLOR       { 255, 255, 0 }
#define pot A12

#define EN1 3
#define EN2 4
#define WTP 5
#define EN3 7
#define EN4 8


struct RGBval {
  int r;
  int g;
  int b;
};

int inputNum = 0;
int CinputNum = 0;
int loopDelay = 0;

unsigned long time_;
int anl;
int wtd;
bool turnON = true;

void ON(int n, RGBval col); // FastLed 함수 불편해서 ON/OFF로 짜놨음,, 지금은 안씀
void OFF(int n);

CRGB leds[NUM_LEDS];

//  pre declaration ===============================================================

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  // 각각의 pinMode 설정하는 부분 INPUT과 OUTPUT,,
  pinMode(pot, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(EN4, OUTPUT);
  pinMode(WTP, OUTPUT);
  pinMode(potWTP, INPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);

  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, HIGH);
  analogWrite(WTP, pumpPower);

  // 값 확인하는 serial 모니터 시작 설정
  Serial.begin(9600);

}

//  main LOOP context ===============================================================

void loop() {

  time_ = millis(); // 밀리세컨드 단위로 값을 가져옴 -> 이따가 켜지고 꺼지는 조건에 사용
  loopDelay += 1;   // 얘는 따로 모터의 딜레이를 설정하기 위한 친구

  // time_은 LED, loopDelay는 모터를 컨트롤 하는 용도

  //wtd = analogRead(potWTP) / 2;
  wtd = 0;
  // water delay : 모터의 딜레이를 가져오는데, 조절 노즐로 값을 받아옴

  anl = map(analogRead(pot), 0, 1023, 0, 10);
  // LED의 깜빡임을 조절하는 친구인데 지금은 연결을 안해서 사용 X

  analogWrite(RED_PIN, 0);
  // Serial 모니터에서 입력한 값을 받아오고 그걸 사용해서 LED의 딜레이를 조절
  if (Serial.available()) {
    inputNum = Serial.read() - '0';
    inputNum = CinputNum + (inputNum-5);
    Serial.println(inputNum);
    CinputNum= inputNum;
  }

  // millis로 받아온 밀리세컨드를 modulus 연산을 한 결과가 0일 경우 켜지고, 0이 아닌 나머지일 경우 꺼짐
  // 즉 inputNum(입력해둔 값)이 3이면 3의 배수인 밀리초에만 켜짐,, 극히 세밀한 단위로 하기위해 사용
  if (time_ % inputNum == 0)
  {
    // 키는 친구들
    //    analogWrite(RED_PIN, 255);
    //    analogWrite(GREEN_PIN, 255);
    //    analogWrite(BLUE_PIN, 255);
    digitalWrite(9, HIGH);
  }
  else
  {
    // 끄는 친구들
    //    analogWrite(RED_PIN, 0);
    //    analogWrite(GREEN_PIN, 0);
    //    analogWrite(BLUE_PIN, 0);
    digitalWrite(9, LOW);
  }

  // 모터를 돌리는 loopDelay의 값이 정해둔 wtd보다 커졌을때 키고 킨 다음엔 다시 끔 (주기마다 툭.. 툭.. 툭.. 켜짐)
  if (loopDelay >= wtd)
  {
    if (turnON)
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


  //Serial.println(anl);
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
