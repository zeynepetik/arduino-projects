int ledPin=13;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int flag=0;
    for(int i=2; i<=13; i++){
      for(int j=3; j<13; j++){
        if(i%j!=0){
          flag=1;
          break;
        }
        
        if(flag==1){
          digitalWrite(ledPin, HIGH);
          delay(3000);
          Serial.print("prime: ");
        }
          else{
            Serial.print("number: ");
            digitalWrite(ledPin, LOW);
            delay(1000);
          }
          
        }
      }
    }

