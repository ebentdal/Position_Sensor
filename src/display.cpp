#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "display.h"


#define DIG1       PB0
#define DIG2       PB1

uint8_t seg_char(char c) {
  switch (c) {
    case '0': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F;
    case '1': return SEG_B|SEG_C;
    case '2': return SEG_A|SEG_B|SEG_D|SEG_E|SEG_G;
    case '3': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_G;
    case '4': return SEG_F|SEG_G|SEG_B|SEG_C;
    case '5': return SEG_A|SEG_F|SEG_G|SEG_C|SEG_D;
    case '6': return SEG_A|SEG_F|SEG_E|SEG_D|SEG_C|SEG_G;
    case '7': return SEG_A|SEG_B|SEG_C;
    case '8': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;
    case '9': return SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G;

    default:            return 0x00; 
  }
}


void display_init() {
    
    DDRD = 0xFF;
    DDRB |= (1 << PB0) | (1 << PB1);
    digits_off();
    seg_all_off();
}

void digit_on(uint8_t digit) {
    if (digit == 1) PORTB |= (1 << DIG1);
    else            PORTB |= (1 << DIG2);
}
void digits_off(void) {
  PORTB &= ~((1 << DIG1) | (1 << DIG2));
}


void display_chars(char left, char right, uint16_t ms) {
  while (ms--) {

    digits_off();
    seg_apply_mask(seg_char(left));
    digit_on(1);
    _delay_ms(2);


    digits_off();
    seg_apply_mask(seg_char(right));
    digit_on(2);
    _delay_ms(2);
  }
  digits_off();
  seg_all_off();
}

void display_cm(uint8_t value, uint16_t ms) {
  char tens = (value >= 10) ? ('0' + (value / 10)) : ' ';   
  char ones = '0' + (value % 10);
  display_chars(tens, ones, ms);
}



void seg_apply_mask(uint8_t on_mask) {
  PORTD = (uint8_t)~on_mask;
}

void seg_all_off(void) { seg_apply_mask(0x00); }  


