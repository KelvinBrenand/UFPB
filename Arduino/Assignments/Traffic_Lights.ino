int GREEN =12, YELLOW = 8, RED= 4;
int GREEN_TIME = 3000, YELLOW_TIME = 2000, RED_TIME = 3000;
void setup()
{
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
}

void loop()
{
  digitalWrite(GREEN, HIGH);
  delay(GREEN_TIME);
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(YELLOW_TIME);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, HIGH);
  delay(RED_TIME);
  digitalWrite(RED, LOW);
}