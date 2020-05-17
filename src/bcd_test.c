#include <gb/gb.h>
#include <gb/bgb_emu.h>

#include <stdio.h>
#include <gb/font.h>

#include "bcd.h"

BCD bcd  = MAKE_BCD(10203040);
BCD bcd2 = MAKE_BCD(05060708);
BCD bcd3 = MAKE_BCD(11111111);

UBYTE len = 0;
unsigned char buf[10];

void main() {
    font_init();
    font_set(font_load(font_spect));

    len = bcd2text(&bcd, 0x11, buf);
    set_bkg_tiles(5, 5, len, 1, buf);

    BGB_PROFILE_BEGIN();
    bcd_add(&bcd, &bcd2);
    BGB_PROFILE_END(bcd_add());

    len = bcd2text(&bcd, 0x11, buf);
    set_bkg_tiles(5, 6, len, 1, buf);

    BGB_PROFILE_BEGIN();
    bcd_sub(&bcd, &bcd3);
    BGB_PROFILE_END(bcd_sub());

    BGB_PROFILE_BEGIN();
    bcd_compare(&bcd, &bcd);
    BGB_PROFILE_END(bcd_compare());

    BGB_PROFILE_BEGIN();
    len = bcd2text(&bcd, 0x11, buf);
    BGB_PROFILE_END(bcd2text());
    set_bkg_tiles(5, 7, len, 1, buf);
}