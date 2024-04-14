#ifndef __YSYXSOC_H__
#define __YSYXSOC_H__

#include ISA_H

// #define DEVICE_BASE 0x02000000

// #define MMIO_BASE 0x02000000

#define SERIAL_PORT     (0x10000000)
#define UART_16550_IER  (SERIAL_PORT + 0x01)  // Interrupt Enable
#define UART_16550_IID  (SERIAL_PORT + 0x02)  // Interrupt ID
#define UART_16550_FCR  (SERIAL_PORT + 0x02) //
#define UART_16550_LCR  (SERIAL_PORT + 0x3)  
#define UART_16550_MCR  (SERIAL_PORT + 0x4)
#define UART_16550_LSR  (SERIAL_PORT + 0x5)
#define UART_16550_MSR  (SERIAL_PORT + 0x6)
#define UART_16550_DLL  (SERIAL_PORT)
#define UART_16550_DLH  (SERIAL_PORT + 1)
#define KBD_ADDR        (0x10011000)
#define RTC_ADDR        (0x02000000)
// #define VGACTL_ADDR     (DEVICE_BASE + 0x0000100)
// #define AUDIO_ADDR      (DEVICE_BASE + 0x0000200)
// #define DISK_ADDR       (DEVICE_BASE + 0x0000300)
// #define FB_ADDR         (MMIO_BASE   + 0x1000000)
// #define AUDIO_SBUF_ADDR (MMIO_BASE   + 0x1200000)

#endif