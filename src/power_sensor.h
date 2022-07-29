#ifndef POWER_SENSOR_H
#define	POWER_SENSOR_H

void init_power_sensor(void);

uint16_t read_current(void); // [mA]
uint16_t read_voltage(void); // [mV]

#endif	/* POWER_SENSOR_H */

