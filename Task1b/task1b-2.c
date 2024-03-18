/*
 *Hana McVicker(1960220) and Diana Verduzco(1839513)
 * November 23, 2022
 * EE/CSE 474: Lab4 Task1b main function
 * This file displays the board temperature and clock frequency at the top of the screen of a LCD 
 * display and uses the onboard switches to change frequencies (12 MHz or 120MHz).
 */

#include <stdint.h>
#include <stdio.h>
#include "task1b_Inits.h"
#include "SSD2119_Display.h"

// STEP 0b: Include your header file here
#include "task1b.h"

uint32_t ADC_value;
enum frequency freq = PRESET2; // 60 MHz

int main(void) {
  LCD_Init(); // Initialize LCD
  LCD_ColorFill(Color4[13]); // bright magenta color
  // Select system clock frequency preset
 
  PLL_Init(freq);         // Set system clock frequency to 60 MHz
  switches_Init();        // Initialize switches (SW1 and SW2)
  ADCReadPot_Init();      // Initialize ADC0 to read from the potentiometer
  TimerADCTrigger_Init(); // Initialize Timer0A to trigger ADC0
  
  while(1) {
    float temp;
    temp =  (147.5 - ((75 * 3.3 * ADC_value) / 4096.0)); // calculation for temperature in Celsius
    LCD_SetCursor(0, 0); // Set cursor at top left
    LCD_Printf("The current temperature is "); // print message to screen
    LCD_PrintFloat(temp); // print temp in Celsius
    LCD_Printf(" C, ");
    LCD_PrintFloat((temp * 1.8) + 32.0); // print temp in Fahrenheit
    LCD_Printf(" F. \n");
    if(!(GPIODATA_J & 0x1)) { // SW1 pressed
      freq = PRESET3; // set frequency to 12 MHz
      PLL_Init(freq);
    } 
    if(!(GPIODATA_J & 0x2)) { // SW2 pressed
      freq = PRESET1; // set frequency to 120 MHz
      PLL_Init(freq);
    }
    LCD_Printf("The current clock frequency is %d MHz.\n", freq); // print frequency as an integer
    
  }
  return 0;
}

void ADC0SS3_Handler(void) {
  // STEP 4: Implement the ADC ISR.
  // 4.1: Clear the ADC0 interrupt flag
  ADCISC |= 0x8;
  GPTMICR0 = 0x1; // Clear timer flag
  
  // 4.2: Save the ADC value to global variable ADC_value
  ADC_value = ADCSSFIFO3;
}