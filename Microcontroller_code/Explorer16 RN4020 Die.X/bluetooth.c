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
 * File:        Bluetooth.c
 * Date:        July 24, 2014
 * Compiler:    XC16 v1.21
 *
 * Functions to communicate with a RN4020 Bluetooth LE module over a UART
 *
 */

#include <xc.h>
#include "definitions.h"
#include "UART.h"
#include "timers.h"
#include "Bluetooth.h"
#include "string.h"
#include <stdlib.h>
//**********************************************************************************************************************
// Send a message over the Bluetooth link
int m=0;
char BT_SendPacket(char data)
{
    WriteTxBuffer(BT_SOF_1);                        //Load preamble / start of frame bytes into the transmit buffer
    WriteTxBuffer(BT_SOF_2);
    WriteTxBuffer('D');        //Load the command byte into the transmit buffer
    WriteTxBuffer(data);           //Load the data byte into the transmit buffer
    WriteTxBuffer('\r');                            //Load carriage return
    WriteTxBuffer('\n');                            //Load line feed
    UART_TxStart();                                 //Start the transmission
    return TRUE;
}

//**********************************************************************************************************************
// Receive a message over the Bluetooth link

char BT_ReceivePacket(struct BT_Message *Message)
{
    static enum BluetoothDecodeState btDecodeState = WaitForSOF1;   //Static so maintains state on reentry
    char messageChar;                                   //Byte read from the UART buffer
    if (IsNewRxData())                                  //Check if new data byte from BT module and return if nothing new
    {
        messageChar = ReadRxBuffer();                   //Read the data byte for processing
        switch(btDecodeState)
        {
        case WaitForSOF1:                               //Waiting to receive first start of frame character, SOF1
            if (messageChar == BT_SOF_1)                //See if we got the SOF1 character
                btDecodeState = WaitForSOF2;            //then wait for the second start of frame character, SOF2
            break;
        case WaitForSOF2:                               //Waiting to receive second start of frame character, SOF2
            if(messageChar == BT_SOF_2)                 //See if this is the second of the two byte start Of frame
                btDecodeState = WaitForCommand;         //Is complete SOF1, SOF2 pattern so wait for command byte
            else
                btDecodeState = WaitForSOF1;            //Did not get complete SOF1, SOF2 pattern so look for new start of frame
            break;
        case WaitForCommand:                            //Waiting to receive command byte
            Message->Kind = messageChar;             //Save byte as command byte of the message
            btDecodeState = WaitForStart;                //Indicate now waiting for data byte            
            break;
        case WaitForStart:
            btDecodeState = WaitForData;            
            break;
        case WaitForData:                               //Waiting to receive data byte
            
            if(messageChar!=']'){ 
                if(messageChar!=','){
                    Message->Data[m]=messageChar;
                    m++;
                }
                btDecodeState= WaitForData;
            }else{             
                m = 0;
                btDecodeState = WaitForCR;                      //Indicate now waiting for CR
            }                          
            break;
        case WaitForCR:
            if(messageChar == '\r')                     //See if this is the CR
                btDecodeState = WaitForLF;              //Is CR so wait for LF
            else
                btDecodeState = WaitForSOF1;            //Did not get CR so look for new start of frame
            break;
        case WaitForLF:
            btDecodeState = WaitForSOF1;                //Will be looking for a new packet next
            if(messageChar == '\n')                     //See if this is the LF
                return TRUE;                            //Got a complete message!
            break;
        default:                                        //Invalid state so start looking for a new start of frame
            btDecodeState = WaitForSOF1;
        }
    }
    return FALSE;
}

//**********************************************************************************************************************
// Send a command to the RN4020 module

void BT_SendCommand(char *data)
{
    int i;

    for(i = 0; i < 25; i++)                             //Send up to 25 characters
 	{
        if(*data != '\0')                               //Keep loading bytes until end of string
            WriteTxBuffer(*data++);                     //Load byte into the transmit buffer
        else
            break;
	}
    UART_TxStart();                                     //Start transmitting the bytes
}

//**********************************************************************************************************************
// Send a byte to the RN4020 module

void BT_SendByte(char data)
{
    WriteTxBuffer(data);                                //Load byte into the transmit buffer
    UART_TxStart();                                     //Start transmitting the byte
}

