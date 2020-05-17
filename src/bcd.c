#include "bcd.h"

void bcd_add(BCD * sour, BCD * value) __naked
{
    sour; value; // suppress warninig: unreferenced function argument
__asm
            lda     HL, 5(SP)
            ld      D, (HL)         
            dec     HL
            ld      E, (HL)         ; DE: value
            dec     HL
            ld      A, (HL-)
            ld      L, (HL)
            ld      H, A            ; HL: sour

            or      A               ; clear C, HC

            ld      A,(DE)
            add     (HL)
            daa
            ld      (HL+), A
            inc     DE
            
            ld      A,(DE)
            adc     (HL)
            daa
            ld      (HL+), A
            inc     DE
            
            ld      A,(DE)
            adc     (HL)
            daa
            ld      (HL+), A
            inc     DE
            
            ld      A,(DE)
            adc     (HL)
            daa
            ld      (HL+), A
            
            ret
__endasm;
}

void bcd_sub(BCD * sour, BCD * value) __naked
{
    sour; value; // suppress warninig: unreferenced function argument 
__asm
            lda     HL, 2(SP)
            ld      E, (HL)         
            inc     HL
            ld      D, (HL)         ; DE: sour
            inc     HL
            ld      A, (HL+)
            ld      H, (HL)
            ld      L, A            ; HL: value

            or      A               ; clear C, HC

            ld      A,(DE)
            sub     (HL)
            daa
            ld      (DE), A
            inc     DE
            inc     HL
            
            ld      A,(DE)
            sbc     (HL)
            daa
            ld      (DE), A
            inc     DE
            inc     HL
            
            ld      A,(DE)
            sbc     (HL)
            daa
            ld      (DE), A
            inc     DE
            inc     HL
            
            ld      A,(DE)
            sbc     (HL)
            daa
            ld      (DE), A
            
            ret
__endasm;
}

BYTE bcd_compare(BCD * A, BCD * B) __naked
{
    A; B; 
__asm
            lda     HL, 2(SP)
            ld      E, (HL)         
            inc     HL
            ld      D, (HL)         ; DE: sour
            inc     HL
            ld      A, (HL+)
            ld      H, (HL)
            ld      L, A            ; HL: value

            inc     DE
            inc     DE
            inc     DE
            
            inc     HL
            inc     HL
            inc     HL
            
            ld      A, (DE)
            cp      (HL)
            jr      Z, bcdcmp01$
            jr      C, bcdcmp_aB$
bcdcmp_Ab$:
            ld      DE, #0x0001
            ret
bcdcmp_aB$:            
            ld      DE, #0xffff
            ret
bcdcmp01$:  
            dec     DE
            dec     HL
            ld      A, (DE)
            cp      (HL)
            jr      Z, bcdcmp02$
            jr      C, bcdcmp_aB$
            jr      bcdcmp_Ab$
bcdcmp02$:            
            dec     DE
            dec     HL
            ld      A, (DE)
            cp      (HL)
            jr      Z, bcdcmp03$
            jr      C, bcdcmp_aB$
            jr      bcdcmp_Ab$
bcdcmp03$:            
            dec     DE
            dec     HL
            ld      A, (DE)
            cp      (HL)
            jr      C, bcdcmp_aB$
            jr      NZ, bcdcmp_Ab$

            ld      DE, #0x0000
            ret
__endasm;
}

UBYTE bcd2text(BCD * bcd, UBYTE tile_offset, unsigned char * buffer) __naked
{
    bcd; tile_offset; buffer;
__asm
            push    BC
            
            lda     HL, 4(SP)
            ld      E, (HL)         
            inc     HL
            ld      D, (HL)         ; DE: bcd
            inc     HL
            ld      C, (HL)         ; C: digit offset
            inc     HL
            ld      A, (HL+)
            ld      H, (HL)
            ld      L, A            ; HL: buffer

            inc     DE
            inc     DE
            inc     DE

            ld      A, (DE)
            dec     DE
            ld      B, A
            swap    A
            and     #0x0f
            add     C
            ld      (HL+), A
            ld      A, B
            and     #0x0f
            add     C
            ld      (HL+), A
            
            ld      A, (DE)
            dec     DE
            ld      B, A
            swap    A
            and     #0x0f
            add     C
            ld      (HL+), A
            ld      A, B
            and     #0x0f
            add     C
            ld      (HL+), A

            ld      A, (DE)
            dec     DE
            ld      B, A
            swap    A
            and     #0x0f
            add     C
            ld      (HL+), A
            ld      A, B
            and     #0x0f
            add     C
            ld      (HL+), A
            
            ld      A, (DE)
            dec     DE
            ld      B, A
            swap    A
            and     #0x0f
            add     C
            ld      (HL+), A
            ld      A, B
            and     #0x0f
            add     C
            ld      (HL+), A
            
            xor     A
            ld      (HL+), A
            
            ld      DE, #0x0008
            
            pop     BC
            ret
__endasm;
}
