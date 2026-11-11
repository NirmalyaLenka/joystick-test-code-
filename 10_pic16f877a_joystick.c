/* Joystick Test — PIC16F877A (MPLAB XC8)
 * Wiring: VCC->5V, GND->GND, VRX->RA0/AN0, VRY->RA1/AN1, SW->RB0
 * Config: 20MHz HS oscillator. Add this file to your MPLAB X project.
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP  = OFF

#define _XTAL_FREQ  20000000UL
#define SW          RB0

static void uart_init(void) {
  SPBRG = 129;    // Approximately 9600 baud @ 20 MHz with BRGH=1
  BRGH  = 1;      // High-speed asynchronous mode: 20 MHz / (16 * (129 + 1))
  TXEN  = 1;
  SPEN  = 1;
}

static void uart_putch(char c) {
  while (!TXIF);
  TXREG = c;
}

static void uart_puts(const char *s) {
  while (*s) uart_putch(*s++);
}

static uint16_t adc_read(uint8_t ch) {
  ADCON0 = (uint8_t)((ch << 3) | 0x81);  // Fosc/32, selected channel, ADON=1
  __delay_us(20);
  GO = 1;
  while (GO);
  // ADCON1 below selects right-justified 10-bit conversion results.
  return ((uint16_t)ADRESH << 8) | ADRESL;
}

void main(void) {
  TRISA = 0xFF;
  TRISB = 0xFF;
  ADCON1 = 0x80;          // Right justified; Vdd/Vss reference; analog inputs enabled
  OPTION_REGbits.RBPU = 0; // Enable PORTB weak pull-ups for the active-low SW input

  uart_init();
  uart_puts("Joystick Test: PIC16F877A\r\n");

  char buf[32];
  while (1) {
    uint16_t x = adc_read(0);
    uint16_t y = adc_read(1);
    sprintf(buf, "X:%4u  Y:%4u  BTN:%s\r\n",
            x, y, SW ? "open" : "PRESSED");
    uart_puts(buf);
    __delay_ms(200);
  }
}
