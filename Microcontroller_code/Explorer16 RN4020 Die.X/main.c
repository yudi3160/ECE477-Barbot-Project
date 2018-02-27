#include <xc.h>
#include "config bits.h"
#include "definitions.h"
#include "timers.h"
#include "UART.h"
#include "Bluetooth.h"
#include "lcd.h"
#include "motor.h"
#include "stdlib.h"
#include "stdio.h"

void Initialize(void);                                      //Initialize function is below main() in this file

//**********************************************************************************************************************
// Text to display on LCD

const char LCD_BTDemo[] =           "The BarBot    ";
const char LCD_Connected[] =        "Connected       ";
const char LCD_Disconnect[] =       "Disconnected    ";
const char LCD_Initializing[] =     "Initializing... ";

const char LCD_Blank[] =            "                ";
const char LCD_FailedToWake[] =     "Failed to wake  ";
const char LCD_Error[] =            "Error ";
const char LCD_During[] =           " during";
const char LCD_Initialization[] =   "initialization  ";
const char LCD_Processing[] =   "Processing...  ";

//**********************************************************************************************************************
// Main routine - start of executable code

int main(void) {
    CLKDIVbits.RCDIV = 0;
    enum WhichBluetoothState bluetoothState = NotConnected; //State of Bluetooth connection
    struct BT_Message IncomingMessage, outgoingMessage;     //Structures for incoming and outgoing messages
    //unsigned int i, oldSwitchVal = 0, switchVal = 0;        //State of the four switches
    char bTVersion[9] = "\0";                               //String of text representing BT module firmware version
    char errorCode = FALSE, gotPacket = FALSE;              //errorCode TRUE if no error, gotPacket TRUE if valid packet

    Initialize(); //Initialize the pins and peripherals

     
    
    Motor_initialize();
    OC1RS = STEPPER_PERIOD/2;
    LCD_Initialize();                                       //Initialize the LCD display
    LCD_ClearScreen();                                      //Clear LCD and cursor to start of line 1
    LCD_WriteString((char *)LCD_BTDemo);                    //Show "Bluetooth Die" on the top line of the display
    LCD_CursorToLine2();                                    //Cursor to start of line 2
    LCD_WriteString((char *)LCD_Initializing);              //Show "Resetting..." on the top line of the display
    
    /*
    //Hold down switch S4 on RD13 while applying power to force a factory reset of the RN4020 module
    if(SWITCH_S4 == 0)                                      //See if switch S4 on RD13 is pressed
    {
        
        for(i = 0; i < 3; i++)                              //Toggle wake pin 3 times to do a factory reset of RN4020
        {                                                   //This code has not been tested!
            Wait1ms(100);                                   //Keep WAKE pin high for some time
            BLE_WAKE_DORMANT = 0;                           //Set wake low
            Wait1ms(100);                                   //Keep WAKE pin low for some time
            BLE_WAKE_DORMANT = 1;                           //Set wake high
        }
        switchVal = 1;                                      //Record that the switch is pressed
        
    }
     */
    LCD_Initialize();                                       //Initialize the LCD display
    LCD_ClearScreen();                                      //Clear LCD and cursor to start of line 1
    LCD_WriteString((char *)LCD_BTDemo);                    
    LCD_CursorToLine2();                                    //Cursor to start of line 2
    LCD_WriteString((char *)LCD_Initializing);              //Show "Resetting..." on the top line of the display
    /*
    if(switchVal == 1){                                      //See if we are doing a factory reset 
        Wait1ms(1000);
    }
     */
                                                            //Give the module time to do a factory reset
    
    StartTimer(2, 2000);                                    //Start 100ms timeout for routine
    
    while(BLE_AWAKE == 0)                                   //Wait for module to wake up
    {
        if(TimerDone(2))                                    //Check if timed out
        {
            LCD_CursorToLine2();                            //Cursor to start of line 2
            LCD_WriteString((char *)LCD_FailedToWake);      //Show "Failed to wake" on the display
            while(1);
        }
    }
     
    Wait1ms(100);                                           //Give the module time

    while(IsNewRxData())                                    //While buffer contains old data
        ReadRxBuffer();                                     //Keep reading until empty

    errorCode = BT_SetupModule(bTVersion);                  //Set up RN4020 module 
    UART_EnableFlowControl();                               //Enable flow control since module now set up to use it

    if(errorCode == TRUE)                                   //See if setting up the RN4020 module was successful
    {
        LCD_CursorToLine2();                                //Cursor to start of line 2
        LCD_WriteString((char *)LCD_Blank);                 //Clear line for version
        LCD_CursorToLine2();                                //Cursor to start of line 2
        LCD_WriteString((char *)"Welcome");               //Successfully set up the BT module so
                              
    }
    else                                                    //Failed to set up the BT module so show message
    {
        LCD_ClearScreen();                                  //Clear LCD and cursor to start of line 1
        LCD_WriteString((char *)LCD_Error);                 //Show "Error " on the top line of the display
        if (errorCode >= 10)                                //See if errorCode >=10 (is always less than 20)
        {
            LCD_WriteData('1');                             //display '1' on LCD
            LCD_WriteData((char) '0' + errorCode - 10);     //display units digit on LCD
        }
        else
        {
            LCD_WriteData((char) '0' + errorCode);          //display error digit on LCD
        }

        LCD_WriteString((char *)LCD_During);                //Show "during" on the top line of the display
        LCD_CursorToLine2();                                //Cursor to start of line 2
        LCD_WriteString((char *)LCD_Initialization);        //Show "applying power" on the second line of the display
        while(1);                                           //Wait for hardware reset
    }

    
    //switchVal = 0;

    //------------------------------------------------------------------------------------------------------------------
    // Main loop

    while (1)
    {
        
        if(bluetoothState == NotConnected && BLE_CONNECTED == 1) //Check if BLE Central has connected
        {
            bluetoothState = Connected;                     //BLE Central has connected to our module
            LCD_CursorToLine2();
            LCD_WriteString((char *)"Welcome");         

        }
        else if(bluetoothState == Connected && BLE_CONNECTED == 0) //Check if BLE Central has disconnected
        {
            LCD_ClearScreen();
            LCD_WriteString((char *)LCD_BTDemo);
            bluetoothState = NotConnected;                  //BLE Central has disconnected from our module
            LCD_CursorToLine2();
            LCD_WriteString((char *)LCD_Disconnect);        //Print "Disconnected on the LCD display
                                 
        }

        if(bluetoothState == Connected)                     //Only do main code if the Central is connected
        {

            gotPacket = BT_ReceivePacket(&IncomingMessage); //Get new message if one has been received from the RN4020
            
            if(gotPacket == TRUE)                           //TRUE if new packet received
            {
                LCD_ClearScreen();
                LCD_WriteString((char *)LCD_Processing);
                LCD_CursorToLine2(); 
                
                
                switch(IncomingMessage.Kind){
                    case 'a':
                        LCD_WriteString("Arizona Sunset");
                        break;
                 
                    case 'p':
                        LCD_WriteString("Pineapple Punch ");
                        break;
                    case 'i':
                        LCD_WriteString("LI Iced Tea");
                        break;
                    case 'o':
                        LCD_WriteString("Orange Fizz");
                        break;
                    case 'g':
                        LCD_WriteString("Gabbie's Punch");
                        break;
                    case 'n':
                        LCD_WriteString("Cinderalla");
                        break;
                    case 'c':
                        LCD_WriteString("Custom Drink");
                        break;
                           
                    default:
                        LCD_WriteString("No drink exists");
                }
                //LCD_ClearScreen();
                //LCD_WriteString((char*)IncomingMessage.Data);
                ProcessList(IncomingMessage.Data);
                
                int ii;
                for(ii=0;ii<32;ii++){
                    IncomingMessage.Data[ii] = 0;
                }
                BT_SendPacket(IncomingMessage.Kind);
                
                LCD_ClearScreen();
                LCD_WriteString((char *)"Your Drink is Done");
                LCD_CursorToLine2();
                LCD_WriteString((char *)"Enjoy!");
                Wait1ms(2000);

                //else if()...
            }
        }
    } //End of while(1) main loop
    return (TRUE);
}


// Initialize the pins and peripherals

void Initialize(void)
{
    AD1PCFG = 0xffcf;               //All digital I/O except AN4 for temperature sensor and AN5 for potentiometer
    LATA = 0x0000;                  //All LEDs off
    TRISA = 0xff00;                 //RA0-RA7 are active high LED outputs
    LATB = 0x0002;                  //RB1 Wake from Dormant high
    TRISB = 0xf3c0;                 //RB1 is an output
    LATD = 0x0000;                  //Start with RD15 U1RTS low
    TRISD = 0x7fff;                 //RD15 is U1RTS output, RD14 is U1CTS input
    LATF = 0x000b;                  //RF0 CMD, RF3 U1TX, RF1 WAKE_NOTSLEEP pin high
    TRISF = 0xfff4;                 //RF2 U1RX input, RF6 not connected input, RF7 PIO8 input, RF8 duplicate AWAKE input
    
    
    UART_Init();                    //Initialize the UART
    Iimers_Init();                  //Initialize the timers

    INTCON1 = 0;                    //Interrupt nesting enabled
    INTCON2 = 0;                    //GIE off, ext interrupts on rising edge
//    INTCON2bits.GIE = 1;            //Global enable interrupts (for dsPIC33EP and PIC24EP devices
}

