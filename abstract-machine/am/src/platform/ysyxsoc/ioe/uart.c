#include <am.h>
#include <ysyxsoc.h>
#include <klib-macros.h>

void __am_uart_config(AM_UART_CONFIG_T *cfg) { cfg->present = true; }

void __am_uart_tx(AM_UART_TX_T *tx) {
  putch(tx->data);
}

void __am_uart_rx(AM_UART_RX_T *rx) {
  while (!(inb(UART_16550_LSR) & 1)) {
  }
  char c = inb(SERIAL_PORT);
  if (c >= 127 || c < 32) {
    rx->data = 0xff;
  } else {
    rx->data = c;
   // putch(rx->data);
  }
  outb(UART_16550_FCR, inb(UART_16550_FCR) | 0b010);

}
