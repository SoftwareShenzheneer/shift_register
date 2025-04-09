/*
 * @description A brief example of how to use this specific shift register module
 * It covers defining platform specific functions, passing these as configured output functions
 * and performing the shift task.
 * */
#include "sn74hc164.h"

/* Arbitrary, platform specific GPIO control functions */
static void myClockSetFunction(void) {}
static void myDataSetFunction(void) {}
static void myClockResetFunction(void) {}
static void myDataResetFunction(void) {}

int main(void) {
  /* Register the set and reset functions */
  sn74hc164_registerSetFunction(CLOCK_FUNCTION, myClockSetFunction);
  sn74hc164_registerSetFunction(DATA_FUNCTION, myDataSetFunction);
  sn74hc164_registerResetFunction(CLOCK_FUNCTION, myClockResetFunction);
  sn74hc164_registerResetFunction(DATA_FUNCTION, myDataResetFunction);

  /* Init the register by shifting out zeroes */
  sn74hc164_init(0x00);

  /* Shift out data */
  sn74hc164_shift(0xFF);

  return 0;
}

