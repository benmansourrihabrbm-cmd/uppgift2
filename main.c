#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

/* Masker för de fyra lysdioderna på PB0–PB3 */
#define LED_RED_MASK     _BV(PB0)
#define LED_GREEN_MASK   _BV(PB1)
#define LED_BLUE_MASK    _BV(PB2)
#define LED_YELLOW_MASK  _BV(PB3)

/* Alla fyra LED-bitarna tillsammans: 0000 1111 */
#define ALL_LEDS_MASK    (LED_RED_MASK | LED_GREEN_MASK | \
                          LED_BLUE_MASK | LED_YELLOW_MASK)

void leds_init(void)
{
    /* PB0–PB3 blir utgångar */
    DDRB |= (uint8_t)ALL_LEDS_MASK;

    /* PB0–PB3 blir låga, alla lysdioder börjar släckta */
    PORTB &= (uint8_t)~ALL_LEDS_MASK;
}

int main(void)
{
    leds_init();

    while (1)
    {
        /* 1. Röda lysdioden tänds */
        PORTB |= (uint8_t)LED_RED_MASK;
        _delay_ms(500);

        /* 2. Gröna lysdioden tänds utan att röda släcks */
        PORTB |= (uint8_t)LED_GREEN_MASK;
        _delay_ms(500);

        /* 3. Röda lysdioden släcks utan att gröna påverkas */
        PORTB &= (uint8_t)~LED_RED_MASK;
        _delay_ms(500);

        /* 4. Blåa lysdioden växlar tillstånd */
        PORTB ^= (uint8_t)LED_BLUE_MASK;
        _delay_ms(500);

        /* 5. Gula lysdioden tänds */
        PORTB |= (uint8_t)LED_YELLOW_MASK;
        _delay_ms(500);

        /* 6. Alla fyra lysdioder släcks */
        PORTB &= (uint8_t)~ALL_LEDS_MASK;
        _delay_ms(500);
    }

    return 0;
}