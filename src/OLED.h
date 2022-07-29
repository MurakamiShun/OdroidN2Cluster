#ifndef OLED_H
#define	OLED_H

#include <stdint.h>

void init_oled(void);

#define OLED_ROW_WIDTH 10
#define OLED_COL_WIDTH 8

// 10rows
// 8cols
void print_at(uint8_t addr, uint8_t col, uint8_t row);

#define print_number_at(num, col, row) print_at((uint8_t)(num<<2), col, row);

void print_n_digits_at(uint16_t num, uint8_t col, uint8_t row, uint8_t digits);

#define print_4digit_at(num, col, row) print_n_digits_at(num, col, row, 4);
#define print_2digit_at(num, col, row) print_n_digits_at(num, col, row, 2);


void print_0filled_n_digit_at(uint16_t num, uint8_t col, uint8_t row, uint8_t digits);

#define print_0filled_2digit_at(num, col, row) print_0filled_n_digit_at(num, col, row, 2);
#define print_0filled_3digit_at(num, col, row) print_0filled_n_digit_at(num, col, row, 3);

#define print_rpm_at(col, row) print_at(0x29, col, row);\
print_at(0x2D, col+1, row);\
print_at(0x31, col+2, row);

#define print_speed_at(col, row) print_at(0x48, col, row);\
print_at(0x4C, col+1, row);\
print_at(0x50, col+2, row);\
print_at(0x54, col+3, row);\
print_at(0x2C, col+4, row);\
print_at(0x5C, col+5, row);\
print_at(0x5C, col+6, row);\
print_at(0x60, col+7, row);

#define print_power_at(col, row) print_at(0x2C, col, row);\
print_at(0x64, col+1, row);\
print_at(0x68, col+2, row);\
print_at(0x6C, col+3, row);\
print_at(0x70, col+4, row);\
print_at(0x74, col+5, row);

#define print_current_at(col, row) print_at(0x78, col, row);\
print_at(0x7C, col+1, row);\
print_at(0x28, col+2, row);\
print_at(0x28, col+3, row);\
print_at(0x5C, col+4, row);\
print_at(0x80, col+5, row);\
print_at(0x84, col+6, row);

#define print_ampere_at(col, row) print_at(0x38, col, row);

#define print_watt_at(col, row) print_at(0x40, col, row);\
print_at(0x44, col+1, row);

#define print_voltage_at(col, row)  print_at(0x88, col, row);\
print_at(0x64, col+1, row);\
print_at(0x8C, col+2, row);\
print_at(0x84, col+3, row);\
print_at(0x90, col+4, row);\
print_at(0x94, col+5, row);\
print_at(0x5C, col+6, row);

#define print_volt_at(col, row)  print_at(0x3C, col, row);

#define print_uptime_at(col, row) print_at(0x98, col, row);\
print_at(0x9C, col+1, row);\
print_at(0x84, col+2, row);\
print_at(0xA0, col+3, row);\
print_at(0x31, col+4, row);\
print_at(0x5C, col+5, row);


#endif	/* OLED_H */

