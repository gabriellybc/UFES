#pragma once

#include <Arduino.h>

// Passaro
// 'pterodactyl-1', 23x20px
const unsigned char passaro_pterodactyl_1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0e, 
	0x00, 0x00, 0x1f, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x01, 0xff, 0x00, 0x00, 0xff, 
	0xfc, 0x00, 0x7f, 0xe0, 0x00, 0x7f, 0xf8, 0x00, 0x7f, 0xc0, 0x00, 0x78, 0x00, 0x00, 0x70, 0x00, 
	0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00
};
// 'pterodactyl-2', 23x20px
const unsigned char passaro_pterodactyl_2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xe0, 0x00, 0x06, 0x70, 0x00, 0x0e, 
	0x78, 0x00, 0x1f, 0x7c, 0x00, 0x3f, 0x7e, 0x00, 0x7f, 0xfe, 0x00, 0x01, 0xff, 0x00, 0x00, 0xff, 
	0xfc, 0x00, 0x7f, 0xe0, 0x00, 0x3f, 0xf8, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 160)
const int passaro_allArray_LEN = 2;
const unsigned char* passaro_allArray[2] = {
	passaro_pterodactyl_1,
	passaro_pterodactyl_2
};
