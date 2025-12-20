#include <avr/io.h>
#include <stdint.h>
#include "display.h"

#define SEG_PORT   PORTD
#define SEG_DDR    DDRD


#define DIG_PORT   PORTB
#define DIG_DDR    DDRB
#define DIG1       PB0
#define DIG2       PB1


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

    case 'A': case 'a': return SEG_A|SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
    case 'b':           return SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;    
    case 'C': case 'c': return SEG_A|SEG_D|SEG_E|SEG_F;
    case 'd':           return SEG_B|SEG_C|SEG_D|SEG_E|SEG_G;     
    case 'E': case 'e': return SEG_A|SEG_D|SEG_E|SEG_F|SEG_G;
    case 'F': case 'f': return SEG_A|SEG_E|SEG_F|SEG_G;
    case 'H': case 'h': return SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
    case 'L': case 'l': return SEG_D|SEG_E|SEG_F;
    case 'P': case 'p': return SEG_A|SEG_B|SEG_E|SEG_F|SEG_G;
    case 'U': case 'u': return SEG_B|SEG_C|SEG_D|SEG_E|SEG_F;

    case '-':           return SEG_G;
    case '_':           return SEG_D;
    case ' ':           return 0x00; 

    default:            return 0x00; 
  }
}