#ifndef UPTIME_H
#define	UPTIME_H

#include "OLED.h"
#include <stdint.h>

#define SCROLL_WIDTH (OLED_COL_WIDTH + 11) // xxdxx:xx:xx

void init_uptime_timer(void);

typedef struct {
    uint8_t days    : 7;
    uint8_t hours   : 5; // <24
    uint8_t mins    : 6; // <60
    uint8_t seconds : 6; // <60
    uint8_t min_resolution : 7; // 1/122s
} Uptime;
extern Uptime uptime;

// implemented at used source
void each_second_callback(void);

void print_uptime(uint8_t row, uint8_t offset);

#endif	/* UPTIME_H */