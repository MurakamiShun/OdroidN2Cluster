/*
 * File:   FAN_controller.c
 * Author: MurakamiShun
 *
 * Created on 2022/07/20, 5:02
 */
#define _XTAL_FREQ 32000000L
#include <xc.h>

#include <stdbool.h>
#include "FAN_controller.h"
#include "interrupt.h"
#include "uptime.h"

static uint8_t io3_edgedown_count;
static uint8_t latest_edgedown_count;

void IO3_callback(void){
    io3_edgedown_count++;
}

void each_second_callback(){
    latest_edgedown_count = io3_edgedown_count;
    io3_edgedown_count = 0;
}

void init_FAN_controller(void){
    TRISAbits.TRISA3 = 1; // RA3 (FAN rpm) is input
    WPUAbits.WPUA3 = 1; // pull up RA3
    nWPUEN = 0; // enable pull up
    io3_edgedown_count = 0;
    latest_edgedown_count = 0;
    
    
    TRISAbits.TRISA5 = 0; // RA5 (FAN PWM) is output
    CCP1CONbits.CCP1M = 0b1100; // CCP1 is PWM mode
    T2CONbits.T2CKPS = 0b00; // prescaler = x1
    PR2 = 0xFF; // (PR2+1)*4*(1/32us)*prescaler = 31.25kHz
    TMR2 = 0;
    TMR2ON = 1;
    CCP1SEL = 1; //set CCP1 to RA5
    
    // gpio interrupt
    IOCAN3 = 1;
    IOCAF3 = 0;
    IOCIE = 1;
    OPTION_REGbits.INTEDG = 1; // high-to-low edge
    
    PEIE = 1;
    GIE = 1;
}

uint16_t get_rpm(void){
    return (uint16_t)latest_edgedown_count*30;
}

// 100% = 255, 0%=0
void set_duty_ratio(uint8_t duty){
    CCPR1L = duty;
}