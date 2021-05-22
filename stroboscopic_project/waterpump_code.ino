#define EN1 3
#define EN2 4
#define WTP 5

int speed_ctl = 120;
#define pumpPower 150
#define potWTP A3

void setup() {
  Serial.begin(9600);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(WTP, OUTPUT);
  pinMode(potWTP, INPUT);

  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(WTP, pumpPower);
}

void loop() {
  int wtd = analogRead(potWTP)/2;

  analogWrite(WTP, pumpPower);
  delay(wtd);
  analogWrite(WTP, 0);
  delay(wtd);

  Serial.println(analogRead(potWTP));
}
