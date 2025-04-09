#ifndef __SN74HC164_H__
#define __SN74HC164_H__

#include <stdint.h>
#include <stdlib.h>

#define SHIFT_BYTES 5

enum Fn {
  CLOCK_FUNCTION = 0,
  DATA_FUNCTION,

  MAX_NO_OF_FUNCTIONS
};

void sn74hc164_init(uint8_t init);
void sn74hc164_shift(uint8_t data);

void sn74hc164_registerSetFunction(enum Fn function, void (*fn));
void sn74hc164_registerResetFunction(enum Fn function, void (*fn));
void sn74hc164_setOutput(enum Fn function);
void sn74hc164_resetOutput(enum Fn function);

#endif /* __SN74HC164_H__ */

