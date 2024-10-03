// main.h
#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#include <ADS1115_WE.h>
#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#define I2C_ADDRESS 0x48
#define PT1000_R_REF 1000.0
#define VCC_VOLTAGE 3300

#define D0 0
#define D1 1

uint8_t map_3300_to_255(uint16_t input_value);
float map_255_to_3300(uint8_t input_value);

#endif // MAIN_H
