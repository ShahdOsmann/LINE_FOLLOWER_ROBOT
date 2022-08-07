//phone control
if(Serial.available() > 0){ 
command = Serial.read();
switch(command){ 
// move forward
case 'F': 
forward();
break; 
// move back
case 'B':
back(); 
break;
 // move left
case 'L': 
sharp_left();
break;
 //move right
case 'R': 
sharp_right(); 
 break; 
}

 