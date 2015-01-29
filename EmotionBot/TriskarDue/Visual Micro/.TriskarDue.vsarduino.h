#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Mega 2560 or Mega ADK
#define __AVR_ATmega2560__
#define ARDUINO 101
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

float getRange(int pin_num);
//
//
void run_cb();
void servo_cb();
void reset_cb();
void stop_cb();
void invalid(const char *command);
void calculateVelocityMotors();
void HandleMotor1InterruptA();
void HandleMotor1InterruptB();
void HandleMotor2InterruptA();
void HandleMotor2InterruptB();
void HandleMotor3InterruptA();
void HandleMotor3InterruptB();

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "f:\EmotionBot\trunk\TriskarDue\TriskarDue.ino"
#endif
