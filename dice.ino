int buttonPin=8;
int ledPin=13;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  int dice_result= random(1,7);
  if(digitalRead(buttonPin)==HIGH){

    Serial.print("dice result: ");
    Serial.println(dice_result);
  }
  //eğer led falan yoksa
  Serial.print("dice result: ");
  Serial.println(dice_result);
  digitalWrite(ledPin, LOW);
  delay(200);

}
