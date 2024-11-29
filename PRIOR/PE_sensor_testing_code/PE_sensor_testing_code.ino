int sensorPin = 9 ;
int sensorValue = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(sensorPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
sensorValue = digitalRead(sensorPin);
if (sensorValue == HIGH)
{
  Serial.println("nothing");
}
if (sensorValue == LOW)
{
  Serial.println("detected");
}
delay(50);
}