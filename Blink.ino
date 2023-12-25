/*

  Turns an LED in case the IR sensor detects an obstacle.
*/
int a = 8;
int ir_sensor = 6;
int ir_sens_val = 0;

//The setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(a, OUTPUT);
  pinMode(ir_sensor, INPUT);
  Serial.begin(9600);
}

//The loop function runs over and over again forever
void loop() {
  delay(100);  // wait for a second

  //IR sensor
  ir_sens_val = digitalRead(ir_sensor);
  Serial.println(ir_sens_val);

  if(!ir_sens_val)
  {
    digitalWrite(a, HIGH);
  }
  else
  {
    digitalWrite(a, LOW);
  }
  
  
}