//**********************************************************************************************************************
// Get a response from the RN4020 module

int BT_GetResponse(char *data)
{
    unsigned int byteCount = 0;
    char newByte;
    
    StartTimer(2, 100);                             //Start 100ms timeout for routine

    while(byteCount < 50)                           //Don't accept more than the buffer size
    {
        if(IsNewRxData())                           //Check if new data byte from BT module and return if nothing new
        {
            newByte = ReadRxBuffer();               //Read the data byte for processing
            *data++ = newByte;                      //Add it to the buffer
            byteCount++;                            //Keep track of the number of bytes received
            if(newByte == '\n')                     //Check if got linefeed
                return TRUE;                        //If linefeed then return success
        }
        if(TimerDone(2))                             //Check if timed out
            return FALSE;                            //If timed out then return failure
    }
    return FALSE;
}

//**********************************************************************************************************************
// Compare the buffer with the response with one of the expected responses

int BT_CompareResponse(char *data1, char *data2)
{
    unsigned int i;

    for(i = 0; i < 50; i++)                         //Compare up to 50 bytes
    {
        if(*data1 == '\0')                          //See if reached end of string with no bytes different
            return TRUE;                            //No bytes were different so return success
        else if(*data1++ != *data2++)               //else see if the bytes are different
            return FALSE;                           //Bytes differ so return failure
    }
    return FALSE;                                   //Did not reach end of string so return failure
}

//**********************************************************************************************************************
// Get a response from the RN4020 module and compare with an expected response

int BT_CheckResponse(char *data)
{
    unsigned int i, ByteCount = 0;
    char NewByte, Buffer[50], *BufPtr;

    StartTimer(2, 200);                             //Start 200ms timeout for routine

    BufPtr = Buffer;
    while(ByteCount < 50)                           //Don't accept more than the buffer size
    {
        if(IsNewRxData())                           //Check if new data byte from BT module and return if nothing new
        {
            NewByte = (char) ReadRxBuffer();        //Read the data byte for processing
            *BufPtr++ = NewByte;                    //Add it to the buffer
            ByteCount++;
            if(NewByte == '\n')                     //Check if got linefeed
                break;                              //If linefeed then we have what we want
        }
        if(TimerDone(2))                            //Check if timed out
            return FALSE;                           //If timed out then return failure
    }

    BufPtr = Buffer;
    for(i = 0; i < ByteCount; i++)                  //Compare all bytes received
    {
        if(*data == '\0')                           //See if reached end of string with no bytes different
            return TRUE;                            //No bytes were different so return success
        else if(*data++ != *BufPtr++)               //else see if the bytes are different
            return FALSE;                           //Bytes differ so return failure
    }
    return TRUE;                                    //All bytes matched so return success
}

//**********************************************************************************************************************
// Get a response from the RN4020 module and compare with an expected response
//   All incoming bytes in the position of the wildcard character are ignored
//   Use this to ignore text that changes, like MAC addresses.

int BT_CheckResponseWithWildcard(char *data, char Wildcard)
{
    unsigned int i, ByteCount = 0;
    char NewByte, Buffer[50], *BufPtr;

    StartTimer(2, 200);                             //Start 200ms timeout for routine

    BufPtr = Buffer;
    while(ByteCount < 50)                           //Don't accept more than the buffer size
    {
        if(IsNewRxData())                           //Check if new data byte from BT module and return if nothing new
        {
            NewByte = ReadRxBuffer();               //Read the data byte for processing
            *BufPtr++ = NewByte;                    //Add it to the buffer
            ByteCount++;
            if(NewByte == '\n')                     //Check if got linefeed
                break;                              //If linefeed then we have what we want
        }
        if(TimerDone(2))                            //Check if timed out
            return FALSE;                           //If timed out then return failure
    }

    BufPtr = Buffer;
    for(i = 0; i < ByteCount; i++)                  //Compare all bytes received
    {
        if(*data == '\0')                           //See if reached end of string with no bytes different
            return TRUE;                            //No bytes were different so return success
        else if(*data == Wildcard)                  //else see if expected response byte is a wildcard
        {
            data++;                                 //Increment past wildcard byte
            BufPtr++;                               //Increment to ignore byte correspinding to wildcard
        }
        else if(*data++ != *BufPtr++)               //else see if the bytes are different
            return FALSE;                           //Bytes differ so return failure
    }
    return TRUE;                                    //All bytes matched or were ignored so return success
}

