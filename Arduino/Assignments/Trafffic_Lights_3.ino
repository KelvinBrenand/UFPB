int G1 = 2, Y1 = 3, R1 = 4, G2 = 5, R2 = 6, BUZZER = 8;
int T1 = 3000, T2 = 2000;
void setup()
{
  pinMode(G1, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  digitalWrite(G1, HIGH);
  digitalWrite(R2, HIGH);
  delay(T1);
  digitalWrite(G1, LOW);
  digitalWrite(Y1, HIGH);
  delay(T2);
  digitalWrite(Y1, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(G2, HIGH);
  tone(BUZZER, 240);
  delay(T1);
  digitalWrite(R1, LOW);
  digitalWrite(G2, LOW);
  noTone(BUZZER);
}