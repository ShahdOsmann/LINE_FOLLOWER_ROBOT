
  // Check incoming data
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.readString();  
    //   Grip  Move
    if (dataIn.startsWith("s5")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      cgrip = dataInS.toInt();
      if (pgrip > cgrip) {
        for ( int i = pgrip; i >= cgrip; i--) {
          servo_grip.write(i);
          delay(20);
        }
      }
      if (pgrip < cgrip) {
        for ( int i = pgrip; i <= cgrip; i++) {
          servo_grip.write(i);
          delay(20);
        }
      }
      pgrip = cgrip;
    }
    //  Wrist Move
    if (dataIn.startsWith("s6")) {
      String dataInS = dataIn.substring(2, dataIn.length());
      cwrist = dataInS.toInt();
      if (pwrist > cwrist) {
        for ( int i = pwrist; i >= cwrist; i--) {
          servo_wrist.write(i);
          delay(10);
        }
      }
      if (pwrist < cwrist) {
        for ( int i = pwrist; i <= cwrist; i++) {
          servo_wrist.write(i);
          delay(10);
        }
      }
      pwrist = cwrist; 
    } 
    // If button "RUN" is pressed
    if (dataIn.startsWith("RUN")) {
      runservo();  
    }
    // If button "RESET" is pressed
   if ( dataIn == "RESET") {
      memset( gripSP, 0, sizeof(gripSP));
      memset( wristSP, 0, sizeof(wristSP));
      in  = 0;  
    }
  }
