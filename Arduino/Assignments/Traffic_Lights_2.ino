int GREEN1 = 12, YELLOW1 = 8, RED1 = 4;
int GREEN2 = 13, YELLOW2 = 9, RED2 = 5;
int T1 = 3000, T2 = 2000;
void setup()
{
  pinMode(GREEN1, OUTPUT);
  pinMode(YELLOW1, OUTPUT);
  pinMode(RED1, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(YELLOW2, OUTPUT);
  pinMode(RED2, OUTPUT);
}

void loop()
{
  digitalWrite(GREEN1, HIGH);
  digitalWrite(RED2, HIGH);
  delay(T1);
  digitalWrite(GREEN1, LOW);
  digitalWrite(YELLOW1, HIGH);
  delay(T2);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(RED1, HIGH);
  digitalWrite(RED2, LOW);
  digitalWrite(GREEN2, HIGH);
  delay(T1);
  digitalWrite(GREEN2, LOW);
  digitalWrite(YELLOW2, HIGH);
  delay(T2);
  digitalWrite(YELLOW2, LOW);
  digitalWrite(RED1, LOW);
}