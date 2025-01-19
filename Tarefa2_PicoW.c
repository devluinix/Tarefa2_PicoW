#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13
#define BUZZER 21

void configure_gpio()
{
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
}

void turn_off_leds()
{
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
}

void control_led(const char *command)
{
    turn_off_leds();
    if (strcmp(command, "green") == 0)
    {
        gpio_put(LED_GREEN, 1);
    }
    else if (strcmp(command, "blue") == 0)
    {
        gpio_put(LED_BLUE, 1);
    }
    else if (strcmp(command, "red") == 0)
    {
        gpio_put(LED_RED, 1);
    }
    else if (strcmp(command, "white") == 0)
    {
        gpio_put(LED_GREEN, 1);
        gpio_put(LED_BLUE, 1);
        gpio_put(LED_RED, 1);
    }
}

void control_buzzer(const char *command)
{
    if (strcmp(command, "buzz") == 0)
    {
        gpio_put(BUZZER, 1);
        sleep_ms(2000);
        gpio_put(BUZZER, 0);
    }
}

int main()
{
    stdio_init_all();
    configure_gpio();

    while (1)
    {
        char command[10];
        scanf("%9s", command);

        if (strcmp(command, "green") == 0 || strcmp(command, "blue") == 0 ||
            strcmp(command, "red") == 0 || strcmp(command, "white") == 0)
        {
            control_led(command);
        }
        else if (strcmp(command, "buzz") == 0)
        {
            control_buzzer(command);
        }
        else if (strcmp(command, "off") == 0)
        {
            turn_off_leds();
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
    }

    return 0;
}
