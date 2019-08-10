/** File: Particle.h
 *  Purpose: Redefine some Particle-defined types for use in unit-testing (compilation on PC)
**/
#ifndef PARTICLE_H
#define PARTICLE_H

// Particle String class
#include "fake_particle_string.h"
// Particle.Publish() faking functionality
#include "fake_particle_publish.h"
// Particle's Time class faking functionality
#include "fake_time.h"
// Serial class for Modbus Master
#include "fake_serial.h"

#define OUTPUT	1

// Functions below are defined in Particle.cpp to prevent multiple redefinitions
void pinMode(int pin, int mode);
void digitalWrite(int pin, int level);
uint32_t millis();

#endif // PARTICLE_H
