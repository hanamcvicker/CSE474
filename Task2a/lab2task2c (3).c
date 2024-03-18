/* Hana McVicker(1960220) and Diana Verduzco(1839513)
 * December 2, 2022
 * Main file for lab 4 task 2a.
 * This program uses the LCD display replicate a traffic light 
 *
 * This traffic light turns on and off with one of the on board buttons after 2 sec press
 * The other button acts as a pedestrian button, and when pressed for 2 sec when the light is 
 * green, will turn yellow and then red to indicate a stop light
 * When the pedestrian button is not pressed when green, the light will flash green and red 
 */

#include <stdint.h> 
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
//Header file 
#include "tm4c1294ncpdt.h"
#include "lab2task2_c.h"

//define traffic light LEDS
# define RED 1
# define YELLOW 2
# define GREEN 3
# define OFF 0

int LIGHT_TRACKER = 0;
int PED = 0;
int ON_OFF = 0;
int main(void) {
  Initialize_Timer0();
  Initialize_Timer1();
  LCD_Init();
  Touch_Init();

  LCD_DrawCircle(48, 65, 45, Color4[10]); //green
  LCD_DrawCircle(160, 65, 45, Color4[14]); //yellow
  LCD_DrawCircle(270, 65, 45, Color4[12]); //red

  LCD_DrawCircle(235, 175, 40, Color4[11]); //on/off button
  LCD_DrawCircle(115, 175, 40, Color4[15]); //ped button
   
  LCD_SetCursor(87,170);
  LCD_Printf("PEDESTRIAN");
  LCD_SetCursor(213,170);
  LCD_Printf("ON | OFF");
  
  while(1){
     if (Touch_ReadY() < 5000 && Touch_ReadY() > 800) { //y boundaries for buttons
      if (Touch_ReadX() > 1700) { //on/off button
       GPTMCTL1 = 0x1; //start 2 sec timer
       ON_OFF = ON_OFF + 1;
     } else if (Touch_ReadX() < 1500) { //ped button
       GPTMCTL1 = 0x1; //start 2 sec timer
       PED = PED + 1;
     } 
     }else {
       PED = 0;
       ON_OFF = 0;
     }
  }
  return 0;
}


//Initialize Timer 0, the 5 second timer
void Initialize_Timer0() {
  // timer configuration
  RCGCTimer |= 0x1; // Enable Timer 0 for A and B
  GPTMCTL0 = 0x0;  // Disable timer 0 for A and B
  GPTMCFG0 = 0x0; // Select 32-bit mode using GPTMCFG
  GPTMTAMR0 = 0x2; // Configure TAMR bit of GPTMTAMR (periodic timer mode)
  GPTMTAILR0 = 0x00F42400 * 5; // load the value 16,000,000 * 5 to GPTMTAILR
  // Interrupts
  INTERRUPT_EN0 |= 0x80000; // Enable interrupt #19  
  GPTMIMR0 = 0x1; // Enable  GPTM TImer A Time-Out Raw Interrupt

}
//Initialize Timer 1, the 2 second timer
void Initialize_Timer1() {
  // timer configuration
  RCGCTimer |= 0x2; // Enable Timer 1 for A and B
  GPTMCTL1 = 0x0;  // Disable timer 1 for A and B
  GPTMCFG1 = 0x0; // Select 32-bit mode using GPTMCFG
  GPTMTAMR1 = 0x1; // Configure TAMR bit of GPTMTAMRA (one shot timer mode) and counts down
  GPTMTAILR1 = 0x00F42400 * 2; // load the value 16,000,000*2 to GPTMTAILR
  //Interrupts
  INTERRUPT_EN0 |= 0x200000; //Enable interrupt #21
  GPTMIMR1 = 0x1; // Enable  GPTM Timer A Time-Out Raw Interrupt
  GPTMICR1 = 0x01; //clear timer 1 flag
} 

//This method controls the switching Lights when called
//Depending on what Light is currently on, the Light will turn red, yellow, or green
void Timer0A_Int_Handler() { 
  GPTMICR0 = 0x01; // clear timer flag to ensure 5 seconds
  if (LIGHT_TRACKER == GREEN) { //if LED is green, turn red
        LIGHT_TRACKER = RED;
        LCD_DrawFilledCircle(48, 65, 44, Color4[0]); //green
        LCD_DrawFilledCircle(160, 65, 44, Color4[0]); //yellow
        LCD_DrawFilledCircle(270, 65, 45, Color4[12]); //red
  } else if (LIGHT_TRACKER == RED) { //if LED is red, turn green
        LIGHT_TRACKER = GREEN;
        LCD_DrawFilledCircle(160, 65, 44, Color4[0]); //yellow
        LCD_DrawFilledCircle(270, 65, 44, Color4[0]); //red
        LCD_DrawFilledCircle(48, 65, 45, Color4[10]); //green
  } else if (LIGHT_TRACKER == YELLOW) { //if LED is yellow, turn red
        LIGHT_TRACKER = RED;
        LCD_DrawFilledCircle(48, 65, 44, Color4[0]); //green
        LCD_DrawFilledCircle(160, 65, 44, Color4[0]); //yellow
        LCD_DrawFilledCircle(270, 65, 45, Color4[12]); //red
  }
}

//This method does not take in any parameters and handles whether the button is still pressed
//when the timer has finished counting down after two seconds
//if on/off button is still pressed and the Lights are not on, the light will turn red and 
//restart the 5 sec timer
//If there are Lights are on and the on/off button is pressed after two seconds, the lights will turn off
//if Ped button is still pressed after two seconds and the LED is at green, the LED will turn yellow, 
//but only when the LED is Green
void Timer1A_Int_Handler() {
  GPTMICR1 = 0x1; //when timer times out, clear the 2 sec timer
  if (Touch_ReadX() > 1050 && Touch_ReadX() < 2000) {
    Initialize_Timer0();
    if (PED > 0) {//ped button
      if (LIGHT_TRACKER == GREEN) {
        LIGHT_TRACKER = YELLOW;
        GPTMCTL0 = 0x1; //turn on five sec timer
        LCD_DrawFilledCircle(48, 65, 44, Color4[0]); //green
        LCD_DrawFilledCircle(270, 65, 44, Color4[0]); //red
        LCD_DrawFilledCircle(160, 65, 45, Color4[14]); //yellow
        GPTMCTL1 = 0x0; //turn off 2 sec timer
      }
    }
    if (ON_OFF > 0) { 
      if (LIGHT_TRACKER == OFF) { //device is off
        LIGHT_TRACKER = RED;
        LCD_DrawFilledCircle(270, 65, 45, Color4[12]); //red
        GPTMCTL0 = 0x1; //turn on five sec timer
      } else { //turn off
        LCD_DrawFilledCircle(48, 65, 44, Color4[0]); //green
        LCD_DrawFilledCircle(270, 65, 44, Color4[0]); //red
        LCD_DrawFilledCircle(160, 65, 44, Color4[0]); //yellow
        LIGHT_TRACKER = OFF;
        Initialize_Timer0();
      }
      GPTMCTL1 = 0x0; //turn off 2 sec timer
    }
  }
} 
  








