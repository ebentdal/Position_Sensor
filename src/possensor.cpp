#include <avr/io.h>
#include <util/delay.h>
#include "possensor.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define T1_PRESCALER 8UL

static inline void trig_low()  { PORTC &= ~(1 << PC0); }
static inline void trig_high() { PORTC |=  (1 << PC0); }
static inline bool echo_read() { return (PINC & (1 << PC1)) != 0; }


void timer1_init() {
  TCCR1A = 0;
  TCCR1B = (1 << CS11); 
  TCNT1  = 0;
}
uint32_t ticks_to_us(uint16_t ticks) {
  return (uint32_t)ticks * T1_PRESCALER * 1000000UL / (uint32_t)F_CPU;
}

uint16_t t1_now() { return TCNT1; }

void pos_init(void) {

  DDRC |=  (1 << PC0);
  DDRC &= ~(1 << PC1);
  trig_low();
  timer1_init();

}

uint16_t pos_pulse(uint16_t timeout_ticks) {
  
  trig_low();  _delay_us(2);
  trig_high(); _delay_us(12);
  trig_low();

  TCNT1 = 0;
  while (!echo_read()) {
    if (TCNT1 >= timeout_ticks) return 0;
  }

  TCNT1 = 0;
  while (echo_read()) {
    if (TCNT1 >= timeout_ticks) return 0;
  }

  return TCNT1;
}

uint16_t pos_distance_cm(uint16_t timeout_us) {
  uint32_t timeout_ticks = (uint32_t)timeout_us * (uint32_t)F_CPU / (T1_PRESCALER*1000000UL);
  if (timeout_ticks > 65535) timeout_ticks = 65535;

  uint16_t ticks = pos_pulse((uint16_t)timeout_ticks);
  if (ticks == 0) return 0;

  uint32_t us = ticks_to_us(ticks);

  return (uint16_t)(us / 5.8);
}


