#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>   /* File Control Definitions - Used for UART*/
#include <termios.h> /* POSIX Terminal Control Definitions - Used for UART*/
#include <unistd.h>   /* UNIX Standard Definitions - Used for UART*/
#include <errno.h>   /* ERROR Number Definitions           */
#include "serial0.h"

#define SERIAL_CONSOLE_DEBUG(f_, ...)          fprintf(stdout, (f_), ##__VA_ARGS__)

/* Private variables ---------------------------------------------------------*/
static int uart_instance0_status = UART_ERROR;
static int uart_instance0; /*File Descriptor*/
struct termios tty; /* Create the structure                          */

UART_Status_t uart_instance0_Init(char* port)
{
  // SERIAL_CONSOLE_DEBUG("\n +----------------------------------+");
  // SERIAL_CONSOLE_DEBUG("\n |        Serial Port Write         |");
  // SERIAL_CONSOLE_DEBUG("\n +----------------------------------+");

  /*------------------------------- Opening the Serial Port -------------------------------*/
  uart_instance0 = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
  /* O_RDWR Read/Write access to serial port            */
  /* O_NOCTTY - No terminal will control the process    */
  /* O_NDELAY -Non Blocking Mode,Does not care about-   */
  /* -the status of DCD line,Open() returns immediately */

  if (-1 == uart_instance0) /* Error Checking */
  {
    // SERIAL_CONSOLE_DEBUG("\n  Error! in Opening %s  ", port);
    return UART_ERROR;
  }
  else
  {
    // SERIAL_CONSOLE_DEBUG("\n  %s Opened Successfully ", port);
  }
  /*---------- Setting the Attributes of the serial port using termios structure --------- */

  tcgetattr(uart_instance0, &tty); /* Get the current attributes of the Serial port */

  cfsetispeed(&tty, B115200); /* Set Read  Speed as 115200                       */
  cfsetospeed(&tty, B115200); /* Set Write Speed as 115200                       */

  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
  tty.c_cflag |= CS8; // 8 bits per byte (most common)
  tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO; // Disable echo
  tty.c_lflag &= ~ECHOE; // Disable erasure
  tty.c_lflag &= ~ECHONL; // Disable new-line echo
  tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

  tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
  // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)


  /* Setting Time outs
   * VMIN = 0, VTIME = 0: No blocking, return immediately with what is available
   * Refers: https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
   */
  tty.c_cc[VMIN] = 0;
  tty.c_cc[VTIME] = 0;

  if (0 != tcsetattr(uart_instance0, TCSANOW, &tty)) /* Set the attributes to the termios structure*/
  {
    // SERIAL_CONSOLE_DEBUG("\n  ERROR ! in Setting attributes");
    return UART_ERROR;
  }
  else
  {
    // SERIAL_CONSOLE_DEBUG("\n  BaudRate = 115200 \n  StopBits = 1 \n  Parity   = none");
  }
  uart_instance0_status = UART_OK;

  return UART_OK;
}

/*------------------------------- Write data to serial port -----------------------------*/
int uart_instance0_write(uint8_t *buffer, uint32_t length)
{
  int bytes_written = 0;           /* Value for storing the number of bytes written to the port */
  if (UART_OK != uart_instance0_status)
  {
    return -1;
  }
  bytes_written = write(uart_instance0, buffer, length); /* use write() to send data to port                                            */
                                /* "uart_instance0"  - file descriptor pointing to the opened serial port */
                                /* "buffer"          - address of the buffer containing data              */
                                /* "length"          - No of bytes to write                               */
  if (length != bytes_written)
  {
    return -1;
  }

  return bytes_written;
}

int uart_instance0_read(uint8_t *buffer, uint32_t length)
{
  int bytes_read;
  if (UART_OK != uart_instance0_status)
  {
    return -1;
  }

  bytes_read = read(uart_instance0, buffer, length); /* Read the data */
  if (length != bytes_read)
  {
    return -1;
  }

  return bytes_read;
}

int getchar_instance0(uint8_t *c)
{
  uint8_t buffer[1];
  if(-1 == uart_instance0_read(buffer, 1))
  {
    return UART_ERROR;
  }
  (*c) = buffer[0];
  return UART_OK;
}

int putchar_instance0(uint8_t c)
{
  uint8_t buffer[1];
  buffer[0] = (uint8_t)c;
  if(-1 == uart_instance0_write(buffer, 1))
  {
    return UART_ERROR;
  }
  return UART_OK;
}

/* Test uart echo */
void uart_instance0_echo(void)
{
  uint8_t c;
  if (UART_OK == getchar_instance0(&c))
  {
    putchar_instance0(c);
  }
}

UART_Status_t uart_instance0_deinit(void)
{
  close(uart_instance0); /* Close the Serial port */
  return UART_OK;
}

/* return length of buff output */
int uart_instance0_printf(const uint8_t *format, ...)
{
  va_list args;
  int length;
  uint8_t buff_printf[1024];
  va_start(args, format);
  length = vsnprintf((char *)buff_printf, 1024, (const char *)format, args);
  va_end(args);

  uart_instance0_write(buff_printf, length);

  return length;
}