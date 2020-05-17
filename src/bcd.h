#ifndef __BCD_H_INCLUDE
#define __BCD_H_INCLUDE

#include <asm/types.h>

// macro for creating BCD constants
#define BCD_HEX(v) {(BYTE)(v), (BYTE)((v) >> 8), (BYTE)((v) >> 16), (BYTE)((v) >> 24)}
#define MAKE_BCD(v) BCD_HEX(0x ## v)

typedef UBYTE BCD[4];

// adding BCD numbers: sour += value
void bcd_add(BCD * sour, const BCD * value);
// subtracting BCD numbers: sour -= value
void bcd_sub(BCD * sour, const BCD * value);
// compare two BCD numbers: returns 1 if greater, 0 if equal, -1 if lower
BYTE bcd_compare(const BCD * A, const BCD * B);

// convert the BCD number into asciiz string and return the length
UBYTE bcd2text(const BCD * bcd, UBYTE tile_offset, unsigned char * buffer);

#endif
