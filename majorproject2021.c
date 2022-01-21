/*
 * File:   EECS2021MajorProject.c
 * Author: Ajay Deonandan
 *
 * Created on December 6, 2021, 1:28 PM
 */

#include <xc.h>
#include <avr/io.h>
#include<util/delay.h>

//Global counter to be incremented by ASM
int global_counter = 0;
int main() {
    //Pins 2, 5 and 6 are outputs. The rest are inputs.
    DDRD = 0b00110010;
    //Pins 0, 1, 2, 3, 4 are outputs. The rest are inputs.
    DDRB = 0b00011111;

    //Set Up Servo Motor
    TCCR1A = (1<<WGM11) | (1 <<COM1A1);
    TCCR1B = (1<<WGM12) | (1 <<WGM13) | (1<<CS11);  
    ICR1 = 39999;
    
    //Initializing register values and storing to global counter
    resetCounter();
    
    //Variable to check if 'system' is on or not
    int sysOn = 0;
    
    //Main While loop. When this runs, the 'system' is on
    while(1){
        //If the Push button is pressed, Blue LED is turned on, next while loop initiates
        if((PIND&(1UL<<PIN7))){
            _delay_ms(2000);
            PORTD |= 0b00000010;
            sysOn = 1;
            
            //Turn on correct LED based on global counter. If global counter is too high (Capacity exceeded), while loop starts making it so rest of the code cannot progress 
            while(sysOn == 1){
                ledChooser();
                if(global_counter >= 7){
                    while(1){
                        //Awaiting button push to rest global counter and continue code
                        if(PINB&(1UL<<PIN4)){
                            resetCounter();
                            break;
                        }
                    }
                }
                //If motion sensor is triggered, open door and close it
                if(PIND&(1UL<<PIN2)){
                    openCloseDoor();
                }
                //If Push Button is pressed, the Blue LED turns off loop is broken.
                else if(PIND&(1UL<<PIN7)){
                    PORTD = 0b00000000;
                    sysOn = 0;
                    _delay_ms(1000);
                }
            }//while 2    
        }
        //If there is no push button press, Blue LED is off
        else {
            PORTD |= (0UL <<PIN1);
            PORTB = 0b00000000;
        }
    }//while 1
}    
    
//Method to open and close the Door (move servo) and turn LED on and off.
int openCloseDoor(){
    //Add 1 to the global counter (R16 + 1)
    asm("INC R16");
    //Store R16 to global counter
    asm("STS global_counter, R16");
    int offset = 800;  //Offset to straighten servo
    PORTD = 0b00010010;//Turn the RED Groove LED on
    OCR1A = 5000+offset; //Move Servo Arm forwards
    _delay_ms(60000);   //Wait
    OCR1A = 5000 - offset; //Move Servo Arm Back
    PORTD = 0b00000010;//Turn the RED Groove LED off
}

//Depending on the value of the global_counter, turn on a specific LED. If the counter is equal to the capacity limit then turn all LEDS on
int ledChooser(){
    if (global_counter < 3){
        PORTB = 0b00000100;
    }
    else if(global_counter >= 3 && global_counter < 4){
        PORTB = 0b00001000;
    } else if(global_counter >= 5 && global_counter <= 6){
        PORTB = 0b00000001;
    } else if (global_counter == 7){
        PORTB = 0b00001101;
    }
}

//Method to reset global_counter variable and R16 (back to 0)
int resetCounter(){
    //Set register 16 to 0
    asm("LDI R16, 0");
    //Store R16 to the global_counter
    asm("STS global_counter, R16");
}
