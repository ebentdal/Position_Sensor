#include <avr/io.h>
#include <util/delay.h>
#include "config.h"
#include "display.h"
#include "possensor.h"
#include "timer.h"

  

int main(void) {
    display_init();
    pos_init();


    while (1) {
        uint16_t cm = pos_distance_cm(30000);
        uint8_t show = (cm > 99) ? 99 : (uint8_t)cm;
        display_cm(show, 70);
        
        
    
  }
}