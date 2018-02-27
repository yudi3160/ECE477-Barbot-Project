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
 * File:        config bits.h
 * Date:        July 24, 2014
 * Compiler:    XC16 v1.21
 *
 * Configuration bits for a PIC24FJ128GA010 on an Explorer-16 board
 * Automatically generated code created by MPLAB X
 *
 */

#include <p24Fxxxx.h>
/*
 int CONFIG2 __attribute__((space(prog), address(0x157FC))) = 0x7B3D ;
//_CONFIG2(
//    POSCMOD_XT &         // Primary Oscillator Select (XT Oscillator mode selected)
//    OSCIOFNC_OFF &       // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
//    FCKSM_CSECME &       // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is enabled)
//    FNOSC_PRIPLL &       // Oscillator Select (Primary Oscillator with PLL module (HSPLL, ECPLL))
//    IESO_OFF             // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)
//);
 int CONFIG1 __attribute__((space(prog), address(0x157FE))) = 0x3F7F ;
//_CONFIG1(
//    WDTPS_PS32768 &      // Watchdog Timer Postscaler (1:32,768)
//    FWPSA_PR128 &        // WDT Prescaler (Prescaler ratio of 1:128)
//    WINDIS_ON &          // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
//    FWDTEN_OFF &         // Watchdog Timer Enable (Watchdog Timer is disabled)
//    ICS_PGx2 &           // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
//    GWRP_OFF &           // General Code Segment Write Protect (Writes to program memory are allowed)
//    GCP_OFF &            // General Code Segment Code Protect (Code protection is disabled)
//    JTAGEN_OFF           // JTAG Port Enable (JTAG port is disabled)
//);
*/
 

// PIC24FJ128GA010 Configuration Bit Settings

// 'C' source line config statements

// CONFIG2
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSECME           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL           // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config IESO = OFF               // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) disabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2               // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
