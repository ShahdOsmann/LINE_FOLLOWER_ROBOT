 #include <SoftwareSerial.h>
 #include <Servo.h>//the library for seial communication  
  
#include <AFMotor.h>
 
AF_DCMotor left_motor(2,MOTOR12_1KHZ);
AF_DCMotor right_motor(4,MOTOR12_1KHZ);  
 
int right_sensor=A0;
int middle_sensor=A1;
int left_sensor=A2;
int front_sensor=A3;
int lleft_sensor=A4;
int rright_sensor=A5;

 Servo servo_grip;
Servo servo_wrist;
SoftwareSerial Bluetooth(0, 1); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)
int servo_grip_c_postion ,servo_wrist_c_postion ; // current position
int servo_grip_p_postion, servo_wrist_p_postion; // previous position
int servo_gripSP[50], servo_wristSP[50]; // for storing positions/steps
int speedDelay = 15;
int index = 0;
String dataIn = "";


 
int first=0;//in condition 101
 int track =0;//black square
char command;
int state =0;


void setup() {
  
  pinMode(right_sensor,INPUT);
  pinMode(middle_sensor,INPUT);
  pinMode(left_sensor ,INPUT);
  pinMode(front_sensor ,INPUT);
  pinMode(lleft_sensor ,INPUT);
  pinMode(rright_sensor ,INPUT);
  
  right_motor.setSpeed(180); 
  left_motor.setSpeed(180); 
  delay(3000);//put the car int the begining line after 3 seconds 

  servo_grip.attach(9);
  servo_wrist.attach(10);
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
  Bluetooth.setTimeout(1);
  delay(20);

  
  // Robot arm initial position
  servo_grip_p_postion = 0;
  servo_grip.write(servo_grip_p_postion);
  servo_wrist_p_postion = 0;
  servo_wrist.write(servo_wrist_p_postion);
   

}

void loop() {
  //the reads of the sensors
  int rs=!digitalRead(right_sensor);
  int ms=!digitalRead(middle_sensor);
  int ls=!digitalRead(left_sensor);
  int fs=!digitalRead(front_sensor);
  int rrs=!digitalRead(rright_sensor);
  int lls=!digitalRead(lleft_sensor);
  

  //conditions
  //read white from the out sensors and black from the middle so move
 if ((ls == 0) && (ms == 1)&&(rs == 0)) //in case 010 
  {
    forward(); 
    state=1;
  }
 
  else if((ls == 1) && (ms == 0)&& (rs == 1) )//in case101  
  {
    if(first==0)//first track dashed line 
    {
    forward();
  first=1;
  
    }
  
  
  else if(first==1)//second track
  {
    left(); 
  first=0;
  
  }
 }
  
  //natural turn to left
  else if ((ls == 1) && (ms == 0)&&(rs == 0)) //in case 100
  {
    left();
    state=2;
  }
  
   //turn with an angle to left
  else if ((ls == 1) && (ms == 1)&&(rs == 0)) //in case 110
  {
    sharp_left();
     state=2;
  }
  
  //natural turn to right
  else if ((ls == 0) && (ms == 0)&&(rs == 1)) //in case001
  {
    right();
   
    state=3;
  }
  
  //angle turn to right
  else if ((ls == 0) && (ms == 1)&&(rs == 1))//in case 011
  {
    sharp_right();
   
     state=3;
  }
    ////////////////////////////////////////*******************************//////////////////////////////////////////////
    
   else if ((ls == 1) && (ms == 1)&& (rs == 1) )//in case111 
  {
    
    if( fs==1)
    {
      if(track==0)// in the finishing black square in track1
      {
      Stop();
      track=1;
      } 
   else if (track==1)//in the beginning track2
   {
    forward();
  track=2;
    }
    else if (track==2)//in the loop
   {
    forward();
  track=0;
    }
   }
    
    
    else if(fs==0)//on the circle path
    {
      left();
 
    }
  
  }

  
///in case 000 if it got out of the line or on dashed linne 
  else if((ls == 0) && (ms == 0)&& (rs == 0))// in case 000=====================================================/////
  {
    if(state==1)// the last was the straighrtb line and now it is now on the dashed line
    {
      forward();
      
    }
    if(rrs==1&&lls==0)//the last  was left turn and got out 
    {
      right();
       
    }
    if(lls==1&&rrs==0)// the last was right turn and got out
    {
       left();
   
    }
  }
    ///in case 000 if it got out of the line or on dashed linne 
  else if((ls == 0) && (ms == 0)&& (rs == 0)&&(lls==0)&&(rrs==0))// in case 000 
  {
    if(state==1)// the last was the straighrtb line and now it is now on the dashed line
    {
       forward();
      
    }
    if(state==2)//the last  was left turn and got out 
    {
      left();
       
    }
    if(state==3)// the last was right turn and got out
    {
      right();
   
    }
  }
  
  // Check for incoming data
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.readString();  // Read the data as string
         // We use for loops so we can control the speed of the servo
      // If previous position is bigger then current position
    // Move Servo for Grip
    if (dataIn.startsWith("s5")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo_grip_c_postion = dataInS.toInt();
      if (servo_grip_p_postion > servo_grip_c_postion) {
        for ( int j = servo_grip_p_postion; j >= servo_grip_c_postion; j--) {
          servo_grip.write(j);
          delay(20);
        }
      }
      if (servo_grip_p_postion < servo_grip_c_postion) {
        for ( int j = servo_grip_p_postion; j <= servo_grip_c_postion; j++) {
          servo_grip.write(j);
          delay(20);
        }
      }
      servo_grip_p_postion = servo_grip_c_postion;
    }
    // Move Servo for Wrist
    if (dataIn.startsWith("s6")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      servo_wrist_c_postion = dataInS.toInt();
      if (servo_wrist_p_postion > servo_wrist_c_postion) {
        for ( int j = servo_wrist_p_postion; j >= servo_wrist_c_postion; j--) {
          servo_wrist.write(j);
          delay(10);
        }
      }
      if (servo_wrist_p_postion < servo_wrist_c_postion) {
        for ( int j = servo_wrist_p_postion; j <= servo_wrist_c_postion; j++) {
          servo_wrist.write(j);
          delay(10);
        }
      }
      servo_wrist_p_postion = servo_wrist_c_postion; 
    }
    // If button "SAVE" is pressed
    if (dataIn.startsWith("SAVE")) {
      servo_gripSP[index] = servo_grip_p_postion;
      servo_wristSP[index] = servo_wrist_p_postion;
      index++;  // Increase the array index
    }
    // If button "RUN" is pressed
    if (dataIn.startsWith("RUN")) {
      runservo();  // Automatic mode - run the saved steps 
    }
    // If button "RESET" is pressed
   if ( dataIn == "RESET") {
      memset(servo_gripSP, 0, sizeof(servo_gripSP));
      memset(servo_wristSP, 0, sizeof(servo_wristSP));
      index = 0;  // Index to 0
    }
  }

  //phone control
  if(Serial.available() > 0){ 
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


  
}
}

