/*
  This is a hardware abstraction layer, it tells the library how to use the
  serial port using the Raspberry Pi Pico SDK.
*/
#include "DYPlayerPico.h"
#include "pico/stdlib.h"
#include <stdio.h>

namespace DY {

void Player::begin() {
    uart_init(this->instance, 9600);

    // Set the TX and RX pins by using the function select on the GPIO
    gpio_set_function(this->txPin, GPIO_FUNC_UART);
    gpio_set_function(this->rxPin, GPIO_FUNC_UART);

    // Set the desired baud rate and log the one we actually got
    uint actualRate = uart_set_baudrate(this->instance, 9600);
    printf("Got actual baud rate %d\n", actualRate);

    // Disable UART flow control CTS/RTS
    uart_set_hw_flow(this->instance, false, false);

    // Set our data format
    uart_set_format(this->instance, 8, 1, UART_PARITY_NONE);

    // Turn on FIFOs
    uart_set_fifo_enabled(this->instance, true);
}

void Player::serialWrite(uint8_t *buffer, uint8_t len) {
    for (size_t i = 0; i < len; i++) {
        uart_putc_raw(this->instance, buffer[i]);
    }
}

bool Player::serialRead(uint8_t *buffer, uint8_t len) {
    uart_read_blocking(this->instance, buffer, len);
}

} // namespace DY
