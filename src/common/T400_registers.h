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
  {0, FLAG_MONITOR},
  {1, FLAG_MONITOR},
  {2, FLAG_MONITOR},
  {3, FLAG_MONITOR},
  {4, FLAG_MONITOR},
  {5, FLAG_MONITOR},
  {6, FLAG_MONITOR},
  {7, FLAG_MONITOR},
  {8, FLAG_SAMPLE},
  {9, FLAG_SAMPLE},
  {10, FLAG_SAMPLE},
  {11, FLAG_MONITOR},
  {12, FLAG_MONITOR},
  {13, FLAG_MONITOR},
  {14, FLAG_MONITOR},
  {15, FLAG_MONITOR},
  {16, FLAG_MONITOR},
  {19, FLAG_SAMPLE},
  {20, FLAG_CALIBRATION},
  {21, FLAG_CALIBRATION},
  {22, FLAG_CALIBRATION},
  {23, FLAG_CALIBRATION},
  {25,	FLAG_SAMPLE}
};

const std::vector<int> INPUT_REGISTERS = {
  6, /* SLOPE1 */
  10, /* OFSET1 */
  18, /* CONC1 */
  28, /* O3TEMP */
  30, /* O3STMP */
  34, /* PHTEMP */
  38, /* SMPTMP */
  40, /* SMPFLW */
  42, /* SMPPRS */
  44 /* BOXTMP */
};

//
const String SD_FILE_HEADER_STR =
  "SLOPE1,"
  "OFSET1,"
  "CONC1 ,"
  "O3TEMP,"
  "O3STMP,"
  "PHTEMP,"
  "SMPTMP,"
  "SMPFLW,"
  "SMPPRS,"
  "BOXTMP,"
  "FLAGS"; // Make sure to end with Flags (discrete inputs)

#endif // T400_REGISTERS_H
