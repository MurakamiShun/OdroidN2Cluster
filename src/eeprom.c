/*
 * File:   eeprom.c
 * Author: MurakamiShun
 *
 * Created on 2022/07/18, 22:56
 */
#define _XTAL_FREQ 32000000L
#include <xc.h>

__EEPROM_DATA( // 0x00
    // 0
    0x00, // padding
    0b11111110,
    0b10000010,
    0b11111110,
    // 1
    0x00, // padding
    0b10000100,
    0b11111110,
    0b10000000
);__EEPROM_DATA( // 0x08
    // 2
    0x00, // padding
    0b11110010,
    0b10010010,
    0b10011110,
    // 3
    0x00, // padding
    0b10010010,
    0b10010010,
    0b11111110
);__EEPROM_DATA( // 0x10
    // 4
    0x00, // padding
    0b00011110,
    0b00010000,
    0b11111110,
    // 5
    0x00, // padding
    0b10011110,
    0b10010010,
    0b11110010
);__EEPROM_DATA( // 0x18
    // 6
    0x00, // padding
    0b11111110,
    0b10010010,
    0b11110010,
    // 7
    0x00, // padding
    0b00000110,
    0b00000010,
    0b11111110
);__EEPROM_DATA( // 0x20
    // 8
    0x00, // padding
    0b11111110,
    0b10010010,
    0b11111110,
    // 9
    0x00, // padding
    0b10011110,
    0b10010010,
    0b11111110
);__EEPROM_DATA( // 0x28
    // r
    0x00, // padding
    0b11111000,
    0b00010000,
    0b00001000,
    // p
    0x00, // padding
    0b11111000,
    0b00101000,
    0b00010000
);__EEPROM_DATA( // 0x30
    // m (5byte)
    0b11111000,
    0b00001000,
    0b11110000,
    0b00001000,
    0b11110000,
    0x00, // padding
    0x00, // padding
    0x00  // padding
);__EEPROM_DATA( // 0x38
    // A
    0b11111100,
    0b00100011,
    0b00100011,
    0b11111100,
    // V
    0b00111111,
    0b11000000,
    0b00110000,
    0b00001111
);__EEPROM_DATA( // 0x40
    // W(5byte)
    0b00111111,
    0b11000000,
    0b00111111,
    0b11000000,
    0b00111111,
    0x00, // padding
    0x00, // padding
    0x00  // padding
);__EEPROM_DATA( // 0x48
    // F
    0b11111111,
    0b00001001,
    0b00001001,
    0x00, // padding
    // A
    0b11111110,
    0b00010001,
    0b11111110,
    0x00  // padding
);__EEPROM_DATA( // 0x50
    // N
    0b11111111,
    0b00001100,
    0b00110000,
    0b11111111,
    // s
    0x00,  //padding
    0b10110000,
    0b10101000,
    0b01001000
);__EEPROM_DATA( // 0x58
    // null
    0x00, //padding
    0x00, //padding
    0x00, //padding
    0x00, //padding
    // e
    0x00,  //padding
    0b01110000,
    0b10101000,
    0b10110000
);__EEPROM_DATA( // 0x60
    // d
    0x00, // padding
    0b11110000,
    0b10010000,
    0b11111110,
    // o
    0x00, // padding
    0b01110000,
    0b10001000,
    0b01110000
);__EEPROM_DATA( // 0x68
    // w(wer)
    0x00, // padding
    0b01111000,
    0b10000000,
    0b01111000,
    0b10000000,
    0b01111000,
    // e
    0x00, // padding
    0b01110000
);__EEPROM_DATA( // 0x70
    0b10101000,
    0b10110000,
    // r
    0x00, // padding
    0b11111000,
    0b00010000,
    0b00001000,
    0x00, // padding
    0x00  // padding
);__EEPROM_DATA( // 0x78
    // c
    0x00, //padding
    0b01110000,
    0b10001000,
    0b10001000,
    // u
    0x00, // padding
    0b01111000,
    0b10000000,
    0b11111000
);__EEPROM_DATA( // 0x80
    // n
    0x00, //padding
    0b11111000,
    0b00001000,
    0b11110000,
    // t
    0x00, // padding
    0b00001000,
    0b11111100,
    0b10001000
);__EEPROM_DATA( // 0x88
    // v
    0x00, //padding
    0b01111000,
    0b10000000,
    0b01111000,
    // l
    0x00, // padding
    0b00000010,
    0b11111110,
    0b10000000
);__EEPROM_DATA( // 0x90
    // a
    0x00, // padding
    0b11101000,
    0b10101000,
    0b11110000,
    // g
    0x00, //padding
    0b10111000,
    0b10101000,
    0b11111100
);__EEPROM_DATA( // 0x98
    // U
    0b01111111,
    0b10000000,
    0b01111111,
    0x00, // padding
    // P
    0b11111111,
    0b00001001,
    0b00001001,
    0b00000110
);__EEPROM_DATA( // 0xA0
    // im
    0x00, // padding
    0b11110100,
    0x00, // padding
    0b11111000,
    // :
    0x00, // padding
    0x00, // padding
    0b00100100,
    0x00  // padding
);__EEPROM_DATA( // 0xA8
    // im
    0x00, // padding
    0x00, // padding
    0b1000000,
    0x00, // padding
    // :
    0x00, // padding
    0x00, // padding
    0x00, // padding
    0x00  // padding
);
// Commands for initialize OLED
__EEPROM_DATA( // 0xB0
    0x00, // control
    0xAE, // display off
    
    0xA8, // set multiplex ratio
    0b00111111,
    
    0xD3, // set display offset
    0x00, // 0
    
    0x40 | 0x00, // set display start line to 0x00
    0xA0  // set segment re-map
);__EEPROM_DATA( // 0xB8
    0xC0, // set COM output scan direction
    
    0xDA, // set COM pins hardware configurationo
    0b00010010,
    
    0x81, // set contrast
    0xFF, // max
    
    0xA4, // disable entire display on
    0xA6, // set normal display
    
    0xD5  // set display clock frequency/divide]
);__EEPROM_DATA( // 0xC0
    0b10000000,
    
    0x8D, // set charge pump
    0x14,
    
    0x2E, // stop scrolling

    0x20, // set memory addressing mode
    0x00, // Horizontal
    
    // 128*8
    0x21, // set column address
    0x00  // start column address
);__EEPROM_DATA( // 0xC8
    0x7F, // stop column address
    
    0x22, // set page address
    0x00, // start page address
    0x07, // stop page address
    
    0xAF, // display on
    
    // padding 0xCD
    0x00,
    0x00,
    0x00
);