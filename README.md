# Button Debounce
An interrupt driven key / button / switch debounce module for the ESP32 microcontroller series. It has been written using the Espressif ESP IDF. It features click / double click and hold detection for multiple buttons and has been written to be easily portable and re-used in your own projects.
## Development Environment
This code was developed using Microsoft Visual Studio Code using a Windows 11 platform, and has been compiled and tested using the ESP-IDF extension for VSC. The latest stable version of the ESP IDF at the time of development was v5.3.1, although the code uses API functions that are present in many older versions of the ESP IDF and so should compile and run successfully with those. An ESP32-DevKitC board was used for testing and development, although this code should run on any ESP32 controller environment with the correct toolchain setup and choice of GPIOs.
## Configuration
The lines of code that need to be configured for use in your project have been commented in the code, but some further explanation is given here.
### button_debounce.h
```
#define NUM_BUTTONS (2)                     // Number of buttons or switches to monitor
```
Simply change the value to match the number of switches or buttons that you wish to use
```
#define GPIO_BUTTON_1 (34)                  // GPIO number of button 1
#define GPIO_BUTTON_2 (35)                  // GPIO number of button 2
```
Set the GPIO numbers that you intend to use here, duplicating or deleting the lines as necessary for more or less inputs
```
#define PULL_MODE GPIO_FLOATING             // No internal pull-up resistors are used - means external pull-up or pull-down resistors should be used
```
The code as written assumes that external pull-up or pull-down resistors are used in your project. If this is not the case then PULL_MODE to either GPIO_PULLUP_ONLY or GPIO_PULLDOWN_ONLY as needed. Note that as written the button debouncer assumes that all inputs are set the same way. If this is not the case, then you will have to modify the gpio configuration code in button_debounce_init() accordingly.
```
#define DEBOUNCE_PERIOD (10000)             // 10ms debounce period
```
The 10ms value used here should work for many use cases, but can be adjusted if necessary. Typical values would be in the range 5ms to 20ms. Value is in microseconds (us).
```
#define DOUBLE_CLICK_PERIOD (500000)        // 500ms timeout to trigger a double click event
```
This is the length of time after an initial button click that it is possible to click a second time to register a double-click event. Again, change this if you wish. Value is in microseconds (us).
```
#define HOLD_PERIOD (2000000)               // 2s button hold trigger
```
The length of time that a button needs to be held down for in order to trigger the hold event. Change to suit your application. Value is in microseconds (us).
```
#define HOLD_CLICK_REPEAT_PERIOD (200000)   // 200ms delay between repeated clicks when button is held
```
Once the hold event has been triggered, the click event will be repeatedly triggered while ever the button is still held down. This is to emulate the typical behaviour of a computer keyboard. The value hear determines how frequently the event is triggered. Value is in microseconds (us).
### button_debounce.c
```
static void button_event_task(void *arg)
{
    button_event_t ev;
    while (true)
    {
        if (xQueueReceive(button_event_queue, &ev, portMAX_DELAY))
        {
            ESP_LOGI(TAG_BUTTON_DEBOUNCE, "button: %d state: %s", ev.button_number, ev.button_state == BUTTON_UP ? "up" : ev.button_state == BUTTON_DOWN       ? "down"
                                                                                                                      : ev.button_state == BUTTON_CLICK        ? "click"
                                                                                                                      : ev.button_state == BUTTON_DOUBLE_CLICK ? "double-click"
                                                                                                                                                               : "hold");
            /* Add code here to detect button events and call your own functions
            e.g.
            if(ev.button_number == 0 && ev.button_state = BUTTON_CLICK)
            {
                your_function();
            }
            */
        }
    }
}
```
As indicated by the comments, this is where you should add the functionality from your own project that should be triggered by the button events. The ev.button_number values will start at 0 for your first button, going on to 1, 2, 3 etc. according to how many buttons you have. The order of the buttons is determined in the code block described below. If you only have a small number of button / event combinations to detect then a few if statements will probably be ok here, but if your needs are more extensive, then a switch / case block might be better.
```
    // Repeat these code blocks as needed, once per button. Configure each option as you wish.
    buttons[0].gpio = GPIO_BUTTON_1;
    buttons[0].active_high = false;
    buttons[0].double_click_detection = true;
    buttons[0].hold_detection = true;
    buttons[0].repeat_on_hold = true;

    buttons[1].gpio = GPIO_BUTTON_2;
    buttons[1].active_high = false;
    buttons[1].double_click_detection = true;
    buttons[1].hold_detection = true;
    buttons[1].repeat_on_hold = true;
    // End of button configuration code blocks
```
This code block determines the order and ev.button_number values that each of your buttons will have. You will need to set the GPIO number of each of your button inputs as well as well they are active high or low. The example here uses external pull-up resistors on each button, so the buttons are configured as active low. If double-click or hold event detection are not required, then they may be disabled here as can the repeated click event functionality of the hold state.

Hopefully you find the code easy to use and useful in your own projects!