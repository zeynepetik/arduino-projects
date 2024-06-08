int ledGreen=2;
int ledYellow=3;
int ledRed=4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=2; i<=100; i++){
     if((i%2==0)&&(i%3==0)){
      Serial.print("number: ");
      Serial.println(i);
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledYellow, HIGH);
      delay(2000);
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledYellow, LOW);
    }
    if((i%2==0)&&(i%3!=0)){
      Serial.print("number: ");
      Serial.println(i);
      digitalWrite(ledGreen, HIGH);
      delay(500);
      digitalWrite(ledGreen, LOW);
      
    }
    if((i%3==0)&&(i%2!=0)){
      Serial.print("number: ");
      Serial.println(i);
      digitalWrite(ledYellow, HIGH);
      delay(500);
      digitalWrite(ledYellow, LOW);
    }
   
    if((i%2!=0)&&(i%3!=0)){
      Serial.print("number: ");
      Serial.println(i);
      digitalWrite(ledRed, HIGH);
      delay(500);
      digitalWrite(ledRed, LOW);
    }
  }
}
