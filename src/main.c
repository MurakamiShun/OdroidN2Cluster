/*
 * File:   main.c
 * Author: MurakamiShun
 *
 * Created on 2022/07/15, 1:49
 */

#pragma config CLKOUTEN = OFF, PLLEN = ON, FOSC = INTOSC
#pragma config LVP = OFF, MCLRE = OFF
#pragma config CP = ON, CPD = ON
#pragma config BOREN = ON, STVREN = OFF, IESO = OFF, FCMEN = OFF, BORV = LO
#pragma config WDTE = OFF, PWRTE = OFF,


//
// 1 VDD           8 VSS
// 2 RA5 FAN(PWM)  7 RA0 Voltage(12V)
// 3 RA4 Current   6 RA1 I2C SCL
// 4 RA3 FAN(rpm)  5 RA2 I2C SDA
//
//

#define _XTAL_FREQ 32000000L
#include <xc.h>
#include <stdint.h>
#include "OLED.h"
#include "uptime.h"
#include "power_sensor.h"
#include "FAN_controller.h"

static void init(void){
    OSCCONbits.IRCF = 0b1110; // 8MHz
    OSCCONbits.SPLLEN = 1; // 4xPLL
    OSCCONbits.SCS = 0b00;
    ANSELA = 0x00; // reset pin to digital
    
    init_oled();
    init_FAN_controller();
    init_uptime_timer();
    init_power_sensor();
}

void main(void) {
    init();
    
    print_speed_at(0,0);
    print_rpm_at(5,1);
    print_voltage_at(0,2);
    print_volt_at(6,3);
    print_current_at(0,4);
    print_ampere_at(6,5);
    print_power_at(0,6);
    print_watt_at(6,7);
    print_uptime_at(0,8);
    
    uint8_t offset = 0;
    while(1){
        print_4digit_at(get_rpm(), 0, 1);
        print_uptime(9, offset);
        offset = (offset + 1)%SCROLL_WIDTH;
        
        uint16_t voltage = read_voltage();
        print_2digit_at(voltage/1000, 0, 3);
        print_at(0xA8, 2, 3);
        print_0filled_2digit_at(voltage/10, 3, 3);
        
        uint16_t current = read_current();
        print_number_at(current/1000, 0, 5);
        print_at(0xA8, 1, 5);
        print_0filled_3digit_at(current, 2, 5);
        
        // mW
        uint16_t power = (uint16_t)((uint24_t)voltage * (uint24_t)current / 1000);
        print_2digit_at(power/1000, 0, 7);
        print_at(0xA8, 2, 7);
        print_0filled_2digit_at(power/10, 3, 7);
        
        if(power < 1024){// 1W
            set_duty_ratio((uint8_t)(power >> 2));
        }
        else{
            set_duty_ratio(0xFF);
        }
        
        
        __delay_ms(200);
    }
    return;
}
