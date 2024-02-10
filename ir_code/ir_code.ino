 
  
#include <AFMotor.h>
 
AF_DCMotor left_motor(2,MOTOR12_1KHZ);
AF_DCMotor right_motor(4,MOTOR12_1KHZ);  
 
int right_sensor=A0;
//int middle_sensor=A1;
int left_sensor=A2;
bool command=true;
int state =0;
bool middle_sensor =true;

void setup() {
  if(Serial.available() > 0){ 
command = Serial.read();
switch(command){ 
case 'F': 
middle_sensor=true; 
break; 
case 'B': 
middle_sensor=false; 
break;  
} 
} 
  pinMode(right_sensor,INPUT);
  //pinMode(middle_sensor,INPUT);
  pinMode(left_sensor ,INPUT);
 
  
  right_motor.setSpeed(180); 
  right_motor.setSpeed(180); 
  delay(3000);//put the car int the begining line after 3 seconds 
   

}

void loop() {
  //the reads of the sensors
  int rs=digitalRead(right_sensor);
  int ms=digitalRead(middle_sensor);
  int ls=digitalRead(left_sensor);

  //conditions
  //read white from the out sensors and black from the middle so move
 if ((ls == 0) && (ms == 1)&&(rs == 0)) //in case 010 
  {
    //forward();
  right_motor.setSpeed(180);
  left_motor.setSpeed(180);
  right_motor.run(FORWARD);
  left_motor.run(FORWARD);
    state=1;
  }
 
  else if((ls == 1) && (ms == 0)&& (rs == 1))
  {
    //forward();
    right_motor.setSpeed(180);
  left_motor.setSpeed(180);
  right_motor.run(FORWARD);
  left_motor.run(FORWARD);
  }
  
  //natural turn to left
  else if ((ls == 1) && (ms == 0)&&(rs == 0))//in case 100
  {
    //left();
  right_motor.setSpeed(150);
  left_motor.setSpeed(50);
  right_motor.run(FORWARD);
  left_motor.run( FORWARD);
    state=2;
  }
  
   //turn with an angle to left
  else if ((ls == 1) && (ms == 1)&&(rs == 0)) 
  {
    //sharp_left();
    right_motor.setSpeed( 180);
  left_motor.setSpeed(0);
  right_motor.run(FORWARD);
  left_motor.run(RELEASE);
     state=2;
  }
  
  //natural turn to right
  else if ((ls == 0) && (ms == 0)&&(rs == 1)) 
  {
    //right();
   right_motor.setSpeed(50);
  left_motor.setSpeed(150);
  right_motor.run( FORWARD);
  left_motor.run(FORWARD);
    state=3;
  }
  
  //angle turn to right
  else if ((ls == 0) && (ms == 1)&&(rs == 1))
  {
    //sharp_right();
    right_motor.setSpeed(0);//shall i low the speed in turns?
  left_motor.setSpeed(180);
  right_motor.run(RELEASE);
  left_motor.run(FORWARD); 
     state=3;
  }
    
  //  in case111 will go for 500ms and if it reads 111 then it arrived to the black square if reads 000 (white) then it reached two ways(circle path)so will retun back for 500ms and turn right or left
  else if ((ls == 1) && (ms == 1)&& (rs == 1))  
  {
    //forward(500);       cause we want know either we are towards a circle or we are at the finishing point
       right_motor.setSpeed(180);
  left_motor.setSpeed(180);
  right_motor.run(FORWARD);
  left_motor.run(FORWARD);
    delay(500);
    
    //stop();
       right_motor.setSpeed(0);
  left_motor.setSpeed(0);
  right_motor.run(RELEASE);
  left_motor.run(RELEASE);
    delay(2);
    if((ls == 1) && (ms == 1)&& (rs == 1))
    {
      //stop();
        right_motor.setSpeed(0);
  left_motor.setSpeed(0);
  right_motor.run(RELEASE);
  left_motor.run(RELEASE);
    }
    else if((ls == 0) && (ms == 0)&& (rs == 0))//on the circle path
    {
      //backward(500);      so we get to the point from where we started
       right_motor.setSpeed( 180);
  left_motor.setSpeed(180);
  right_motor.run(BACKWARD);
  left_motor.run(BACKWARD);
      delay(500);
      //stop(); // delay 500 ms to take the recent read after we get to the point we moved from 
        right_motor.setSpeed(0);
  left_motor.setSpeed(0);
  right_motor.run(RELEASE);
  left_motor.run(RELEASE);
      delay(1);
      //right();// we now know that we are in a circle so we must get right or left
      right_motor.setSpeed(50);
  left_motor.setSpeed(150);
  right_motor.run( FORWARD);
  left_motor.run(FORWARD);
    }
  
  }

  
///in case 000 if it got out of the line or on dashed linne 
  if((ls == 0) && (ms == 0)&& (rs == 0))
  {
    if(state==1)// the last was the straighrtb line and now it is now on the dashedline
    {
      //forward();
      right_motor.setSpeed(180);
  left_motor.setSpeed(180);
  right_motor.run(FORWARD);
  left_motor.run(FORWARD);
    }
    if(state==2)//the last  was left turn and got out 
    {
      //left();
       right_motor.setSpeed(150);
  left_motor.setSpeed(50);
  right_motor.run(FORWARD);
  left_motor.run( FORWARD);
    }
    if(state==3)// the last was right turn and got out
    {
      //right();
       right_motor.setSpeed(50);
  left_motor.setSpeed(150);
  right_motor.run( FORWARD);
  left_motor.run(FORWARD);
    }
  }
  
 }
 
  //phone control
/*  if(Serial.available() > 0){ 
command = Serial.read();
switch(command){ 
case 'F': 
forward(); 
break; 
case 'B': 
back(); 
break; 
case 'L': 
sharp_left(); 
break; 
case 'R': 
sharp_right(); 
break; 
} 
} */
//functions
/*void forward(){
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
  right_motor.setSpeed(0);//shall i low the speed in turns?
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
} */
