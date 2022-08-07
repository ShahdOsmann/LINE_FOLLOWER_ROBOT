 #include <SoftwareSerial.h>
 #include <Servo.h>   
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
int cgrip ,cwrist ;  //current positions
int pgrip, pwrist;  // previous positions
int  gripSP[50], wristSP[50];  
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
  delay(3000); 

  servo_grip.attach(9);
  servo_wrist.attach(10);
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
  Bluetooth.setTimeout(1);
  delay(20); 

  // Robot arm initial position
  pgrip = 0;
  servo_grip.write(pgrip);
  pwrist= 0;
  servo_wrist.write(pwrist);
   

}