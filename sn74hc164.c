#include <stdbool.h>

#include "sn74hc164.h"

void (*setClock)()    = NULL;
void (*resetClock)()  = NULL;
void (*setData)()     = NULL;
void (*resetData)()   = NULL;

/*
 * @brief Initialize the shift register by shifting out an initialization value
 * @param uint8_t data
 * @return void
 * */
void sn74hc164_init(uint8_t init) {
  sn74hc164_shift(init);
}

/*
 * @brief Shift out single byte of data bit-by-bit
 * @param uint8_t data
 * @return void
 * */
void sn74hc164_shift(uint8_t data) {
  bool bit = 0;
  uint8_t byte = data;
  uint8_t i = 0;

  bit = byte & 0x01;

  for (i = 0; i < 8; i++) {
    sn74hc164_resetOutput(CLOCK_FUNCTION);

    if (1 == bit) {
      sn74hc164_resetOutput(DATA_FUNCTION);
    } else {
      sn74hc164_setOutput(DATA_FUNCTION);
    }
    byte = byte >> 1;
    bit = byte & 0x01;
    sn74hc164_setOutput(CLOCK_FUNCTION);
  }
}

/*
 * @brief Register a platform specific function to function in this module
 * @param enum Fn function - IO function to call
 * @param void *fn - paltform dependent function implementation
 * @return void
 * */
void sn74hc164_registerSetFunction(enum Fn function, void (*fn)) {
  switch(function) {
    case CLOCK_FUNCTION:
      setClock = fn;
      break;

    case DATA_FUNCTION:
      setData = fn;
      break;

    case MAX_NO_OF_FUNCTIONS:
    default:
      break;
  }
}

/*
 * @brief Register a platform specific function to function in this module
 * @param enum Fn function - IO function to call
 * @param void *fn - paltform dependent function implementation
 * @return void
 * */
void sn74hc164_registerResetFunction(enum Fn function, void (*fn)) {
  switch (function) {
    case CLOCK_FUNCTION:
      resetClock = fn;
      break;

    case DATA_FUNCTION:
      resetData = fn;
      break;

    case MAX_NO_OF_FUNCTIONS:
    default:
      break;
  }
}

/*
 * @brief Call the set function according to the registered platform
 * @param enum Fn function - IO function to call
 * @return void
 * */
void sn74hc164_setOutput(enum Fn function) {
  switch (function) {
    case CLOCK_FUNCTION:
      if (setClock) {
        setClock();
      } else {
        exit(1);
      }
      break;

    case DATA_FUNCTION:
      if (setData) {
        setData();
      } else {
        exit(1);
      }
      break;

    case MAX_NO_OF_FUNCTIONS:
    default:
      break;
  }
}

/*
 * @brief Call the reset function according to the registered platform
 * @param enum Fn function - IO function to call
 * @return void
 * */
void sn74hc164_resetOutput(enum Fn function) {
  switch (function) {
    case CLOCK_FUNCTION:
      if (resetClock) {
        resetClock();
      } else {
        exit(1);
      }
      break;

    case DATA_FUNCTION:
      if (resetData) {
        resetData();
      } else {
        exit(1);
      }
      break;

    case MAX_NO_OF_FUNCTIONS:
    default:
      break;
  }
}

