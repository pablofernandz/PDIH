int animationSpeed = 0;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  animationSpeed = 50;

  digitalWrite(13, HIGH);
  delay(animationSpeed); 
  digitalWrite(13, LOW);
  delay(animationSpeed);

  digitalWrite(12, HIGH);
  delay(animationSpeed); 
  digitalWrite(12, LOW);
  delay(animationSpeed);

  digitalWrite(11, HIGH);
  delay(animationSpeed); 
  digitalWrite(11, LOW);
  delay(animationSpeed);

  digitalWrite(10, HIGH);
  delay(animationSpeed); 
  digitalWrite(10, LOW);
  delay(animationSpeed);

  digitalWrite(9, HIGH);
  delay(animationSpeed); 
  digitalWrite(9, LOW);
  delay(animationSpeed);

  digitalWrite(10, HIGH);
  delay(animationSpeed); 
  digitalWrite(10, LOW);
  delay(animationSpeed);

  digitalWrite(11, HIGH);
  delay(animationSpeed); 
  digitalWrite(11, LOW);
  delay(animationSpeed);

  digitalWrite(12, HIGH);
  delay(animationSpeed); 
  digitalWrite(12, LOW);
  delay(animationSpeed);

}