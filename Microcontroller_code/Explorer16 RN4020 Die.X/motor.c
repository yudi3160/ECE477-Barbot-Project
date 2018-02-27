/*
 * File:   motor.c
 * Author: mac
 *
 * Created on February 28, 2017, 1:59 PM
 */


#include "xc.h"
#include "motor.h"
#include "timers.h"
#include "string.h"


//const int locations[8] = {125,645,1165,1685, 2215, 2735, 3255, 3775};
const int locations[8] = {100,1140,2180,3220, 4250, 5290, 6330, 7370};
const int push_height[8] = {2800,3050,3000,3000,2900,2900,2900,2900};

void Motor_initialize(void)
{
    Wait1ms(15);
    STEPPER_RESET = 1;
    STEPPER_FH = 0;
    STEPPER_CCW = 1;
    STEPPER_EN = 0;
    LINEAR_PORT1 = 0;
    LINEAR_PORT2 = 0;
    
    T2CONbits.TON = 0; // Timer off 
    T2CONbits.TCS = 0;
    T2CONbits.TGATE = 0;
    T2CONbits.TCKPS = 0;
    TMR2 = 0x00; // Prescale Value 
    PR2 = STEPPER_PERIOD * 2; // Set PWM Period
    T2CONbits.TON = 1; // Timer 2 on
    
    OC1CONbits.OCM = 0b000; // Clear whatever values are in 
    OC1R = 0x0F;
    OC1RS = 0x0F;
    OC1CONbits.OCTSEL = 0; //select timer 2
    OC1R = 0x0F;
    OC1CONbits.OCM = 0b110;
    Wait1ms(5);
    STEPPER_RESET = 0;
    Wait1ms(5);
    STEPPER_RESET = 1;
    Wait1ms(5);
}
//limit switch ??? if(==1)
void ProcessList(char * list){
    
    int i;
    int current_loc = 0;
    int next_loc = 0;
    for(i=0; i < 32; i++){
        
        if((list[i] - '0') == 0){
            break;
        }
        int drink = list[i] - '0';
        next_loc = locations[drink - 1];
        
        
        if(next_loc > current_loc){
           STEPPER_CCW = 1;
           STEPPER_EN = 1;
           Wait1ms(next_loc - current_loc);
           STEPPER_EN = 0;
           PushValve(drink);
           
        }else if (next_loc < current_loc){
           STEPPER_CCW = 0;
           STEPPER_EN = 1;
           Wait1ms(current_loc - next_loc);
           STEPPER_EN = 0;
           PushValve(drink);
        }else{
            
            PushValve(drink);
        }
        current_loc = next_loc;
        
            
    }
    STEPPER_EN = 1;
    STEPPER_CCW = 0;
    while(PORTBbits.RB8 != 0){
    }        
       
    STEPPER_EN = 0;
    return;
    
}

void PushValve(int drink){
    LINEAR_PORT1 = 1;
    LINEAR_PORT2 = 0;
    Wait1ms(push_height[drink-1]);
    LINEAR_PORT1 = 0;
    LINEAR_PORT2 = 0;
    Wait1ms(2500);
    LINEAR_PORT1 = 0;
    LINEAR_PORT2 = 1;
    Wait1ms(push_height[drink-1]);
    LINEAR_PORT1 = 0;
    LINEAR_PORT2 = 0;
}