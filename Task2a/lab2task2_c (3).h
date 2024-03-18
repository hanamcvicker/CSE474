//header file for task 2a on lab 4
/* Hana McVicker(1960220) and Diana Verduzco(1839513)
 * December 2, 2022
 * Header file for lab 4 Task 2a.
 * This header file contains the definitions for each register used
 * from Port N and Port L, but used for the timer0 and timer1
 */

#ifndef lab2task2_c
#define lab2task2_c

// Enables ports GPIO
#define RCGCGPIO         (*((volatile uint32_t *)0x400FE608)) 

// Used to set up and change data for Port L, containing the LEDs
#define GPIOAMSEL_L      (*((volatile uint32_t *)0x40062528)) 
#define GPIODIR_L        (*((volatile uint32_t *)0x40062400)) 
#define GPIODEN_L        (*((volatile uint32_t *)0x4006251C)) 
#define GPIOAFSEL_L      (*((volatile uint32_t *)0x40062420)) 
#define GPIODATA_L       (*((volatile uint32_t *)0x400623FC)) 

// Used to set up and change data for Port N, containing the on/off button
#define GPIOAMSEL_N      (*((volatile uint32_t *)0x40064528)) 
#define GPIODIR_N        (*((volatile uint32_t *)0x40064400)) 
#define GPIODEN_N        (*((volatile uint32_t *)0x4006451C)) 
#define GPIOAFSEL_N      (*((volatile uint32_t *)0x40064420)) 
#define GPIODATA_N       (*((volatile uint32_t *)0x400643FC))

// Used to set up and change data for Port F1, containing the pedestrian buttons
#define GPIOAMSEL_F      (*((volatile uint32_t *)0x4005D528)) //Set up and Assign Port F GPIOs for Pushbutton 1
#define GPIODIR_F        (*((volatile uint32_t *)0x4005D400))  
#define GPIODEN_F        (*((volatile uint32_t *)0x4005D51C)) 
#define GPIOAFSEL_F      (*((volatile uint32_t *)0x4005D420)) 
#define GPIODATA_F       (*((volatile uint32_t *)0x4005D3FC)) 

// Timer initialization,
#define RCGCTimer (*((volatile uint32_t *)0x400FE604)) // RCGCTimer for 0 and 1 (need to change name)
#define GPTMCTL0 (*((volatile uint32_t *)0x4003000C)) // timer 0 GPTMCTL
#define GPTMCFG0 (*((volatile uint32_t *)0x40030000)) // timer 0 GPTMCFG
#define GPTMTAMR0 (*((volatile uint32_t *)0x40030004)) // timer 0 GPTMTAMR
#define GPTMTAILR0 (*((volatile uint32_t *)0x40030028)) // timer 0 GPTMTAILR
#define GPTMICR0 (*((volatile uint32_t *)0x40030024)) // timer 0 GPTMICR 
#define GPTMRIS0 (*((volatile uint32_t *)0x4003001C)) // timer 0 GPTMRIS 

// Interrupts
#define GPTMIMR0 (* ((volatile uint32_t *)0x40030018)) // timer 0 GPTMIMR 
#define INTERRUPT_EN0 (* ((volatile uint32_t *)0xE000E100)) // Interrupt 0-31 Set Enable(EN0) for both timers
#define INTERRUPT_EN2 (* ((volatile uint32_t *)0xE000E108))  //for port N
#define GPTMIMR1 (* ((volatile uint32_t *)0x40031018)) // timer 1 GPTMIMR  //timer 1 GPTMIMR

//priorities
#define INT_PRI_0 (*((volatile uint32_t *)0xE000E410)) //Interrupt Priority for timer0
#define INT_PRI_1 (*((volatile uint32_t *)0xE000E414)) //Interrupt Priority for timer1
#define INT_PRI_N (*((volatile uint32_t *)0xE000E448)) //Interrupt Priority for N

//port N - Interrupt Number 73- Reg 42: (PRI18) offset 0x448 -EN2
//Timer0A - Interrupt Number 19 - Reg 28: (PRI4) offset 0x410 -EN0
//Timer 1A - Interrupt Number 21 - Reg 29: (PRI5) offset 0x414 -EN0

//Timer 1 initialization
#define GPTMCTL1 (*((volatile uint32_t *)0x4003100C)) // timer 0 GPTMCTL
#define GPTMCFG1 (*((volatile uint32_t *)0x40031000)) // timer 0 GPTMCFG
#define GPTMTAMR1 (*((volatile uint32_t *)0x40031004)) // timer 0 GPTMTAMR
#define GPTMTAILR1 (*((volatile uint32_t *)0x40031028)) // timer 0 GPTMTAILR
#define GPTMICR1 (*((volatile uint32_t *)0x40031024)) // timer 0 GPTMICR
#define GPTMRIS1 (*((volatile uint32_t *)0x4003101C)) // timer 0 GPTMRIS

//Enable interrupts for Port N (Port2)
#define GPIOIS_N (*((volatile uint32_t *)0x40064404)) //Interrupt Sense register, setting a bit configures the corresponding pin to detect levels, 0 is edge sensitive, 1 is level sensitive
#define GPIOIBE_N (*((volatile uint32_t *)0x40064408)) //0, interrupt generation is controlled by GPIOIEV, 1, both edges on corresponding pin trigger an interrupt
#define GPIOIEV_N (*((volatile uint32_t *)0x4006440C))  //0, falling edge/lowlevel triggers an interrupt, 1, rising edge/high level triggers interrupt
#define GPIOICR_N (*((volatile uint32_t *)0x4006441C)) //clear any prior interrupt
#define GPIOIM_N (*((volatile uint32_t *)0x40064410))  //0, interrupt is masked , 1, interrupt is sent to interrrupt controller
#define GPIOMIS_N (*((volatile uint32_t *)0x40064418)) // use this for edge detect interrupts, this bit is cleared by writing a 1 to the corresponding bit in the GPIOICR register



//Initializes Timer 0
void Initialize_Timer0();
//Initializes Timer 1
void Initialize_Timer1();
//Timer interrupt controls LED switching
void Timer0A_Int_Handler();
//Timer interrupts handles button press hold
void Timer1A_Int_Handler();
//


#endif //__LAB2_H__