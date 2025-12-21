#include <stdint.h>
#include <stdbool.h>


void pos_init(void);


uint16_t pos_pulse_us(uint16_t timeout_us);

uint16_t pos_distance_cm(uint16_t timeout_us);
