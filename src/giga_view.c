#pragma output nostreams
#pragma output nofileio

#include <spectrum.h>
#include <im2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void di() __naked
{
#asm
    di
    ret
#endasm
}

void ei() __naked
{
#asm
    ei
    ret
#endasm
}

char screen = 0;
M_BEGIN_ISR(isr)                    
{
    memcpy(0x5800, 0xD800 + 0x300 * (screen = (screen + 1) % 2), 0x300);
}
M_END_ISR

void initIM2() __z88dk_fastcall
{
    im2_Init(0xbc00);
    memset(0xbc00, 0xbd, 257);       // initialize 257-byte im2 vector table with all 0xb4 bytes
    bpoke(0xbdbd, 0xc3);              // POKE jump instruction at address 0xb4b4 (interrupt service routine entry)
    wpoke(0xbdbe, isr);  
}

void copyImage() __z88dk_fastcall
{
    zx_border(INK_BLACK);
    memcpy(0x4000, 0xC000, 0x1B00);
}

int main()
{
    di();
    copyImage();
    initIM2();
    ei();

    while (1);

    return 0;
}