#include <Neko.h>
#include <Wire.h>
#include <Servo.h>
#include <ADXL345.h>

ADXL345 adxl;
Neko neko(10,4,12,9); //sets pins
int array[][4] = {
  {135,15,75,75}
  ,{95,85,95,85}
  ,{80,100,150,10}
}; //sets movement for ears
//Servo BaseRight;
//Servo BaseLeft;
//Servo TopRight;
//Servo TopLeft;

boolean Booted = false;
boolean Moved = false;
boolean ONOFF = true;

void setup()
{

  Wire.begin();        
  Serial.begin(5700);  
  //Sensor Crap
  adxl.powerOn();

  adxl.setActivityThreshold(75); //62.5mg per increment

  //look of activity movement on this axes - 1 == on; 0 == off 
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);

  //look of inactivity movement on this axes - 1 == on; 0 == off
  // adxl.setInactivityX(0);
  // adxl.setInactivityY(0);
  // adxl.setInactivityZ(0);

  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(0);

  //set values for what is a tap, and what is a double tap (0-255)
  //  adxl.setTapThreshold(50); //62.5mg per increment
  //  adxl.setTapDuration(15); //625μs per increment
  //  adxl.setDoubleTapLatency(80); //1.25ms per increment
  //  adxl.setDoubleTapWindow(200); //1.25ms per increment

  //setting all interupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  // adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,   ADXL345_INT1_PIN );
  // adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,   ADXL345_INT1_PIN );
  // adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,     ADXL345_INT1_PIN );

  //register interupt actions - 1 == on; 0 == off  
  // adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 0);
  // adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 0);
  // adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT,  0);
  // adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,   1);
  // adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 0);

  //Attach servo's to pins
  //  BaseRight.attach(10);
  //  TopRight.attach(4);
  //  BaseLeft.attach(12);
  //  TopLeft.attach(9);
  pinMode(6,INPUT_PULLUP);
  neko.setNTB(array);
}

void loop()
{
  if(!Booted) {
    neko.move(0);
    Booted = true;
  }
  int x,y,z;
  /*BaseRight.write(0);
   BaseLeft.write(0);
   TopRight.write(0);
   TopLeft.write(0);
   delay(1000);
   */
  byte interrupts = adxl.getInterruptSource();
  //double tap
  adxl.readAccel(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z

  /*
  BaseRight.write(180);
   BaseLeft.write(180);
   TopRight.write(180);
   TopLeft.write(180);
   */
  //if processing running
  //  if(Serial.available() >= 2)
  //  {
  //    int t = 0;
  //    switch(byte(Serial.read()))
  //    {
  //    case 'u':
  //      t = Serial.read();
  //      if((t >=0) && (t <= 180)) BaseRight.write(t);
  //      break;
  //    case 'd':
  //      t = Serial.read();
  //      if(t >=0 && t <= 180) BaseLeft.write(t);
  //      break;
  //    case 't':
  //      t = Serial.read();
  //      if(t >=0 && t <= 180)  TopRight.write(t);
  //      break;
  //    case 'q':
  //      t = Serial.read();
  //      if(t >=0 && t <= 180)  TopLeft.write(t);
  //      break;
  //    }
  //  }

  // Output x,y,z values - Commented out
  //  Serial.print(F("X: "));
  //  Serial.print(x);
  //  Serial.print(F(" Y: "));
  //  Serial.print(y);
  //  Serial.print(F(" Z: "));
  //  Serial.println(z);

  if(x > 100)
  {
    neko.move(0); //normal
  }
  else if(x < 100)
  {
    neko.move(2); //back
  }
  delay(10); // only read every 0.5 seconds
}


//void Back(){
//  BaseRight.write(80);
//  BaseLeft.write(100);
//  TopRight.write(150);
//  TopLeft.write(10);
//}
//
//void Twitch(){
//  BaseRight.write(95);
//  BaseLeft.write(85);
//  TopRight.write(95);
//  TopLeft.write(85);
//}
//
//void Normal() {
//  BaseRight.write(135);
//  BaseLeft.write(15);
//  TopRight.write(75);
//  TopLeft.write(75);
//}














