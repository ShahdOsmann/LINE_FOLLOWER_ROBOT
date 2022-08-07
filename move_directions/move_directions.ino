
// control the motors direction and speed  

void forward(){
  right_motor.setSpeed(180);
  left_motor.setSpeed(180);
  right_motor.run(FORWARD);
  left_motor.run(FORWARD);
}
void left(){
  right_motor.setSpeed(150);
  left_motor.setSpeed(50);
  right_motor.run(FORWARD);
  left_motor.run( FORWARD);
}
void right(){
  right_motor.setSpeed(50);
  left_motor.setSpeed(150);
  right_motor.run( FORWARD);
  left_motor.run(FORWARD);
}
void Stop(){
  right_motor.setSpeed(0);
  left_motor.setSpeed(0);
  right_motor.run(RELEASE);
  left_motor.run(RELEASE);
}
void sharp_right(){
  right_motor.setSpeed(0); 
  left_motor.setSpeed(180);
  right_motor.run(RELEASE);
  left_motor.run(FORWARD);
}
void sharp_left(){
  right_motor.setSpeed( 180);
  left_motor.setSpeed(0);
  right_motor.run(FORWARD);
  left_motor.run(RELEASE);
}
 void back(){
  right_motor.setSpeed( 180);
  left_motor.setSpeed(180);
  right_motor.run(BACKWARD);
  left_motor.run(BACKWARD);
}

 
 