/*
 * Copyright (C) 2014 Microchip Technology Inc. and its subsidiaries.  You may use this software and any derivatives
 * exclusively with Microchip products.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS
 * SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE,
 * COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF
 * THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON
 * ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID
 * DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS.
 *
 *
 * File:        definitions.h
 * Date:        July 24, 2014
 * Compiler:    XC16 v1.21
 *
 * General definitions for the project
 *
 */

// Clock frequency
#define FCY (16000000)                                  //8MHz crystal x 4 PLL = 32 MHz (2 clocks per instruction)

#define _ISR_NO_AUTO_PSV __attribute__((interrupt,no_auto_psv))


#define BLE_WAKE_DORMANT LATBbits.LATB1                 //Wake RN4020 module from dormant or hibernate
#define BLE_WAKE_SLEEP LATFbits.LATF1                   //Wake RN4020 module from sleep mode
#define BLE_COMMAND_MODE LATFbits.LATF0                 //Place RN4020 module in command mode, low for MLDP mode

#define LINEAR_PORT1 LATBbits.LATB2
#define LINEAR_PORT2 LATBbits.LATB3



#define BLE_CONNECTED PORTFbits.RF6                     //Bluetooth module is connected to central device
#define BLE_AWAKE PORTEbits.RE8                         //Bluetooth module is awake and active
#define BLE_EVENT PORTEbits.RE9                         //Bluetooth in MLDP mode has a pending event

//UART baud rate
#define BRG_115200 ((FCY + 230400) / 460800 - 1)        //BRG value for 115,200 baud with BRGH = 1 (with rounding)

//Timer initialization
#define TIMER_OFF 0
#define TIMER_ON_PRESCALE1 0x8000
#define TIMER_ON_PRESCALE8 0x8010
#define TIMER_ON_PRESCALE64 0x8020
#define TIMER_ON_PRESCALE256 0x8030

#define TIMER_1MS_PERIOD (FCY / 1000 - 1)
#define TIMER_100US_PERIOD (FCY / 10000 - 1)

//Buffer sizes
#define SIZE_RxBuffer 1024//128
#define SIZE_TxBuffer 1024//128

#define TRUE 1
#define FALSE 0

#define BT_SOF_1 '='                                    //Start of frame to or from BLE Central
#define BT_SOF_2 '>'                                    //Start of frame to or from BLE Central


enum WhichBluetoothState {NotConnected, Connected};
enum BluetoothDecodeState {WaitForSOF1, WaitForSOF2, WaitForCommand, WaitForStart, WaitForData, WaitForCR, WaitForLF};

struct BT_Message
{
    char Kind;
    char Data[32];
};

