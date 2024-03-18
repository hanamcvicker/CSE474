/* Hana McVicker(1960220) and Diana Verduzco(1839513)
 * December 2, 2022
 * This header file contains the definitions for each register used
 * from multiple ports for Lab 4 Task 1c
 */

#ifndef __TASK1B_H__
#define __TASK1B_H__

// Enables ports GPIO
#define RCGCGPIO   (*((volatile uint32_t *)0x400FE608))

// Used to set up and change data for Port L, containing the LEDs
//#define GPIODEN_F  (*((volatile uint32_t *)0x4005D51C))
//#define GPIODATA_F (*((volatile uint32_t *)0x4005D3FC))
//#define GPIODIR_F  (*((volatile uint32_t *)0x4005D400))

// Used to set up and change data for Port N
//#define GPIOAMSEL_N  (*((volatile uint32_t *)0x40064528)) 
//#define GPIODIR_N    (*((volatile uint32_t *)0x40064400)) 
//#define GPIODEN_N    (*((volatile uint32_t *)0x4006451C)) 
//#define GPIOAFSEL_N  (*((volatile uint32_t *)0x40064420)) 
//#define GPIODATA_N   (*((volatile uint32_t *)0x400643FC)) 

// Used to set up and change data for Port E
#define GPIOAMSEL_E (*((volatile uint32_t *)0x4005C528))
#define GPIODIR_E   (*((volatile uint32_t *)0x4005C400))
#define GPIODEN_E   (*((volatile uint32_t *)0x4005C51C))
#define GPIOAFSEL_E (*((volatile uint32_t *)0x4005C420))
#define GPIODATA_E  (*((volatile uint32_t *)0x4005C3FC))
   
// Used to set up and change data for Port J
#define GPIODEN_J  (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIODIR_J  (*((volatile uint32_t *)0x40060400))
#define GPIOPUR_J  (*((volatile uint32_t *)0x40060510))

// Clock Configuration
#define RCGCADC (*((volatile uint32_t *)0x400FE638)) // ADC run mode clock gating control
#define ADCCC   (*((volatile uint32_t *)0x40038FC8)) // ADC clock configuration
#define ADCACTSS (*((volatile uint32_t *)0x40038000)) // ADC Active Sample Sequencer or 800 offset?
#define ADCEMUX (*((volatile uint32_t *)0x40038014)) // ADC Event Multiplexer Select
#define ADCSSMUX3 (*((volatile uint32_t *)0x400380A0)) // ADC Sample Sequence Input Multiplexer Select 3
#define ADCSSCTL3 (*((volatile uint32_t *)0x400380A4)) // ADC Sample Sequence Control 3
#define ADCIM (*((volatile uint32_t *)0x40038008)) // ADC Interrupt Mask
#define ADCISC (*((volatile uint32_t *)0x4003800C)) // ADC Interrupt Status and Clear
#define ADCSSFIFO3 (*((volatile uint32_t *)0x400380A8)) // ADC Sample Sequence Result FIFO 3
#define ADCSSTSH3 (*((volatile uint32_t *)0x400380BC)) // ADC Sample Sequence 3 Sample and Hold Time
#define ALTCLKCFG (*((volatile uint32_t *)0x400FE138))
// Timer initialization
#define RCGCTimer (*((volatile uint32_t *)0x400FE604)) // RCGCTimer
#define GPTMCTL0 (*((volatile uint32_t *)0x4003000C)) // timer 0 GPTMCTL
#define GPTMCFG0 (*((volatile uint32_t *)0x40030000)) // timer 0 GPTMCFG
#define GPTMTAMR0 (*((volatile uint32_t *)0x40030004)) // timer 0 GPTMTAMR
#define GPTMTAILR0 (*((volatile uint32_t *)0x40030028)) // timer 0 GPTMTAILR
#define GPTMRIS0 (*((volatile uint32_t *)0x4003001C)) // timer 0 GPTMRIS
#define GPTMICR0 (*((volatile uint32_t *)0x40030024)) // timer 0 GPTMICR
#define INT_PRI_0 (*((volatile uint32_t *)0xE00E0410)) //Interrupt Priority for timer0
#define GPTMADCEV (*((volatile uint32_t *)0x40030070)) // timer 0 GPTMADCEV

// Interrupts
#define GPTMIMR0 (*((volatile uint32_t *)0x40030018)) // timer 0 GPTMIMR 
#define INTERRUPT_EN0 (*((volatile uint32_t *)0xE000E100)) // Interrupt 0-31 Set Enable(EN0)
#define GPTMIMR1 (* ((volatile uint32_t *)0x40031018)) // timer 1 GPTMIMR
#define INTERRUPT_EN1 (* ((volatile uint32_t *)0xE000E184)) 
#define INTERRUPT_EN2 (* ((volatile uint32_t *)0xE000E108)) 

//Timer 1 initialization
#define GPTMCTL1 (*((volatile uint32_t *)0x4003100C)) // timer 0 GPTMCTL
#define GPTMCFG1 (*((volatile uint32_t *)0x40031000)) // timer 0 GPTMCFG
#define GPTMTAMR1 (*((volatile uint32_t *)0x40031004)) // timer 0 GPTMTAMR
#define GPTMTAILR1 (*((volatile uint32_t *)0x40031028)) // timer 0 GPTMTAILR
#define GPTMICR1 (*((volatile uint32_t *)0x40031024)) // timer 0 GPTMICR
#define GPTMRIS1 (*((volatile uint32_t *)0x4003101C)) // timer 0 GPTMRIS

//Enable interrupts for Port N (4&2)
#define GPIO_IS_N (*((volatile uint32_t *)0x40064404)) //Interrupt Sense register, setting a bit configures the corresponding pin to detect levels, 0 is edge sensitive, 1 is level sensitive
#define GPIO_IBE_N (*((volatile uint32_t *)0x40064408)) //0, interrupt generation is controlled by GPIOIEV, 1, both edges on corresponding pin trigger an interrupt
#define GPIO_IEV_N (*((volatile uint32_t *)0x4006440C))  //0, falling edge/lowlevel triggers an interrupt, 1, rising edge/high level triggers interrupt
#define GPIO_ICR_N (*((volatile uint32_t *)0x4006441C)) //clear any prior interrupt
#define GPIO_IM_N (*((volatile uint32_t *)0x40064410))  //0, interrupt is masked , 1, interrupt is sent to interrrupt controller
#define GPIO_RIS_N (*((volatile uint32_t *)0x40064414)) // 0, interrupt condition has not occured, 1, interrupt condition has occured
#define GPIO_MIS_N (*((volatile uint32_t *)0x40064418)) // use this
//for edge detect interrupts, this bit is cleared by writing a 1 to the corresponding bit in the GPIOICR register


// Initializes the PLL module and generates a system clock frequency
// that equal to the frequency preset.
// Returns 1 if configured successfully, -1 if you select a non-exist preset.
int PLL_Init(enum frequency freq);

void switches_Init();

// Initializes ADC Module 0 Sample Sequencer 3. The module is triggered by
// Timer module 0 subtimer A at 1 HZ. The interupt of ADC0 SS3 will be
// generated whenever the A/D conversion is done.
void ADCReadPot_Init(void);

// Initializes Timer 0A to trigger ADC0 at 1 HZ.
void TimerADCTrigger_Init(void);

void ADC0SS3_Handler(void);

#endif //__TASK1B_H__