#ifndef Neko_h
#define Neko_h

#include "Arduino.h"
#include "Servo.h"

class Neko
{
  public:
    Neko(int pin, int pin2, int pin3, int pin4);
    void setNTB(int[][4]);
   void move(int cat);

  private:
    Servo _servos[4];
	int _NTB[][4];
    };

#endif
