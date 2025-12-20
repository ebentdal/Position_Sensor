#define F_CPU 8000000UL


#define DISPLAY_COMMON_ANODE 1


#define SEG_PORT   PORTD
#define SEG_DDR    DDRD
#define SEG_PIN_A  PD0
#define SEG_PIN_B  PD1
#define SEG_PIN_C  PD2
#define SEG_PIN_D  PD3
#define SEG_PIN_E  PD4
#define SEG_PIN_F  PD5
#define SEG_PIN_G  PD6
#define SEG_PIN_DP PD7

#define DIG_PORT   PORTB
#define DIG_DDR    DDRB
#define DIG1_PIN   PB0  
#define DIG2_PIN   PB1   


#define TRIG_PORT  PORTC
#define TRIG_DDR   DDRC
#define TRIG_PIN   PC0

#define ECHO_PINREG PINC
#define ECHO_PORT   PORTC
#define ECHO_DDR    DDRC
#define ECHO_PIN    PC1

#define BUZ_PORT   PORTB
#define BUZ_DDR    DDRB
#define BUZ_PIN    PB2