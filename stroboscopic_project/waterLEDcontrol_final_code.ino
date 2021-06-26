#define pumpPower 85

#define JOYSTICK_X A1
#define JOYSTICK_Y A2
#define JOYSTICK_FUNCTION A3

#define WATER_PUMP_PWM 3
#define WATER_PUMP_INPUT1 5
#define WATER_PUMP_INPUT2 6 // 모터 pwm핀

#define LED_PWM 9
#define LED_INPUT3 10
#define LED_INPUT4 11

int inputNum = 0;
int CinputNum = 0;

int PUMP_DELAY = 0;
int DISPLAY_DELAY = 0;

unsigned long time_;
int PUMP_DELAY_THRESHOLD;
bool MOTOR_TURN_ON = true;
bool LCD_TURN_ON = true;

//  pre declaration ===============================================================

void setup() {

  // 각각의 pinMode 설정하는 부분 INPUT과 OUTPUT,,

  pinMode(WATER_PUMP_PWM, OUTPUT);
  pinMode(WATER_PUMP_INPUT1, OUTPUT);
  pinMode(WATER_PUMP_INPUT2, OUTPUT);

  pinMode(LED_PWM, OUTPUT);
  pinMode(LED_INPUT3, OUTPUT);
  pinMode(LED_INPUT4, OUTPUT);
  pinMode(LED_PWM, OUTPUT);
  digitalWrite(LED_PWM, HIGH);

  digitalWrite(WATER_PUMP_INPUT1, HIGH);
  digitalWrite(WATER_PUMP_INPUT2, LOW);
  digitalWrite(LED_INPUT3, HIGH);
  digitalWrite(LED_INPUT4, HIGH);
  analogWrite(WATER_PUMP_PWM, pumpPower);

  inputNum = 120;

  // 값 확인하는 serial 모니터 시작 설정
  Serial.begin(9600);

}


int joyConverter(int x, int nowValue)
{
   if(x < -80)
   {
     if(nowValue == 0)
     {
       return 0; 
     }

     return -1;
   }
   else if (x > 80)
   {
     return 1;
   }

   return 0;
}


//  main LOOP context ===============================================================

void loop() {

  int Jox = map(analogRead(JOYSTICK_X), 0, 1023, -100, 100);
  int Joy = map(analogRead(JOYSTICK_Y), 0, 1023, -100, 100);
  
  time_ = millis();  // 밀리세컨드 단위로 값을 가져옴 -> 이따가 켜지고 꺼지는 조건에 사용
  PUMP_DELAY += 1;
  DISPLAY_DELAY += 1;

  // PUMP_DELAY_THRESHOLD = analogRead(potWTP) / 2;
  PUMP_DELAY_THRESHOLD = 0;

  digitalWrite(LED_PWM, HIGH);


  if (time_ % (inputNum/10) == 0)
  {
    digitalWrite(LED_INPUT3, LOW);
  }
  else
  {
    digitalWrite(LED_INPUT3, HIGH);
  }
  

  if(DISPLAY_DELAY >= 500)
  {
    if(LCD_TURN_ON)
    {
      LCD_TURN_ON = false;
    }
    else
    {
      LCD_TURN_ON = true;
    }
  }
  
  if (LCD_TURN_ON)
  {
    inputNum += joyConverter(Jox, inputNum);
    
    if(inputNum == 9)
    {

      //lcd.clear();
    }
    
    DISPLAY_DELAY = 0;
  }

  if (PUMP_DELAY >= PUMP_DELAY_THRESHOLD)
  {
    if (MOTOR_TURN_ON)
    {
      analogWrite(WATER_PUMP_PWM, pumpPower);
      MOTOR_TURN_ON = false;
    }
    else
    {
      MOTOR_TURN_ON = true;
    }

    PUMP_DELAY = 0;
  }


  //Serial.println(anl);
  //Serial.println(analogRead(potWTP));

}
