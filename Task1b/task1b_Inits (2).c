/**
 * Hana McVicker(1960220) and Diana Verduzco(1839513)
 * November 17, 2022
 * EE/CSE 474: Lab3 drivers starter code
 * This file initializes the PLL driver, the on-board switches, the initializations needed to read
 * from the potentiometer, and a ADC Trigger timer handler.e
 */

#include "PLL_Header.h"
#include "task1b_Inits.h"

// STEP 0a: Include your header file here
#include "task1b.h"

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6)); // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0)); // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5)); // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);               // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void switches_Init(void) {
  RCGCGPIO |= 0x100; // Enable PortJ GPIO   
  
  GPIODIR_J &= ~0x1; // Set PJ0 to input
  GPIODEN_J |= 0x1;  // Set PJ0 to digital port
  GPIOPUR_J |= 0x1;  // Attach pull-up resistor to PJ0
  
  GPIODIR_J &= ~0x2; // Set PJ1 to input
  GPIODEN_J |= 0x2;  // Set PJ1 to digital port
  GPIOPUR_J |= 0x2;  // Attach pull-up resistor to PJ1
}

void ADCReadPot_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 0x1;
  
  // 2.2: Delay for RCGCADC (Refer to page 1073) // TODO
  for (int i = 0; i < 10000; i++){}

  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ALTCLKCFG = 0x0;
  ADCCC |= 0x1;
  
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  RCGCGPIO |= 0x10; // enable port E
  
  // 2.7: Delay for RCGCGPIO
  for (int i = 0; i < 10000; i++){}
  
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= 0x08; // PE3
  
  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= ~0x08;

  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E &= ~0x08;
  
  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS &= ~0x08;
  
  // 2.12: Select timer as the trigger for SS3
  ADCEMUX |= 0x5000;
  
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSMUX3 &= 0x0;
   
  // 2.14: Configure ADCSSCTL3 register
  ADCSSCTL3 |= 0xE;
  
  // 2.15: Set the SS3 interrupt mask
  ADCIM |= 0x8;
    
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  INTERRUPT_EN0 |= 0x20000;
  
  // 2.17: Enable ADC0 SS3
  GPIODEN_E |= 0x8;
  ADCACTSS |= 0x8;
  
  ADCSSTSH3 |= 0x4; // sample and hold width for 16 ADC clocks
}

void TimerADCTrigger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  RCGCTimer = 0x1;
  for (int i = 0; i < 10000; i++){} // delay
  GPTMCTL0 = 0x0;  // Disable timer A
  GPTMCFG0 = 0x0; // Select 32-bit mode using GPTMCFG
  GPTMTAMR0 = 0x2; // Configure TAMR bit of GPTMTAMR(periodic timer mode)
  GPTMADCEV = 0x1; // Timer A Time-out Event ADC trigger enabled
  GPTMTAILR0 = 0xF42400; // Load the value 16,000,000 to GPTMTAILR
  GPTMICR0 = 0x1; // Clear flag
  GPTMCTL0 = 0x21; // Turn timer on
}

// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler