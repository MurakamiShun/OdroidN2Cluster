/*
 * File:   uptime.c
 * Author: MurakamiShun
 *
 * Created on 2022/07/20, 0:26
 */

#define _XTAL_FREQ 32000000L
#include <xc.h>

#include "uptime.h"
#include "OLED.h"
#include "interrupt.h"

Uptime uptime;

static void add_1second_to_uptime(void){
    each_second_callback();
    // sec
    if(uptime.seconds < 59){
        uptime.seconds++;
        return;
    }
    // min
    uptime.seconds = 0;
    if(uptime.mins < 59){
        uptime.mins++;
        return;
    }
    // hour
    uptime.mins = 0;
    if(uptime.hours < 23){
        uptime.hours++;
        return;
    }
    // days
    uptime.hours = 0;
    uptime.days++;
}

void timer0_callback(void){
    uptime.min_resolution++;
    if(uptime.min_resolution == 122){
        uptime.min_resolution = 0;
        add_1second_to_uptime();
    }
}

static void init_timer0(void){
    // 8.192ms per interrupt
    OPTION_REGbits.TMR0CS = 0; // Focs/4
    OPTION_REGbits.PSA = 0; // use prescaler
    OPTION_REGbits.PS = 0b111;// prescaler 1/256
    
    // interrupt
    TMR0IE = 1;
    TMR0IF = 0;
    GIE = 1;
    
    // 122 times = 999.424ms = 1s(-0.06%))
}

void init_uptime_timer(void){
    uptime.days = 0;
    uptime.hours = 0;
    uptime.mins = 0;
    uptime.seconds = 0;
    uptime.min_resolution = 0;
    
    init_timer0();
}

void print_uptime(uint8_t row, uint8_t offset){
    offset = offset % SCROLL_WIDTH;
    uint8_t font_addr[11] = {
        uptime.days/10,
        uptime.days,
        0x60, // d
        uptime.hours/10,
        uptime.hours,
        0xA4, // :
        uptime.mins/10,
        uptime.mins,
        0xA4, // :
        uptime.seconds/10,
        uptime.seconds
    };
    for(uint8_t i = 0; i < OLED_COL_WIDTH; ++i){
        if(i+offset < OLED_COL_WIDTH || i+offset > SCROLL_WIDTH-1) print_at(0x58, i, row);
        else{
            uint8_t index = offset+i-OLED_COL_WIDTH;
            if(index%3 == 2) print_at(font_addr[index], i, row);
            else print_number_at(font_addr[index]%10, i, row);
        }
    }
}