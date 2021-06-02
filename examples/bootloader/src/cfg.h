#ifndef _CFG_H_
#define _CFG_H_

#include <stdint.h>
#include <string.h>
#include <samr34.h>

#define BOOT_DELAY         0xFFFFF

#define APPLICATION        0x00002000  /* start address      */
#define MIN_ADDRESS        0x02000     /* protect bootloader */
#define MAX_ADDRESS        0x40000     /* from linker script */

#define CLOCK_DEFAULT      48000000ul

#define BOOT_UART          SERCOM0

#define ATTN        '#'
#define CONF        'C'
#define ACK         'A'
#define NACK        'N'

#define PING        'P'
#define PONG        'p'

#define DA_ERASE    'E'
#define DA_WRITE    'W'
#define DA_READ     'R'
#define DA_RESET    'X'

typedef enum
{
    E_LIMIT = 1,
    E_CRC,
    E_ALIGN,
    E_ERASE,
    E_WRITE,
    E_VERIFY,
} ERRORS_E;

void UART_INIT(void);
int available(void);
uint8_t getChar(void);
void putChar(char);
void putString(char *str);
void boot_task(void);

#endif
