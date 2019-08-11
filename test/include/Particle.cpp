#include "Particle.h"
#include <unistd.h>

void pinMode(int pin, int mode){}

void digitalWrite(int pin, int level){}

uint32_t millis(){}

void delay(unsigned int ms){
  sleep(ms / 1000);
}
