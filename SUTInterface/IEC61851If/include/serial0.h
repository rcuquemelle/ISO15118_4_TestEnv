/**
  ******************************************************************************
  * @file    uart.h
  * @author
  * @version V1.1.0
  * @date    23-May-2019
  * @brief   This file contains the common defines and functions prototypes for
  *          the uart.c driver.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

/**
  * @brief  UART status structure definition
  */

typedef enum {
  UART_OK = 0,
  UART_ERROR
} UART_Status_t;

/** @defgroup UART_Exported_Macro UART Exported Macro
  * @{
  */
#define UART0_PRINTF(f_, ...)          uart_instance0_printf((f_), ##__VA_ARGS__)

/** @defgroup _UART_Exported_Functions UART Exported Functions
  * @{
  */
UART_Status_t uart_instance0_Init(char* port);

UART_Status_t uart_instance0_deinit(void);

int putchar_instance0(uint8_t c);

int uart_instance0_write(uint8_t *buffer, uint32_t length);

int uart_instance0_read(uint8_t *buffer, uint32_t length);

int getchar_instance0(uint8_t *c);

int uart_instance0_printf(const uint8_t *format, ...);

void uart_instance0_echo(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __UART_H */
