# LINE_FOLLOWER_ROBOT 

## Description

I started working on my first robot about a year ago with a team and I was responsible for the software part. The robot is a black line follower that we often see in hospitals and large factories, and it has an arm to carry things and move them from one place to another, following the line automatically, and it can also be controlled remotely by your phone.

## Table of Contents  

The robot consists of two main parts, the mechanical part and the programming part. We will focus on the programming part as I was responsible for it. This part is divided into three main sections and will include the electrical components.
 
-  ### electrical components 
-  ### Motor controlled motion forms
-  ### Algorithm of the robot movement
-  ### Algorithm of the arm movement



## electrical components

- 6 x IR Transmitter and Receiver pair  
- LM2576 Step-Down Voltage Regulator
- L298 Motor Driver Module
- Atmega32 microcontroller   
- Lithium-Ion Rechargeable Battery Pack 11.1V 3000mAh 2C 
- Resistors , Capacitors npn transistors and diodes

## Motor controlled motion forms

The robot has seven forms of movement that take place according to the readings of the sensors, and the movement is forward by making the direction of the two motors   forward , backward movement, by making the two directionsof motors backward , to turn right, we make the right motor move backwardand and the other forward  at different speeds . In the sharp curves, the speeds are increased in the most appropriate direction, and vice versa on left curves anfd stop, by stopping both motors.
  
---
  
## Algorithm of the robot movement

The algorithm is developed keeping in mind the following rules:
- at any intersection, if there exists a forward path, then the robot should take that path and if it doesn't exist, then the robot is free to choose any path.
- if there is any discontinuity in the line, then the robot has to move forward until it detects the line.
- there will be black square in the end of the track.
- Five sensors are placed in a straight horizontal line, and each sensor is separated by three centimeters, and the sixth sensor is placed in the middle front, at a     distance of five centimeters from the sensor behind it.
  
Given below are three steps which is repeatedly executed when the robot moves over the line:

Step1 : 
The sensor readings are taken and stored in a byte with each bit representing the status of one particular sensor. If a bit is 1, then the corresponding sensor is over the line and if the bit is 0, then it is not on the line. 

Step2 : 
The three sensors in the middle are the main ones, and they have eight readings, which are:
-  000 : the robot is out the line or in the dashed line (solvd by the  code).
-  010 : the robot in straight black line and the robot should move forward.
-  001 : right turn so the robot should turn right.
-  011 : an angle right turn so the robot should take a sharp turn right.
-  100 : left turn so the robot should turn left.
-  110 : an angle left turn so the robot should take a sharp turn left.
-  101 : in the dashed line and the robot will keep moving forward.
-  111 : the black square and the robot should stop moving. 

step3
- the front sensor check if in the black square will read 1 or  in the circle will read 0.
- the sensors on the sides check if the robot got out of track or not and balance the move of the robot.
 
## Algorithm of the arm movement
 
 it has two main sections are the grip and the wrist using two servos and control their move by an application.

---  

## Features
The most important feature of the robot is that if it deviates from the path, it can return to its previous position and continue on its way (achieved by coding).

## Applications
 the app of manual control via bluetooth "Bluetooth RC Controller". 
 
