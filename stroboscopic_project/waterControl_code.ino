#define EN1 3
#define EN2 4
#define WTP 5
#define potWTP A3
// digital output pins to control waterpump motor,
// analog input pin for potentiometer to control waterpump power

#define pumpPower 150           // default power of waterpump motor, you can change this value

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
