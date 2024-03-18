/*
 * Hana McVicker(1960220) and Diana Verduzco(1839513)
 * December 2, 2022
 * Header file for lab 4 Task 1c, uaing from previous labs
 * This header file contains the definitions for each register used
 * from multiple ports.
 */

#ifndef LAB3_TASK1B_H
#define LAB3_TASK1B_H

#include <stdint.h>


#define RCGCGPIO   (*((volatile uint32_t *)0x400FE608))

// Used to set up and change data for Port F
#define GPIODEN_F  (*((volatile uint32_t *)0x4005D51C))
#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
#define GPIODIR_F  (*((volatile uint32_t *)0x4005D400))

// Used to set up and change data for Port N
#define GPIOAMSEL_N  (*((volatile uint32_t *)0x40064528)) 
#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
#define GPIOAFSEL_N  (*((volatile uint32_t *)0x40064420)) 
#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC)) 

// ******************** CLOCK CONTROL REGISTERS ********************** //
#define MOSCCTL                 (*(volatile uint32_t *) 0x400FE07C)
#define RIS                     (*(volatile uint32_t *) 0x400FE050)
#define RSCLKCFG                (*(volatile uint32_t *) 0x400FE0B0)
#define PLLFREQ0                (*(volatile uint32_t *) 0x400FE160)
#define PLLFREQ1                (*(volatile uint32_t *) 0x400FE164)
#define PLLSTAT                 (*(volatile uint32_t *) 0x400FE168)
#define MEMTIM0                 (*(volatile uint32_t *) 0x400FE0C0)

#define ADCCC_ADC0              (*(volatile uint32_t *) 0x40038FC8 // ADC clock config

#endif  // LAB3_TASK1B_H