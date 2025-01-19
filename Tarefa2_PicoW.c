#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BUZZER 21

void configurar_gpio()
{
    printf("Configurando GPIO...\n");
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
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
    printf("Todos os LEDs apagados.\n");
}

void controlar_led(const char *comando)
{
    apagar_leds();
    if (strcmp(comando, "verde") == 0)
    {
        gpio_put(LED_VERDE, 1);
        printf("LED verde acionado.\n");
    }
    else if (strcmp(comando, "azul") == 0)
    {
        gpio_put(LED_AZUL, 1);
        printf("LED azul acionado.\n");
    }
    else if (strcmp(comando, "vermelho") == 0)
    {
        gpio_put(LED_VERMELHO, 1);
        printf("LED vermelho acionado.\n");
    }
    else if (strcmp(comando, "branco") == 0)
    {
        gpio_put(LED_VERDE, 1);
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERMELHO, 1);
        printf("Todos os LEDs acionados (branco).\n");
    }
}

void controlar_buzzer()
{
    gpio_put(BUZZER, 1);
    printf("Buzzer acionado.\n");
    sleep_ms(2000);
    gpio_put(BUZZER, 0);
    printf("Buzzer desligado.\n");
}

int main()
{
    stdio_init_all();
    configurar_gpio();

    printf("Aguardando comando via serial...\n");

    char comando[20];
    int comando_index = 0;
    char ch;

    while (1)
    {
        // Aguarda por um caractere de entrada (bloqueia até que um caractere seja recebido)
        ch = getchar();

        // Verifica se o caractere é Enter (nova linha ou retorno de carro)
        if (ch == '\n' || ch == '\r')
        {
            comando[comando_index] = '\0'; // Finaliza a string
            comando_index = 0;             // Reseta o índice para o próximo comando

            // Executa a ação baseada no comando recebido
            if (strcmp(comando, "verde") == 0 || strcmp(comando, "azul") == 0 ||
                strcmp(comando, "vermelho") == 0 || strcmp(comando, "branco") == 0)
            {
                controlar_led(comando);
            }
            else if (strcmp(comando, "buzz") == 0)
            {
                controlar_buzzer();
            }
            else if (strcmp(comando, "off") == 0)
            {
                apagar_leds();
            }
            else if (strcmp(comando, "exit") == 0)
            {
                printf("Saindo do programa.\n");
                break; // Encerra o programa
            }
            else
            {
                printf("Comando desconhecido: %s\n", comando);
            }
        }
        else if (ch == 0x08 || ch == 0x7F) // Tratar o backspace
        {
            if (comando_index > 0)
            {
                comando_index--; // Remove o último caractere do comando
                printf("\b \b"); // Apaga o último caractere do terminal
            }
        }
        else
        {
            // Adiciona o caractere ao buffer do comando
            if (comando_index < sizeof(comando) - 1)
            {
                comando[comando_index++] = ch;
                putchar(ch); // Imprime o caractere no terminal
            }
        }
    }

    return 0;
}
