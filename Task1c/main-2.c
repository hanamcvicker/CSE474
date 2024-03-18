/* Hana McVicker(1960220) and Diana Verduzco(1839513)
 * December 2, 2022
 * Main file for Lab 4 task 1c.
 * This file displays the board temperature and clock frequency at the top of the screen of a LCD 
 * display and uses on board switches to change frequencies (12 MHz or 120MHz).
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdint.h>
#include <stdio.h>
#include "Lab3_Inits.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
//Header file 

#include "tm4c1294ncpdt.h"
             
// STEP 0b: Include your header file here
#include "task1b.h"

uint32_t ADC_value;


int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 12 MHz
  switches_Init();
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTrigger_Init(); // Initialize Timer0A to trigger ADC0
  LCD_Init(); //Initializes GPIOs for data and control signals.
  Touch_Init();
  float temp;
  temp =  (147.5 - ((75 * 3.3 * ADC_value) / 4096.0));
  while(1) {
    float temp;
    temp =  (147.5 - ((75 * 3.3 * ADC_value) / 4096.0)); // calculation for temperature in Celsius
    LCD_SetCursor(0, 0); // Set cursor at top left
    LCD_Printf("The current temperature is "); // print message to screen
    LCD_PrintFloat(temp); // print temp in Celsius
    LCD_Printf(" C, ");
    LCD_PrintFloat((temp * 1.8) + 32.0); // print temp in Fahrenheit
    LCD_Printf(" F. \n");
    
    LCD_DrawCircle(75, 150, 50, Color4[14]);
    LCD_DrawCircle(225, 150, 50, Color4[14]);
    
    LCD_SetCursor(50,150);
    LCD_Printf("12 MHz");
    LCD_SetCursor(200,150);
    LCD_Printf("120 Mhz"); 


      if ((Touch_ReadY() > 600) && (Touch_ReadY() < 3000)) { 
          if (Touch_ReadX() < 1400) { 
            freq = PRESET3; // set frequency to 12 MHz
            PLL_Init(freq);
          }
          if (Touch_ReadX() > 1600) {
            freq = PRESET1; // set frequency to 120 MHz
            PLL_Init(freq);
          }
      }
    LCD_SetCursor(0, 10); // Set cursor at top left
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

