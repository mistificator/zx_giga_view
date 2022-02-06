#pragma output nostreams
#pragma output nofileio

#include <spectrum.h>
#include <im2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <spectrum.h>

char screen = 0;
M_BEGIN_ISR(isr)                    
{
#asm
    ld a, (0x5B5C)
    xor 0x08
    or 0x07 | 0x10
    ld bc, 0x7FFD
    out (c), a
    ld (0x5B5C), a
#endasm
}
M_END_ISR

void initIM2() __z88dk_fastcall
{
#asm
    ld a, 0xBC
    ld i, a
    ld a, 0xBD
    ld hl, 0xBC00
    ld de, 0xBC01
    ld bc, 257
    ld (hl), a
    ldir
    ld a, 0xC3
    ld (0xBDBD), a
    ld de, _isr
    ld (0xBDBE), de
    im 2
#endasm      
}

int main()
{
#asm
    ld a, 0x07 | 0x10
    ld bc, 0x7FFD
    out (c), a
    ld (0x5B5C), a
#endasm

    zx_cls();
    zx_border(INK_BLACK);
    memset(0x4000, 0, 0x1B00);

    tape_load_block(0xFF00, 0x11, 0x00); // load header somewhere
    tape_load_block(0xC000, 0x1B00, 0xFF);
    tape_load_block(0xFF00, 0x11, 0x00); // load header somewhere
    tape_load_block(0x4000, 0x1B00, 0xFF);

    initIM2();

    while (1);

    return 0;
}