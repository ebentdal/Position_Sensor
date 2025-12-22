#include <stdint.h>
#include <stdbool.h>

void timer1_init();
uint32_t ticks_to_us(uint16_t ticks);
void pos_init(void);
uint16_t t1_now();
uint16_t pos_pulse(uint16_t timeout_us);

uint16_t pos_distance_cm(uint16_t timeout_us);
