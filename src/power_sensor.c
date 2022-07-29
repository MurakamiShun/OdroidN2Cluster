/*
 * File:   power_sensor.c
 * Author: MurakamiShun
 *
 * Created on 2022/07/20, 3:25
 */

#define _XTAL_FREQ 32000000L
#include <xc.h>
#include "power_sensor.h"
#include "interrupt.h"

uint16_t current;
uint16_t voltage;

void ADC_callback(void){
    if(ADCON0bits.CHS == 0b00000){ // RA0
        current = ADRES;
    }
    else if(ADCON0bits.CHS == 0b00011){ // RA4
        voltage = ADRES;
    }
}

void init_power_sensor(void){
    ANSA0 = 1; // RA0 is analog
    TRISA0 = 1; // RA0 is input
    ANSA4 = 1; // RA4 is analog
    TRISA4 = 1; // RA4 is input
    
    ADCON1bits.ADFM = 1; // right justify
    ADCON1bits.ADCS = 0b110; // Fosc/64
    ADCON1bits.ADPREF = 0b11; // reference is Vdd
    ADCON0bits.ADON = 1; // ADC ON
    
    FVRCONbits.FVREN = 1; // FRV enable
    FVRCONbits.ADFVR = 0b11; // FRV=4.096 1=4mV
    
    // interrupt
    ADIE = 1;
    ADIF = 0;
    PEIE = 1;
    GIE = 1;
}


static void start_current_ADC(void){
    ADCON0bits.CHS = 0b00000; // RA0
    ADCON0bits.GO = 1;
}
static void start_voltage_ADC(void){
    ADCON0bits.CHS = 0b00011; // RA4
    ADCON0bits.GO = 1;
}

uint16_t read_current(void){ // [mA]
    static uint16_t mean_current = 0;
    start_current_ADC();
    // 0mA = 2.5V = 625 on ADC
    // 200mV/A * 3.13 amp
    // 1bit on ADC = 4mV = 20/3.13mA = 6.39mA
    // [[correction]]
    // 433 = 0mA, 6.723mA per 1bit = 74/11
    uint16_t real_current;
    if(current < 440) real_current = 0;
    else real_current = (current-440)*8;
    
    mean_current = (mean_current*7 + real_current)/8;
    return mean_current;
}
uint16_t read_voltage(void){ // [mV]
    static uint16_t mean_voltage = 0;
    start_voltage_ADC();
    // VCC ---2.4kohm--[-1.0kohm-]-- GND
    // 1bit on ADC = 13.6mV
    // VCC = ADCV * 4 * 3400 / 1000 = ADCV * 27/2 (-0.07%)
    // [0V, 13.9V]
    // [[correction]]
    //  ADCV * 27/2
    mean_voltage = (mean_voltage*3 + voltage*27/2)/4;
    return mean_voltage;
}