/**
 * @file
 *
 * @ingroup lpc32xx
 *
 * @brief Console configuration.
 */

/*
 * Copyright (c) 2009
 * embedded brains GmbH
 * Obere Lagerstr. 30
 * D-82178 Puchheim
 * Germany
 * <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#include <libchip/serial.h>
#include <libchip/ns16550.h>

#include <bsp.h>
#include <bsp/lpc32xx.h>
#include <bsp/irq.h>

extern console_fns lpc32xx_hsu_fns;

static uint8_t lpc32xx_uart_get_register(uintptr_t addr, uint8_t i)
{
  volatile uint32_t *reg = (volatile uint32_t *) addr;

  return (uint8_t) reg [i];
}

static void lpc32xx_uart_set_register(uintptr_t addr, uint8_t i, uint8_t val)
{
  volatile uint32_t *reg = (volatile uint32_t *) addr;

  reg [i] = val;
}

#ifdef LPC32XX_UART_3_BAUD
  static bool lpc32xx_uart_probe_3(int minor)
  {
    LPC32XX_UARTCLK_CTRL |= 1U << 0;
    LPC32XX_U3CLK = LPC32XX_CONFIG_U3CLK;

    return true;
  }
#endif

#ifdef LPC32XX_UART_4_BAUD
  static bool lpc32xx_uart_probe_4(int minor)
  {
    LPC32XX_UARTCLK_CTRL |= 1U << 1;
    LPC32XX_U4CLK = LPC32XX_CONFIG_U4CLK;

    return true;
  }
#endif

#ifdef LPC32XX_UART_6_BAUD
  static bool lpc32xx_uart_probe_6(int minor)
  {
    LPC32XX_UARTCLK_CTRL |= 1U << 3;
    LPC32XX_U6CLK = LPC32XX_CONFIG_U6CLK;

    return true;
  }
#endif

/* FIXME: Console selection */

