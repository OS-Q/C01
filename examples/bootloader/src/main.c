#include "cfg.h"

void delayUs(uint32_t delay)
{
    while (delay--)
        __asm__ __volatile__("");
}

__attribute__((naked, noreturn)) void jump_app(uint32_t SP, uint32_t RH)
{
    __asm("MSR MSP, r0");
    __asm("BX  r1");
}

int main(void)
{
    UART_INIT();
    uint32_t cnt = BOOT_DELAY;
    volatile uint32_t *Address = (uint32_t *)(APPLICATION);
    while (1)
    {
        if (BOOT_UART->USART.INTFLAG.bit.RXC)
        {
            if (ACK == BOOT_UART->USART.DATA.reg)
                boot_task();
        }
        if (0 == cnt--)
        {
            if (0xFFFFFFFF != *Address)
            {
                BOOT_UART->USART.CTRLA.bit.SWRST = 1;
                delayUs(0xFFF);
                SCB->VTOR = APPLICATION & SCB_VTOR_TBLOFF_Msk;
                jump_app(Address[0], Address[1]);
            }
            cnt = BOOT_DELAY;
        }
    }
}
