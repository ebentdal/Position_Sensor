#include <avr/io.h>
#include <util/delay.h>
#include "possensor.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif


static inline void trig_low()  { PORTC &= ~(1 << PC0); }
static inline void trig_high() { PORTC |=  (1 << PC0); }
static inline bool echo_read() { return (PINC & (1 << PC1)) != 0; }


static inline void t1_start_1mhz() {
  TCCR1A = 0;
  TCCR1B = (1 << CS11); 
  TCNT1  = 0;
}

static inline uint16_t t1_now() { return TCNT1; }

void pos_init(void) {

  DDRC |=  (1 << PC0);
  DDRC &= ~(1 << PC1);

  trig_low();

  
  t1_start_1mhz();
}

uint16_t pos_pulse_us(uint16_t timeout_us) {
  
  trig_low();
  _delay_us(2);
  trig_high();
  _delay_us(12);
  trig_low();

  
  TCNT1 = 0;
  while (!echo_read()) {
    if (t1_now() >= timeout_us) return 0;
  }

  
  TCNT1 = 0;
  while (echo_read()) {
    if (t1_now() >= timeout_us) return 0;
  }

  return t1_now(); 
}

uint16_t pos_distance_cm(uint16_t timeout_us) {
  uint16_t us = pos_pulse_us(timeout_us);
  if (us == 0) return 0;

  return (uint16_t)(us / 5.8);
}
