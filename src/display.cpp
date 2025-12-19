#include "headers/display.h"

void digits_off(void) {
  DIG_PORT &= ~((1 << DIG1) | (1 << DIG2));
}

void digit_on(uint8_t digit) {
  if (digit == 1) DIG_PORT |= (1 << DIG1);
  else            DIG_PORT |= (1 << DIG2);
}

void digit_off(uint8_t digit) {
  if (digit == 1) DIG_PORT &= ~(1 << DIG1);
  else            DIG_PORT &= ~(1 << DIG2);
}


void seg_apply_mask(uint8_t on_mask) {
  SEG_PORT = (uint8_t)~on_mask;
}

void seg_all_off(void) { seg_apply_mask(0x00); }  
void seg_all_on(void)  { seg_apply_mask(0xFF); }  