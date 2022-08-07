 
void runservo() {
  while (dataIn != "RESET") {   
    for (int i = 0; i <= in - 2; i++) { 
      if (Bluetooth.available() > 0) {      
        dataIn = Bluetooth.readString();
        if ( dataIn == "PAUSE") {         
          while (dataIn != "RUN") {      
            if (Bluetooth.available() > 0) {
              dataIn = Bluetooth.readString();
              if ( dataIn == "RESET") {     
                break;
              }
            }
          }
        }  
      }
      
      //   grip move 
      if ( gripSP[i] > gripSP[i + 1]) {
        for ( int j =  gripSP[i]; j >=  gripSP[i + 1]; j--) {
          servo_grip.write(j);
          delay(speedDelay);
        }
      }
      if ( gripSP[i] < gripSP[i + 1]) {
        for ( int j =  gripSP[i]; j <=  gripSP[i + 1]; j++) {
          servo_grip.write(j);
          delay(speedDelay);
        }
      }

      //   wrist move 
      if ( wristSP[i] >  wristSP[i + 1]) {
        for ( int j =  wristSP[i]; j >=  wristSP[i + 1]; j--) {
          servo_wrist.write(j);
          delay(speedDelay);
        }
      }
      if ( wristSP[i] <  wristSP[i + 1]) {
        for ( int j =  wristSP[i]; j <=  wristSP[i + 1]; j++) {
          servo_wrist.write(j);
          delay(speedDelay);
        }
      }
    }
  }
}
 