//**********************************************************************************************************************
// Set up the RN4020 module with the correct name

int BT_SetupModule(char *Version)
{
    char buffer[50];
    unsigned int i, changes = FALSE;

    //Send "V" to get firmware version of module
    BT_SendCommand("v\r");                          //Get RN4020 module firmware version
    if(!BT_GetResponse(buffer))                     //Get response
        return 2;

    for(i = 0; i < 8; i++)                          //Copy up to eight bytes of version number text returned by the module
    {
        Version[i] = buffer[i + 11];                //Copy only the text after the "v" before the version number
        if(Version[i] == ' ')                       //Look for space after the version number
        {
            Version[i] = '\0';                      //End the line after the version number to ignore the date
            break;
        }
    }
    Version[8] = '\0';                              //For safety just in case no spaces were detected

    //Send "GR" to get feature settings
    BT_SendCommand("gr\r");                         //Get RN4020 module feature settings

    if(!BT_CheckResponse("32000C00\r\n"))           //Check if features are set for auto advertize, MLDP, flow control
    {                                               //auto enable MLDP, suppress messages during MLDP
        BT_SendCommand("sr,32000c00\r");            //Features not correect so set features
        if(!BT_CheckResponse("AOK\r\n"))
            return 3;
        changes = TRUE;                             //Have changed a setting so will have to reboot later
    }

    //Send "GN" to get the name of the device
    BT_SendCommand("gn\r");                         //Get RN4020 module name
    if(!BT_CheckResponse("BarBot\r\n"))               //Check if name is what we want
    {
        BT_SendCommand("sn,BarBot\r");                //Set name to what we want
        if(!BT_CheckResponse("AOK\r\n"))
            return 4;
        changes = TRUE;                             //Have changed a setting so will have to reboot later
    }
    //Use BT_CheckResponseWithWildcard() to ignore parts of the name that may change
    //    if(!BT_CheckResponseWithWildcard("BTA=************\r\n", '*'))

    //If settings were changed then reboot and verify that changes were saved
    if(changes == TRUE)                             //See if we made any changes and need a reboot
    {
        BT_SendCommand("wc\r");                     //Command to clear script, just in case there is a script
        if(!BT_CheckResponse("AOK\r\n"))
            return 5;

        //Send "R,1" to save changes and reboot
        if(!BT_Reboot())
            return 6;

        //Send "GR" to get feature settings
        BT_SendCommand("gr\r");                     //Get RN4020 module feature settings
        if(!BT_CheckResponse("32000C00\r\n"))       //Check if features are correct
            return 7;

        //Send "GN" to get the name of the device
        BT_SendCommand("gn\r");                     //Get RN4020 module name
        if(!BT_CheckResponse("BarBot\r\n"))           //Check if name is what we want
            return 8;
    }

    return TRUE;
}

//**********************************************************************************************************************
// Reboot the module to save changes

int BT_Reboot(void)
{
//    BLE_COMMAND_MODE = 0;                           //Ensure CMD/DATA pin low to avoid factory reset
    //Send "R,1" to save changes and reboot
    BT_SendCommand("r,1\r");                        //Force reboot
    if(!BT_CheckResponse("Reboot\r\n"))
        return FALSE;

    StartTimer(2, 200);                             //Start 200ms timeout to wait for the 0 byte output by the RN4020
    while(!IsNewRxData())                           //Wait for new byte from UART
    {
        if(TimerDone(2))                            //Check if timed out
            return FALSE;                           //If timed out then return failure
    }
    if (ReadRxBuffer() != 0)                        //Read the data byte and see if it is zero
        return FALSE;                               //If not zero then return failure

    StartTimer(2, 3000);                            //Start 3s timeout to wait for the reboot to occur
    while(!IsNewRxData())                           //Wait for new byte from UART
    {
        if(TimerDone(2))                            //Check if timed out
            return FALSE;                           //If timed out then return failure
    }

    if(!BT_CheckResponse("CMD\r\n"))                //Check that we received CMD indicating reboot is done
        return FALSE;

//    BLE_COMMAND_MODE = 1;                           //Return to Command mode

    return TRUE;
}

