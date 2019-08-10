/** File: T400_registers.h
 *  Purpose: Define register mappings for the T400
**/
#ifndef T400_REGISTERS_H
#define T400_REGISTERS_H

#include <map>
#include <vector>

#include "Particle.h"

/* T400 Specific Registers */
enum DiscreteInputFlag {
  FLAG_MONITOR = 0,
  FLAG_SAMPLE = 1,
  FLAG_CALIBRATION = 2
};

const std::map<int, DiscreteInputFlag> DISCRETE_INPUTS_MAP = {
  { 0, FLAG_MONITOR },
  { 1, FLAG_MONITOR },
  { 8, FLAG_SAMPLE },
  { 20, FLAG_CALIBRATION }
};

const std::vector<int> INPUT_REGISTERS = {
  0, /* PHSTB */
  6, /* SLOPE1 */
  10, /* OFSET1 */
  20, /* SMPFLW */
  124, /* CONC1 */
};

//
const String SD_FILE_HEADER_STR =
  "PHSTB"
  "SLOPE1"
  "OFSET1"
  "SMPLFLW"
  "CONC1"
  "FLAGS"; // Make sure to end with Flags (discrete inputs)

#endif // T400_REGISTERS_H
