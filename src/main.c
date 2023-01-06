#include <8052.h>

#define uint_8 unsigned int

uint_8 len = 8;
void delay_ms(uint_8 ms);
void main()
{

    uint_8 i;

    while (1)
    {
        P0 = 0xff;
        for (i = 0; i < len; i++)
        {
            P0 = P0 >> 1;
            delay_ms(100);
        }

        P0 = 0xff;
        for (i = 0; i < len; i++)
        {
            P0 = P0 << 1;
            delay_ms(100);
        }
    }
}

void delay_ms(uint_8 ms)
{
    uint_8 i, j;
    for (i = ms; i > 0; i--)
        for (j = 110; j > 0; j--)
            ;
}