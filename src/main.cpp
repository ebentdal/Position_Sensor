#include <avr/io.h>
#include <util/delay.h>
#include "config.h"
#include "display.h"
#include "possensor.h"
#include "timer.h"

// static void hw_init_minimal_for_A_only() {
//   DDRB |= (1 << PB0) | (1 << PB1);

//   DDRD |= (1 << PD0);

//   digits_off();
//   seg_all_off();
// }

// int main(void) {
//     hw_init_minimal_for_A_only();
//     while(1) {
//         digits_off();                
//         seg_all_off();                
//         seg_apply_mask(SEG_A);        
//         digit_on(1);
//         _delay_ms(500);

//         // --- Digit 2: A on ---
//         digits_off();
//         seg_all_off();
//         seg_apply_mask(SEG_A);
//         seg_apply_mask(SEG_B);
//         seg_apply_mask(SEG_C);
//         seg_apply_mask(SEG_D);
//         seg_apply_mask(SEG_E);
//         seg_apply_mask(SEG_F);
//         seg_apply_mask(SEG_G);
//         seg_apply_mask(SEG_DP);
//         digit_on(2);
//         _delay_ms(500);

//         // --- All off pause ---
//         digits_off();
//         seg_all_off();
//         _delay_ms(200);
//     }
// }
  
static void hw_init_display_only() {
  // Segments PD0..PD7 output
  DDRD = 0xFF;

  // Digits PB0/PB1 output
  DDRB |= (1 << PB0) | (1 << PB1);

  digits_off();
  seg_all_off();
}

static void show_mask_on_digit(uint8_t digit, uint8_t mask, uint16_t ms) {
  digits_off();         
  seg_all_off();
  seg_apply_mask(mask);  
  digit_on(digit);

  while (ms--) _delay_ms(1);

  digits_off();
  seg_all_off();
}

static void sweep_segments(uint8_t digit, uint16_t per_seg_ms) {
  const uint8_t segs[] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, SEG_DP };
  for (uint8_t i = 0; i < sizeof(segs); i++) {
    show_mask_on_digit(digit, segs[i], per_seg_ms);
    _delay_ms(50);
  }
}

static uint8_t mask_for_digit_char(char c) {
  return seg_char(c);
}

static void multiplex_two_chars(char left, char right, uint16_t total_ms) {

  while (total_ms--) {
    digits_off();
    seg_apply_mask(mask_for_digit_char(left));
    digit_on(1);
    _delay_ms(2);

    digits_off();
    seg_apply_mask(mask_for_digit_char(right));
    digit_on(2);
    _delay_ms(2);
  }
  digits_off();
  seg_all_off();
}

int main(void) {
  hw_init_display_only();

  

  // 3) Test “alt på” (88), deretter “00”, deretter “12”
  while (1) {
    

    multiplex_two_chars('2', '5', 1000);
    _delay_ms(2);
    
    
  }
}