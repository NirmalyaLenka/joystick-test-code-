/* Joystick Test — ATtiny85 (AVR-C, bit-bang UART)
 * Wiring: VCC->5V, GND->GND, VRX->PB2/ADC1 (pin7), VRY->PB3/ADC3 (pin2),
 *         SW->PB4 (pin3), TX->PB1 (pin6) -> USB-Serial adapter RX
 * Compile: avr-gcc -mmcu=attiny85 -DF_CPU=8000000UL -Os -o joy.elf joy.c
 * Fuses:   LFUSE=0xE2 (8 MHz internal RC, no div8)
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define TX_PIN  PB1
#define SW_PIN  PB4
#define BAUD_US 104   /* 1/9600 * 1e6 */

static void tx_byte(uint8_t b) {
  PORTB &= ~(1 << TX_PIN);          // start bit
  _delay_us(BAUD_US);
  for (uint8_t i = 0; i < 8; i++) {
    if (b & 1) PORTB |=  (1 << TX_PIN);
    else        PORTB &= ~(1 << TX_PIN);
    _delay_us(BAUD_US);
    b >>= 1;
  }
  PORTB |= (1 << TX_PIN);           // stop bit
  _delay_us(BAUD_US);
}

static void tx_str(const char *s) { while (*s) tx_byte((uint8_t)*s++); }

static uint8_t adc_read(uint8_t ch) {
  ADMUX  = (1 << ADLAR) | (ch & 0x03);  // left-adjust, select channel
  ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS1) | (1 << ADPS0);
  while (ADCSRA & (1 << ADSC));
  return ADCH;   // 8-bit result
}

int main(void) {
  DDRB  |=  (1 << TX_PIN);   PORTB |=  (1 << TX_PIN);  // TX idle HIGH
  DDRB  &= ~(1 << SW_PIN);   PORTB |=  (1 << SW_PIN);  // SW pull-up

  tx_str("Joystick Test: ATtiny85\r\n");

  char    buf[24];
  uint8_t x, y, sw;

  while (1) {
    x  = adc_read(1);                    // PB2/ADC1
    y  = adc_read(3);                    // PB3/ADC3
    sw = !(PINB & (1 << SW_PIN));

    snprintf(buf, sizeof(buf), "X:%3u  Y:%3u  %s\r\n",
             x, y, sw ? "BTN:PRESSED" : "BTN:open");
    tx_str(buf);
    _delay_ms(300);
  }
}
