# Task 1

## Task 1b
We needed to display the temperature readings of the TM4C on the LCD. We also
needed to print the readings in Celsius and Fahrenheit using the given format in the lab 4 specifications.
In addition, we were tasked to print the current clock frequency with the readings. This message was to be
printed at the top of the display and with no extra characters. To ensure the message was displayed at the
top of the display, we used the provided LCD_SetCursor() function with (0,0) coordinates. The
functionality of Lab 3 was to be kept so we still needed to be able to change the clock frequency by using
the 2 onboard switches. To print the correct temperature readings, we had to complete the
LCD_PrintFloat() function which printed the value of the temperature with at least 2 decimal places. This
function was implemented by first creating a buffer to use the sprintf() function to find the total number of
characters and store each character in the character buffer. The characters stored in the buffer are then
printed one by one using the LCD_PrintChar() method. The main function of Task 1b took care of
printing the message and correct temperature value using the LCD_Printf() and LCD_PrintFloat()
functions. In main, we also checked which button was pressed and set the frequency accordingly. The
LCD displayed the current temperature in Celsius and in Fahrenheit and updated appropriately each time
the frequency changed just like it did in Lab3 with UART communication.

## Task 1c 
We used the touch-screen functionality of the LCD to create two virtual buttons with
12 MHz and 120 MHz labels that imitated the functionality of the 2 onboard switches. When one of the
buttons on the LCD was pressed, the temperature with either a clock frequency of 120 MHz or 12 Mhz
was displayed at the top of the screen in Celsius and in Fahrenheit. To achieve these results, we had to
check the position of the buttons and whether the stylus was touching any of that area. If it did, the LCD
would display whatever temperature was coming from the board depending on what frequency button was
pressed. To implement this task, we started by creating both of our buttons using the LCD_DrawCircle()
to create two buttons, one labeled with “12 MHz” and another labeled “120 MHz,” which would change
the frequency to that value depending on which button was pressed. To figure out where to place the
buttons, we set the x and y values in the LCD_DrawCircle() to random coordinates until we had a
placement we wanted on the board. To get the buttons to actually work on a button press, we used the
Touch_ReadX() and Touch_ReadY() functions. We used the SetCursor() function to print the
TouchReadX() and TouchReadY() values at the edges of our circle buttons to get the correct boundary
coordinates. Once we got the button presses working, we just created if statements depending on the boundaries 
of the buttons and changed the frequency depending on whether the 12 MHz button was pressed or the 120 MHz was pressed,
and set the the PLL_Init() to the new frequency.

# Task 2

## Task 2a
We needed to implement the virtual traffic light controller using the LCD display
board. It had to have the same functionality as previous labs, meaning the light should turn on after a 2
second button hold on on/off button and start at red, stay on for five seconds if the on/off button is not
pressed, turn green, stay on for five seconds if no button is pressed for 2 seconds and go to red. If the
pedestrian button is pressed for two seconds and the green light is on, the light should turn yellow five
seconds and then red if the on and off button is not pressed for two seconds. We used interrupts to control
the timing on the lights and the button presses. Before we even tried to implement the buttons, we first
needed to position our traffic lights and buttons on the display, which was done using the LCD_DrawCircle() 
function. To get the boundaries for the buttons, we again used the LCD_SetCursor function to mark the edges of the circle
buttons for our boundary cutoffs. 


## Task 2b
We were tasked to implement the traffic light controller using RTOS instead. The
results had the same functionality as the previous task, and the system had to be running at 60 MHz.We
first had to prepare running RTOS on the TIVA board by downloading and installing the given program
and configuring certain files in the correct folder we were using. We were given the main file which
included skeleton code so we had to complete the missing parts. This included setting the clock frequency
to 60 MHz using the PLL_Init() file and PLL header, initializing the display and touch functionalities, and
creating the virtual buttons/ lights in main which were both already done from the previous task. We also
needed to assign priorities to tasks created in main. The highest priority task was the start/stop task, next
was the pedestrian button and finally the control FSM was the lowest priority task. We chose to assign the
priorities this way because the on/off button should always work, even if the pedestrian button was also
pressed. After doing this, we needed to complete each task function implementation. Each task function
(start/stop, pedestrian, control checked whether the virtual buttons were pressed for a specific amount of
time and set global flags as needed. This meant for the stop/start button we needed to check whether the
difference between the current and previous ticks were greater than 2 secs and if it was we set the
onoff_status to 1. Otherwise, we cleared the flag. This similar implementation was used for the pedestrian
task function. For the control task function, we needed to check if any of the lights were on for 5 seconds
or more and then switched to the next corresponding state and reset the light tick. To switch from one
state to another, we implemented the FSM() function that had states which checked the onoff_status
variable and/or the pedestrian_status variable which told us whether the on/off button was on or the
pedestrian button was pressed and changed states accordingly. This function also took care of drawing the
filled in circle for each light on the board when it needed to be filled.