//functions
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



// Automatic mode custom function - run the saved steps
void runservo() {
  while (dataIn != "RESET") {   // Run the steps over and over again until "RESET" button is pressed
    for (int i = 0; i <= index - 2; i++) {  // Run through all steps(index)
      if (Bluetooth.available() > 0) {      // Check for incomding data
        dataIn = Bluetooth.readString();
        if ( dataIn == "PAUSE") {           // If button "PAUSE" is pressed
          while (dataIn != "RUN") {         // Wait until "RUN" is pressed again
            if (Bluetooth.available() > 0) {
              dataIn = Bluetooth.readString();
              if ( dataIn == "RESET") {     
                break;
              }
            }
          }
        }
        // If speed slider is changed
        if (dataIn.startsWith("ss")) {
          String dataInS = dataIn.substring(2, dataIn.length());
          speedDelay = dataInS.toInt(); // Change servo speed (delay time)
        }
      }
      
      // Servo for grip move
      if (servo_gripSP[i] == servo_gripSP[i + 1]) {
      }
      if (servo_gripSP[i] > servo_gripSP[i + 1]) {
        for ( int j = servo_gripSP[i]; j >= servo_gripSP[i + 1]; j--) {
          servo_grip.write(j);
          delay(speedDelay);
        }
      }
      if (servo_gripSP[i] < servo_gripSP[i + 1]) {
        for ( int j = servo_gripSP[i]; j <= servo_gripSP[i + 1]; j++) {
          servo_grip.write(j);
          delay(speedDelay);
        }
      }

      // Servo for wrist move
      if (servo_wristSP[i] == servo_wristSP[i + 1]) {
      }
      if (servo_wristSP[i] > servo_wristSP[i + 1]) {
        for ( int j = servo_wristSP[i]; j >= servo_wristSP[i + 1]; j--) {
          servo_wrist.write(j);
          delay(speedDelay);
        }
      }
      if (servo_wristSP[i] < servo_wristSP[i + 1]) {
        for ( int j = servo_wristSP[i]; j <= servo_wristSP[i + 1]; j++) {
          servo_wrist.write(j);
          delay(speedDelay);
        }
      }
    }
  }
}

  
 
 
 
 
  
 
  
