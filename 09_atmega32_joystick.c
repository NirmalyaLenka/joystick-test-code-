/* Joystick Test — ATmega32 bare-metal (AVR-C)
 * Wiring: VCC->5V, GND->GND, VRX->PA0 (ADC0), VRY->PA1 (ADC1), SW->PD2
 * Compile: avr-gcc -mmcu=atmega32 -DF_CPU=8000000UL -Os -o joystick.elf joystick.c
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

static void uart_init(void) {
  UBRRL = 51; UBRRH = 0;   // 9600 baud @ 8 MHz
  UCSRB = (1 << TXEN);
  UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

static void uart_putch(char c) {
  while (!(UCSRA & (1 << UDRE)));
  UDR = c;
}

static void uart_puts(const char *s) {
  while (*s) uart_putch(*s++);
}

static uint16_t adc_read(uint8_t ch) {
  ADMUX  = (1 << REFS0) | (ch & 0x07);  // AVcc ref, select channel
  ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1); // prescale 64
  while (ADCSRA & (1 << ADSC));
  return ADC;
}

int main(void) {
  uart_init();
  DDRD  &= ~(1 << PD2);   // SW as input
  PORTD |=  (1 << PD2);   // enable pull-up

  uart_puts("Joystick Test: ATmega32\r\n");

  char buf[40];
  while (1) {
    uint16_t x  = adc_read(0);
    uint16_t y  = adc_read(1);
    uint8_t  sw = !(PIND & (1 << PD2));

    snprintf(buf, sizeof(buf), "X:%4u  Y:%4u  BTN:%s\r\n",
             x, y, sw ? "PRESSED" : "open");
    uart_puts(buf);
    _delay_ms(200);
  }
}
