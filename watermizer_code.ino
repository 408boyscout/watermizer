// Watermizer Arduino code. Aryan A. 04/30/2024
int sewerPin = 10;
int tankPin = 8;
int tankLedPin = 11;
int sewerLedPin = 12;
int buzzer = 9;
boolean qualityBad = true;


void setup() {
  // setup code here, to run once:
  pinMode(sewerPin, OUTPUT);
  pinMode(sewerLedPin, OUTPUT);
  pinMode(tankPin, OUTPUT);
  pinMode(tankLedPin, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  //start with Sewer valve open always.
  digitalWrite(sewerPin, HIGH);
  digitalWrite(tankPin, LOW);

}

void loop() {
//check the Torbidy sensor value
int waterQuality = analogRead(A0);
printWaterQuality(waterQuality);

if (waterQuality < 600){
  //water is bad, send it to sewer
  if (!qualityBad){ // take action only if quality was good before
  waterToSewer();  
  qualityBad = true;
  }
  
} else {
  //water is clean, send it to tank
  if (qualityBad){ // take action only if quality was bad before
  waterToTank();
  qualityBad = false;
  }
  
}

delay(200); //slower the reaction/sensing time

}

void printWaterQuality(int waterQuality){
  Serial.println ("Sensor Value: ");
  Serial.println (waterQuality);
  Serial.println();  
}


void waterToSewer() {
  //close tank valve, open sewer valve
  digitalWrite(sewerPin, HIGH);
  digitalWrite(tankPin, LOW);
  digitalWrite(sewerLedPin, HIGH);
  digitalWrite(tankLedPin, LOW);
  buzz();
}

void waterToTank() {
  //open tank valve, close sewer valve
  digitalWrite(tankPin, HIGH);
  digitalWrite(sewerPin, LOW);
  digitalWrite(tankLedPin, HIGH);
  digitalWrite(sewerLedPin, LOW);
  buzz2();
}

void buzz() { // single buzzer for dirty water
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
}
void buzz2() { // pattern buzzer for clean water
  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(80);
  digitalWrite(buzzer, LOW);
}

void shutWater() {
  // close both valves
  digitalWrite(tankPin, LOW);
  digitalWrite(sewerPin, LOW);
  digitalWrite(tankLedPin, LOW);
  digitalWrite(sewerLedPin, LOW);
}

