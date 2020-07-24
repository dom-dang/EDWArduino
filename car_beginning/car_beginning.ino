// TODO: Change these values to the digital pin numbers on the Arduino connected to the button
int limit_switch_pin = 5;

// TODO: Change value to digital pwm pin number on the Arduino connected to the motor
// NOTE: pwm pins have a "~" in front of the number usually
int motor_1_pin = ~4;
int motor_2_pin = 0;

void setup() {
  // Here we initialize the pins on the board to the code
  // We want to get information from the button so we will set them as an input
  pinMode(limit_switch_pin, INPUT_PULLUP);

  // We want to send information to the motor so we will set them as an output
  pinMode(motor_1_pin, OUTPUT);
  pinMode(motor_2_pin, OUTPUT);
}

void loop() {
  // Here we check what the electrical value of the button pin is
  // We will know if the button is pressed or not based on what the value returns
  int limit_switch_value = digitalRead(limit_switch_pin);
  int motor_1_pin_value = digitalRead(motor_1_pin);
  int motor_2_pin_value = digitalRead(motor_2_pin);
  
  if (motor_1_pin_value ==0 && motor_2_pin_value ==0) {
      digitalWrite(motor_1_pin, HIGH);
      digitalWrite(motor_2_pin, HIGH);
  }
  else if (motor_1_pin_value ==1 && motor_2_pin_value ==0) {
      digitalWrite(motor_1_pin, HIGH);
      digitalWrite(motor_2_pin, LOW);
  }
  else if (motor_1_pin_value ==0 && motor_2_pin_value ==1) {
      digitalWrite(motor_1_pin, LOW);
      digitalWrite(motor_2_pin, HIGH);
  }
  else {
      digitalWrite(motor_1_pin, LOW);
      digitalWrite(motor_2_pin, LOW);
  }
  

  /* TODO: Fill in the switch statement!
  switch(limit_switch_value){
    case HIGH:
      analogWrite(motor_1_pin, 100);
      break;
    case LOW:
      analogWrite(motor_1_pin, 100);
      break;
  } */
}