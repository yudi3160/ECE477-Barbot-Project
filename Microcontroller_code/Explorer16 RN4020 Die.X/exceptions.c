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
 * File:        exceptions.c
 * Date:        July 24, 2014
 * Compiler:    XC16 v1.21
 *
 * Exception handlers for error traps
 * Specific peripheral interrupt routines are in the peripheral source files
 * Interrupt initialization is in the Initialize() function in main.c
 *
 */

//#include <xc.h>

//**********************************************************************************************************************
// Oscillator Fail error trap

void __attribute__((interrupt,no_auto_psv)) _OscillatorFail(void)
{
    while(1);       //For debugging only. Replace with real error handler in final application
}

//**********************************************************************************************************************
// Address error trap

void __attribute__((interrupt,no_auto_psv)) _AddressError(void)
{
    while(1);       //For debugging only. Replace with real error handler in final application
}

//**********************************************************************************************************************
// Stack error trap

void __attribute__((interrupt,no_auto_psv)) _StackError(void)
{
    while(1);       //For debugging only. Replace with real error handler in final application
}

//**********************************************************************************************************************
// Math error trap

void __attribute__((interrupt,no_auto_psv)) _MathError(void)
{
    while(1);       //For debugging only. Replace with real error handler in final application
}

