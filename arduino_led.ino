int redPin=2;//ledlerin bağlanacağı yer
int yellowPin=3;
int greenPin=4;
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  
}

void loop() {
 digitalWrite(redPin, HIGH);
 delay(3000);
digitalWrite(redPin, LOW);

 digitalWrite(grenPin, HIGH);
 delay(2000);
 digitalWRite(greenPin, LOW);

 digitalWrite(yellowPin, HIGH);
 delay(1000);
 digitalWrite(yellowPin, LOW);
}