console_tbl Console_Configuration_Ports [] = {
  #ifdef LPC32XX_UART_5_BAUD
    {
      .sDeviceName = "/dev/ttyS5",
      .deviceType = SERIAL_NS16550,
      .pDeviceFns = &ns16550_fns,
      .deviceProbe = NULL,
      .pDeviceFlow = NULL,
      .ulMargin = 16,
      .ulHysteresis = 8,
      .pDeviceParams = (void *) LPC32XX_UART_5_BAUD,
      .ulCtrlPort1 = LPC32XX_BASE_UART_5,
      .ulCtrlPort2 = 0,
      .ulDataPort = LPC32XX_BASE_UART_5,
      .getRegister = lpc32xx_uart_get_register,
      .setRegister = lpc32xx_uart_set_register,
      .getData = NULL,
      .setData = NULL,
      .ulClock = 16 * LPC32XX_UART_5_BAUD,
      .ulIntVector = LPC32XX_IRQ_UART_5
    },
  #endif
  #ifdef LPC32XX_UART_3_BAUD
    {
      .sDeviceName = "/dev/ttyS3",
      .deviceType = SERIAL_NS16550,
      .pDeviceFns = &ns16550_fns,
      .deviceProbe = lpc32xx_uart_probe_3,
      .pDeviceFlow = NULL,
      .ulMargin = 16,
      .ulHysteresis = 8,
      .pDeviceParams = (void *) LPC32XX_UART_3_BAUD,
      .ulCtrlPort1 = LPC32XX_BASE_UART_3,
      .ulCtrlPort2 = 0,
      .ulDataPort = LPC32XX_BASE_UART_3,
      .getRegister = lpc32xx_uart_get_register,
      .setRegister = lpc32xx_uart_set_register,
      .getData = NULL,
      .setData = NULL,
      .ulClock = 16 * LPC32XX_UART_3_BAUD,
      .ulIntVector = LPC32XX_IRQ_UART_3
    },
  #endif
  #ifdef LPC32XX_UART_4_BAUD
    {
      .sDeviceName = "/dev/ttyS4",
      .deviceType = SERIAL_NS16550,
      .pDeviceFns = &ns16550_fns,
      .deviceProbe = lpc32xx_uart_probe_4,
      .pDeviceFlow = NULL,
      .ulMargin = 16,
      .ulHysteresis = 8,
      .pDeviceParams = (void *) LPC32XX_UART_4_BAUD,
      .ulCtrlPort1 = LPC32XX_BASE_UART_4,
      .ulCtrlPort2 = 0,
      .ulDataPort = LPC32XX_BASE_UART_4,
      .getRegister = lpc32xx_uart_get_register,
      .setRegister = lpc32xx_uart_set_register,
      .getData = NULL,
      .setData = NULL,
      .ulClock = 16 * LPC32XX_UART_4_BAUD,
      .ulIntVector = LPC32XX_IRQ_UART_4
    },
  #endif
  #ifdef LPC32XX_UART_6_BAUD
    {
      .sDeviceName = "/dev/ttyS6",
      .deviceType = SERIAL_NS16550,
      .pDeviceFns = &ns16550_fns,
      .deviceProbe = lpc32xx_uart_probe_6,
      .pDeviceFlow = NULL,
      .ulMargin = 16,
      .ulHysteresis = 8,
      .pDeviceParams = (void *) LPC32XX_UART_6_BAUD,
      .ulCtrlPort1 = LPC32XX_BASE_UART_6,
      .ulCtrlPort2 = 0,
      .ulDataPort = LPC32XX_BASE_UART_6,
      .getRegister = lpc32xx_uart_get_register,
      .setRegister = lpc32xx_uart_set_register,
      .getData = NULL,
      .setData = NULL,
      .ulClock = 16 * LPC32XX_UART_6_BAUD,
      .ulIntVector = LPC32XX_IRQ_UART_6
    },
  #endif
  #ifdef LPC32XX_UART_1_BAUD
    {
      .sDeviceName = "/dev/ttyS1",
      .deviceType = SERIAL_CUSTOM,
      .pDeviceFns = &lpc32xx_hsu_fns,
      .deviceProbe = NULL,
      .pDeviceFlow = NULL,
      .ulMargin = 16,
      .ulHysteresis = 8,
      .pDeviceParams = (void *) LPC32XX_UART_1_BAUD,
      .ulCtrlPort1 = LPC32XX_BASE_UART_1,
      .ulCtrlPort2 = 0,
      .ulDataPort = 0,
      .getRegister = NULL,
      .setRegister = NULL,
      .getData = NULL,
      .setData = NULL,
      .ulClock = 16,
      .ulIntVector = LPC32XX_IRQ_UART_1
    },
  #endif
  #ifdef LPC32XX_UART_2_BAUD
    {
      .sDeviceName = "/dev/ttyS2",
      .deviceType = SERIAL_CUSTOM,
      .pDeviceFns = &lpc32xx_hsu_fns,
      .deviceProbe = NULL,
      .pDeviceFlow = NULL,
      .ulMargin = 16,
      .ulHysteresis = 8,
      .pDeviceParams = (void *) LPC32XX_UART_2_BAUD,
      .ulCtrlPort1 = LPC32XX_BASE_UART_2,
      .ulCtrlPort2 = 0,
      .ulDataPort = 0,
      .getRegister = NULL,
      .setRegister = NULL,
      .getData = NULL,
      .setData = NULL,
      .ulClock = 16,
      .ulIntVector = LPC32XX_IRQ_UART_2
    },
  #endif
  #ifdef LPC32XX_UART_7_BAUD
    {
      .sDeviceName = "/dev/ttyS7",
      .deviceType = SERIAL_CUSTOM,
      .pDeviceFns = &lpc32xx_hsu_fns,
      .deviceProbe = NULL,
      .pDeviceFlow = NULL,
      .ulMargin = 16,
      .ulHysteresis = 8,
      .pDeviceParams = (void *) LPC32XX_UART_7_BAUD,
      .ulCtrlPort1 = LPC32XX_BASE_UART_7,
      .ulCtrlPort2 = 0,
      .ulDataPort = 0,
      .getRegister = NULL,
      .setRegister = NULL,
      .getData = NULL,
      .setData = NULL,
      .ulClock = 16,
      .ulIntVector = LPC32XX_IRQ_UART_7
    },
  #endif
};

#define LPC32XX_UART_COUNT \
  (sizeof(Console_Configuration_Ports) / sizeof(Console_Configuration_Ports [0]))

unsigned long Console_Configuration_Count = LPC32XX_UART_COUNT;
