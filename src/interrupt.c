/*
 * File:   interrupt.c
 * Author: MurakamiShun
 *
 * Created on 2022/07/20, 6:50
 */
#define _XTAL_FREQ 32000000L
#include <xc.h>
#include "interrupt.h"

static void __interrupt() isr(void){
    if(TMR0IF){
        timer0_callback();
        TMR0IF = 0;
    }
    if(ADIF){
        ADC_callback();
        ADIF = 0;
    }
    if(IOCAF3){
        IO3_callback();
        IOCAF3 = 0;
    }
}