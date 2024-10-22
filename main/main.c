#include "esp_err.h"
#include "esp_log.h"
#include "button_debounce.h"

void app_main(void)
{
    if(button_debounce_init() != ESP_OK)
    {
        ESP_LOGE("main", "Button debouncer could not be initialised!");
    }
}
