/* 
 * File:   I2C.h
 * Author: willi
 *
 * Created on March 1, 2025, 5:18 PM
 */

#ifndef I2C_H
#define	I2C_H

void initI2C(void);
void Start_I2C (uint8_t address);
void I2C_Clock_Rate(uint16_t khz);
void Slave_I2C (void);


#endif	/* I2C_H */

