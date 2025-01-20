#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BUZZER 21

void configurar_gpio()
{
    // Inicializa LEDs e buzzer como saída
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);

    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
}

void apagar_leds()
{
    // Desliga todos os LEDs
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
}

void controlar_led(const char *comando)
{
    apagar_leds(); // Apaga todos os LEDs antes de acionar o especificado

    if (strcmp(comando, "green") == 0)
        gpio_put(LED_VERDE, 1);
    else if (strcmp(comando, "blue") == 0)
        gpio_put(LED_AZUL, 1);
    else if (strcmp(comando, "red") == 0)
        gpio_put(LED_VERMELHO, 1);
    else if (strcmp(comando, "white") == 0)
    {
        gpio_put(LED_VERDE, 1);
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERMELHO, 1);
    }
}

void controlar_buzzer()
{
    // Toca o buzzer por 1 segundo (alternando entre on e off)
    for (int i = 0; i < 10; i++)
    {
        gpio_put(BUZZER, 1); // Liga o buzzer
        sleep_ms(50);        // Atraso
        gpio_put(BUZZER, 0); // Desliga o buzzer
        sleep_ms(50);        // Atraso
    }
}

int main()
{
    stdio_init_all();  // Inicializa a entrada/saída padrão
    configurar_gpio(); // Configura os pinos GPIO

    char comando[20]; // Buffer para armazenar o comando
    int comando_index = 0;
    char ch;

    while (1)
    {
        // Espera pelo comando via serial
        ch = getchar();

        // Se o comando for enter, executa a ação
        if (ch == '\n' || ch == '\r')
        {
            printf("\nComando: %s\n", comando);
            comando[comando_index] = '\0'; // Finaliza a string
            comando_index = 0;

            if (strcmp(comando, "green") == 0 ||
                strcmp(comando, "blue") == 0 ||
                strcmp(comando, "red") == 0 ||
                strcmp(comando, "white") == 0)
            {
                controlar_led(comando); // Aciona o LED
            }
            else if (strcmp(comando, "buzz") == 0)
            {
                controlar_buzzer(); // Toca o buzzer
            }
            else if (strcmp(comando, "off") == 0)
            {
                apagar_leds(); // Desliga todos os LEDs
            }
            else if (strcmp(comando, "exit") == 0)
            {
                printf("Saindo...\n");
                break; // Encerra o programa
            }
            else
            {
                printf("Comando desconhecido: %s\n", comando);
            }
        }
        else if (ch == 0x08 || ch == 0x7F) // Backspace
        {
            if (comando_index > 0)
            {
                comando_index--; // Remove o último caractere
                printf("\b \b"); // Apaga o caractere do terminal
            }
        }
        else
        {
            // Adiciona o caractere ao comando
            if (comando_index < sizeof(comando) - 1)
            {
                comando[comando_index++] = ch;
                putchar(ch); // Exibe no terminal
            }
        }
    }

    return 0;
}
