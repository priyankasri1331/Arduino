or/*

*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//This constant won't change. It's the PIN of the sensor's output:
const int TrigPin = 7;
const int echoPin = 8;
int display_delay = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(TrigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.print("PK");
}

void loop() {
  // establish variables for the duration of the ping, and the distance result
  // in inches and centimeters:

  display_delay++;
  
  long duration, inches, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);

  //sensor reading
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  Serial.println(duration);

  //More delay for LCD display

  if(display_delay >=10) 
  {
    display_delay = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Dist in cm");
    lcd.setCursor(0,1);
    lcd.print(cm);
  }
  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance traveled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  //Take half of the distance traveled.
  return microseconds / 29 / 2;
}
