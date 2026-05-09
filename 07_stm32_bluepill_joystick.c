/* Joystick Test — STM32F103 BluePill (STM32 HAL / C)
 * Wiring: VCC->3.3V, GND->GND, VRX->PA0 (ADC1_IN0), VRY->PA1 (ADC1_IN1), SW->PB0
 * Include this function in your main.c and call joystick_test_loop() from main().
 * Requires: hadc1 and huart1 initialized by CubeMX.
 */

#include "stm32f1xx_hal.h"
#include <string.h>
#include <stdio.h>

extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;

static uint32_t readChannel(uint32_t ch) {
  ADC_ChannelConfTypeDef cfg = {0};
  cfg.Channel      = ch;
  cfg.Rank         = ADC_REGULAR_RANK_1;
  cfg.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  HAL_ADC_ConfigChannel(&hadc1, &cfg);
  HAL_ADC_Start(&hadc1);
  HAL_ADC_PollForConversion(&hadc1, 10);
  return HAL_ADC_GetValue(&hadc1);
}

void joystick_test_loop(void) {
  char msg[] = "Joystick Test: STM32F103 BluePill\r\n";
  HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 100);

  char buf[64];
  while (1) {
    uint32_t x  = readChannel(ADC_CHANNEL_0);  // PA0
    uint32_t y  = readChannel(ADC_CHANNEL_1);  // PA1
    uint8_t  sw = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET;

    snprintf(buf, sizeof(buf), "X:%4lu  Y:%4lu  BTN:%s\r\n",
             x, y, sw ? "PRESSED" : "open");
    HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(buf), 100);
    HAL_Delay(200);
  }
}
