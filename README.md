### Controle de LEDs e Buzzer via Comandos Seriais

**Descrição**

Neste projeto, foi implementado um controle de LEDs RGB e buzzer utilizando um microcontrolador RP2040, presente na placa de desenvolvimento Raspberry Pi Pico W, com a entrada de comandos via comunicação serial. O código foi desenvolvido em linguagem C e permite a interação com o hardware utilizando comandos enviados através do terminal serial. Os seguintes componentes foram utilizados:

- 1 LED RGB
- Componente Buzzer
- Microcontrolador Raspberry Pi Pico W

**Funcionalidades**

O código implementa o controle dos LEDs e do buzzer através de comandos simples enviados via terminal serial. As funcionalidades disponíveis são:

- **Comando "green"**: Acende o LED verde.
- **Comando "blue"**: Acende o LED azul.
- **Comando "red"**: Acende o LED vermelho.
- **Comando "white"**: Acende todos os LEDs (branco).
- **Comando "buzz"**: Aciona o buzzer para um som intermitente.
- **Comando "off"**: Desliga todos os LEDs.
- **Comando "exit"**: Encerra o programa.

- [Vídeo de Demonstração](https://youtube.com/shorts/5AZ3WJBEfeg?feature=share)

## Objetivo

O objetivo deste projeto foi fornecer uma interface simples para controlar os LEDs RGB e o buzzer do Raspberry Pi Pico W através de comandos seriais, permitindo o controle de hardware de forma prática e eficaz.

## Como compilar
Para compilar o programa, utilize um compilador C, e rode o código para geração do arquivo `.uf2` e `.elf`. Segue um exemplo:

## Como executar
Após a compilação, execute o simulador Wokwi clicando no arquivo `diagram.json`:

Para testar, só clicar no play e explorar o circutio.

## Requisitos
- Compilador C (gcc ou equivalente).
- Sistema operacional compatível com programas C.
- Extensão Raspberry Pi Pico 
- Wokwi conectado no VS Code

## Demonstração

Após carregar o código no Raspberry Pi Pico W, você pode testar as funcionalidades do sistema enviando os comandos via terminal. O comportamento dos LEDs e do buzzer pode ser observado diretamente na placa.

**Equipe de Desenvolvimento**

Equipe 2 - Grupo 3 - EmbarcaTech
- [Luiz Marcelo](https://github.com/devluinix)
