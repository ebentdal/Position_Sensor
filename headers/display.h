#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>

#define SEG_PORT   PORTD
#define SEG_DDR    DDRD


#define DIG_PORT   PORTB
#define DIG_DDR    DDRB
#define DIG1       PB0
#define DIG2       PB1

void digits_off(void);
void digit_on(uint8_t digit);
void digit_off(uint8_t digit);

void seg_apply_mask(uint8_t on_mask);

void seg_all_off(void);
void seg_all_on(void);

enum {
  SEG_A  = (1 << 0),
  SEG_B  = (1 << 1),
  SEG_C  = (1 << 2),
  SEG_D  = (1 << 3),
  SEG_E  = (1 << 4),
  SEG_F  = (1 << 5),
  SEG_G  = (1 << 6),
  SEG_DP = (1 << 7),
};


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
    case 'b':           return SEG_C|SEG_D|SEG_E|SEG_F|SEG_G;      // lowercase b
    case 'C': case 'c': return SEG_A|SEG_D|SEG_E|SEG_F;
    case 'd':           return SEG_B|SEG_C|SEG_D|SEG_E|SEG_G;      // lowercase d
    case 'E': case 'e': return SEG_A|SEG_D|SEG_E|SEG_F|SEG_G;
    case 'F': case 'f': return SEG_A|SEG_E|SEG_F|SEG_G;
    case 'H': case 'h': return SEG_B|SEG_C|SEG_E|SEG_F|SEG_G;
    case 'L': case 'l': return SEG_D|SEG_E|SEG_F;
    case 'P': case 'p': return SEG_A|SEG_B|SEG_E|SEG_F|SEG_G;
    case 'U': case 'u': return SEG_B|SEG_C|SEG_D|SEG_E|SEG_F;

    case '-':           return SEG_G;
    case '_':           return SEG_D;
    case ' ':           return 0x00; // blank

    default:            return 0x00; // unknown -> blank
  }
}