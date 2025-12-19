#include <avr/io.h>
#include <util/delay.h>




int main(void) {
  // Digit anoder (common anode): HIGH = on
  DDRB |= (1 << PB0) | (1 << PB1);

  // Segment A cathodes for digit1/digit2: LOW = on
  DDRD |= (1 << PD0) | (1 << PD1);

  // Slå av alt (digits off, segments off)
  PORTB &= ~((1 << PB0) | (1 << PB1));      // digits OFF
  PORTD |=  (1 << PD0) | (1 << PD1);        // segments OFF (cathodes HIGH)

  while (1) {
    // ---- Digit 1: A on ----
    PORTB &= ~((1 << PB0) | (1 << PB1));    // digits OFF (unngå ghosting)
    PORTD |=  (1 << PD0) | (1 << PD0);      // segments OFF
    PORTD &= ~(1 << PD0);                   // A1 ON (LOW)
    PORTB |=  (1 << PB0);                   // digit1 ON
    _delay_ms(500);

    // ---- Digit 2: A on ----
    //PORTB &= ~((1 << PB0) | (1 << PB1));    // digits OFF
    PORTD |=  (1 << PD0) | (1 << PD1);      // segments OFF
    PORTD &= ~(1 << PD0);                   // A2 ON (LOW)
    PORTB |=  (1 << PB1);                   // digit2 ON
    _delay_ms(500);
  }
}
