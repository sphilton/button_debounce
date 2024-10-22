#ifndef BUTTON_DEBOUNCE_H
#define BUTTON_DEBOUNCE_H

#include <stdint.h>
#include "esp_err.h"
#include "esp_timer.h"
#include "driver/gpio.h"

#define NUM_BUTTONS (2)
#define GPIO_BUTTON_1 (34)
#define GPIO_BUTTON_2 (35)
#define PULL_MODE GPIO_FLOATING
#define DEBOUNCE_PERIOD (10000)     // 10ms debounce period
#define HOLD_PERIOD (2000000)       // 2s button hold trigger
#define HOLD_CLICK_REPEAT_PERIOD (200000) // 200ms delay between repeated clicks when button is held
#define BUTTON_EVENT_QUEUE_LENGTH (10)

esp_err_t button_debounce_init();

#endif