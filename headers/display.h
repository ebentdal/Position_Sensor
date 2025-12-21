#include <stdint.h>
#include <stdbool.h>

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

void display_init();

void display_cm(uint8_t value, uint16_t ms);
void display_chars(char left, char right, uint16_t ms);

void digits_off(void);
void digit_on(uint8_t digit);
void digit_off(uint8_t digit);

void seg_apply_mask(uint8_t on_mask);

void seg_all_off(void);
void seg_all_on(void);

uint8_t seg_char(char c);