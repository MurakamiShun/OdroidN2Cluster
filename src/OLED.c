/*
 * File:   OLED.c
 * Author: MurakamiShun
 *
 * Created on 2022/07/18, 22:48
 */


#define _XTAL_FREQ 32000000L
#include <xc.h>

#include "OLED.h"

static void init_i2c(void){
    SSP1CON1bits.SSPEN = 1;
    SSP1CON1bits.SSPM = 0b1000; // i2c master
    SSP1CON2 = 0x00;
    SSP1CON3 = 0x00;
    SSP1STAT = 0x00;
    // 400kbps
    SSP1ADD = 0x13;// _XTAL_FREQ/(CLK * 4) - 1
    SSP1STATbits.SMP = 0;
    // 100kbps
    //SSP1ADD = 0x4F; 
    //SSP1STATbits.SMP = 1;
    
    WPUAbits.WPUA1 = 1; // pull up RA1
    WPUAbits.WPUA2 = 1; // pull up RA2
    nWPUEN = 0; // enable pull up
}

static void send_i2c(uint8_t data){
    SSP1IF = 0;
    SSP1BUF = data;
    while(!SSP1IF);
    SSP1IF = 0;
}

static void begin_i2c_transmission(uint8_t address){
    // start condition
    SSP1CON2bits.SEN = 1;
    while(SSP1CON2bits.SEN);
    // send address
    send_i2c(address);
}

static void end_i2c_transmission(void){
    // stop condition
    SSP1CON2bits.PEN = 1;
    while(SSP1CON2bits.PEN);
}

void init_oled(void){
    init_i2c();
    __delay_ms(100);
    
    begin_i2c_transmission(0x78);
    for(uint8_t rom_addr = 0xB0; rom_addr != 0xCD; ++rom_addr){
        send_i2c(eeprom_read(rom_addr));
    }
    end_i2c_transmission();
    __delay_us(3);
    
    // clear display
    begin_i2c_transmission(0x78);
    send_i2c(0x40);
    for(uint8_t page = 0; page < 8; ++page){
        for(uint8_t col = 0; col < 128; ++col){
            send_i2c(0);
        }
    }
    end_i2c_transmission();
}

// 10rows
// 8cols
// 00:xx:xx
void print_at(uint8_t addr, uint8_t col, uint8_t row){
    uint8_t font_data[4] = {
        eeprom_read(addr),
        eeprom_read(addr + 1),
        eeprom_read(addr + 2),
        eeprom_read(addr + 3)
    };
    row = (9-row)*12;
    // set_draw_area
    begin_i2c_transmission(0x78);
    send_i2c(0x00); // control
    send_i2c(0x21); // column range
    send_i2c(row);
    send_i2c(row+11);
    send_i2c(0x22); // page range
    send_i2c(col);
    send_i2c(col);
    end_i2c_transmission();
    __delay_us(3);
    
    begin_i2c_transmission(0x78);
    send_i2c(0x40);
    for(uint8_t c = 0; c < 8; ++c){
        addr = 0;
        for(uint8_t i = 0; i < 4; ++i){
            uint8_t shft = (3-i)*2;
            addr |= ((font_data[i] & 128) >> shft) | ((font_data[i] & 128) >> (shft+1));
            font_data[i] = (uint8_t)(font_data[i] << 1);
        }
        send_i2c(addr);
    }
    end_i2c_transmission();
}

void print_n_digits_at(uint16_t num, uint8_t col, uint8_t row, uint8_t digits){
    digits--;
    print_number_at(num%10, col+digits, row);
    for(uint8_t i = 1; i <= digits; ++i){
        num = num/10;
        if(num != 0){print_number_at(num%10, col + (digits-i), row);}
        else{ print_at(0x58, col + (digits-i), row); }
    }
}

void print_0filled_n_digit_at(uint16_t num, uint8_t col, uint8_t row, uint8_t digits){
    for(uint8_t i = 1; i <= digits; ++i){
        print_number_at(num%10, col + (digits-i), row);
        num = num/10;
    }
}