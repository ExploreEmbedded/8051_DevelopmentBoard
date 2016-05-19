/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
****************************************************************************************************
 * File:   eeprom.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library routines for Eeprom Read-Write

This code has been developed and tested on ExploreEmbedded boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider buying the ExploreEmbedded boards.
 
The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
***************************************************************************************************/



/***************************************************************************************************
                             Revision History
****************************************************************************************************
15.0: Initial version 
***************************************************************************************************/
#include"eeprom.h"
#include"i2c.h"
#include"delay.h"



/***************************************************************************************************
  void EEPROM_WriteByte(uint16_t v_eepromAddress_u16, uint8_t v_eepromData_u8)
***************************************************************************************************
 * I/P Arguments: uint16_t: eeprom_address at which eeprom_data is to be written
                  uint8_t: byte of data to be to be written in eeprom.
 * Return value    : none

 * description:This function is used to write the data at specified EEPROM_address..
               At24xx ic is enabled by sending its ID on the i2c bus.
               After selecting At24xx ic,select the address where the data is to written
               Write the Data at selected EppromAddress
               Stop the I2c communication.



    AT24xxx eeprom has two different memory addressing depending on the size of the.
    At24C01-At24C16 have single byte memory address where as AT24C32 to AT24C256 have 2-byte address.

    Further the AT24xxx series eeproms have the memory structure divided into pages.
    Size of the page depends on the IC series ex:At24C04 has 8-byte page where as AT24C04 has 16-bytes.

    -----------------------------------------------------------------------------------------
                        SingleByteAddress: AT24C01 - AT24C16
    ----------------------------------------------------------------------------------------*
    For single byte memory address, the actual address is obtained by the below formula.
    Actual page address = PageNumber * PageSize + Offset.
    ex: if address is 700(2*256 + 188) then the actual memory location is 188th byte of page 2(PageSize = 256)
    For a 16bit address d8-d10 represents the Page number and d0-d7 the byte number in that page.

    The page number has to be given as the part of eeprom Id(d1-d3)
    The Byte number within the page should be the address, which is sent after the device ID
    ------------------------------------------------------------------------------------------



    -----------------------------------------------------------------------------------------
                        DoubleByteAddress: AT24C32 - AT24C256
    -----------------------------------------------------------------------------------------
     For Double byte address, the 16bit address has to be sent as two bytes first MSB(D15 - D8)
     followed by LSB(D7 - D0)
    -----------------------------------------------------------------------------------------


    Note: User doesn't have to worry about the address decoding as the library takes care of it.
          It is just an info, so that proper IC needs to be selected in the eeprom.h file.        

***************************************************************************************************/
void EEPROM_WriteByte(uint16_t v_eepromAddress_u16, uint8_t v_eepromData_u8)
{    

    uint8_t v_eepromLowerAddress_u8;
    uint8_t v_eepromPageNumber_u8;
    uint8_t v_eepromId_u8 = C_EepromIdWriteMode_U8;
    
    #if (C_EepromIcType_U16 >  AT24C16)
        uint8_t v_eepromHigherAddress_u8;
    #endif

    if(v_eepromAddress_u16 < C_MaxEepromSize_U16)    
    {
        v_eepromLowerAddress_u8 = util_ExtractByte0to8(v_eepromAddress_u16);

#if (C_EepromIcType_U16 >  AT24C16)
        v_eepromHigherAddress_u8 = util_ExtractByte8to16(v_eepromAddress_u16);
#else
        v_eepromPageNumber_u8 = util_ExtractByte8to16(v_eepromAddress_u16);
        v_eepromId_u8 = v_eepromId_u8 | (v_eepromPageNumber_u8 << 1); 
#endif

        I2C_Start();                       // Start i2c communication
                                           // connect to At24xx by sending its ID on I2c Bus
        I2C_Write(v_eepromId_u8); 
#if (C_EepromIcType_U16 >  AT24C16)    
        I2C_Write(v_eepromHigherAddress_u8);
#endif        
        I2C_Write(v_eepromLowerAddress_u8); // Select the Specified EEPROM address of At24xx
        I2C_Write(v_eepromData_u8);         // Write the data at specified address
        I2C_Stop();                           // Stop i2c communication after Writing the data

        DELAY_ms(10);                         // Write operation takes max 5ms, refer At24xx data sheet 
    }    
}






/***************************************************************************************************
               uint8_t EEPROM_ReadByte(uint16_t v_eepromAddress_u16)
***************************************************************************************************
 * I/P Arguments: uint16_t: eeprom_address from where eeprom_data is to be read.
 * Return value    : uint8_t: data read from Eeprom.

 * description:
           This function is used to read the data from specified EEPROM_address.
           At24xx ic is enabled by sending its ID on the i2c bus.
           After selecting At24xx ic,select the address from where the data is to read
           Read the Data from selected EppromAddress
           Stop the I2c communication.
           Return the Data read from Eeprom


    AT24xxx eeprom has two different memory addressing depending on the size of the.
    At24C01-At24C16 have single byte memory address where as AT24C32 to AT24C256 have 2-byte address.

    Further the AT24xxx series eeproms have the memory structure divided into pages.
    Size of the page depends on the IC series ex:At24C04 has 8-byte page where as AT24C04 has 16-bytes.

    -----------------------------------------------------------------------------------------
                        SingleByteAddress: AT24C01 - AT24C16
    ----------------------------------------------------------------------------------------*
    For single byte memory address, the actual address is obtained by the below formula.
    Actual page address = PageNumber * PageSize + Offset.
    ex: if address is 700(2*256 + 188) then the actual memory location is 188th byte of page 2(PageSize = 256)
    For a 16bit address d8-d10 represents the Page number and d0-d7 the byte number in that page.

    The page number has to be given as the part of eeprom Id(d1-d3)
    The Byte number within the page should be the address, which is sent after the device ID
    ------------------------------------------------------------------------------------------



    -----------------------------------------------------------------------------------------
                        DoubleByteAddress: AT24C32 - AT24C256
    -----------------------------------------------------------------------------------------
     For Double byte address, the 16bit address has to be sent as two bytes, first MSB(D15 - D8)
     followed by LSB(D7 - D0)
    -----------------------------------------------------------------------------------------


    Note: User doesn't have to worry about the address decoding as the library takes care of it.
          It is just an info, so that proper IC needs to be selected in the eeprom.h file.        

***************************************************************************************************/           
uint8_t EEPROM_ReadByte(uint16_t v_eepromAddress_u16)
{
    uint8_t v_eepromLowerAddress_u8;
    uint8_t v_eepromPageNumber_u8;
    uint8_t v_eepromData_u8 = 0x00;
    uint8_t v_eepromId_u8 = C_EepromIdWriteMode_U8;
    #if (C_EepromIcType_U16 >  AT24C16)
    uint8_t v_eepromHigherAddress_u8;
    #endif

    if(v_eepromAddress_u16 < C_MaxEepromSize_U16)    
    {
        v_eepromLowerAddress_u8 = util_ExtractByte0to8(v_eepromAddress_u16);

#if (C_EepromIcType_U16 >  AT24C16)
        v_eepromHigherAddress_u8 = util_ExtractByte8to16(v_eepromAddress_u16);
#else
        v_eepromPageNumber_u8 = util_ExtractByte8to16(v_eepromAddress_u16);
        v_eepromId_u8 = v_eepromId_u8 | (v_eepromPageNumber_u8 << 1); 
#endif

        I2C_Start();                        // Start i2c communication
                                            // connect to At24xx by sending its ID on I2c Bus
        I2C_Write(v_eepromId_u8); 
#if (C_EepromIcType_U16 >  AT24C16)    
        I2C_Write(v_eepromHigherAddress_u8);
#endif        
        I2C_Write(v_eepromLowerAddress_u8); // Select the Specified EEPROM address of At24xx

        I2C_Start();                          // Start i2c communication after selecting the address
        I2C_Write(v_eepromId_u8 | 0x01);    // connect to At24xx(read) by sending its ID on I2c Bus
        v_eepromData_u8 = I2C_Read(0);      // Read the data from specified address
        I2C_Stop();                           // Stop i2c communication after Reading the data
        DELAY_us(10);

    }
    return v_eepromData_u8;             // Return the data read from eeprom
}





/***************************************************************************************************
void EEPROM_WriteNBytes(uint16_t v_eepromAddress_u16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16)
***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address from where the N-bytes are to be written.
                  uint8_t*: Buffer(Pointer) containing the N-Bytes of data to be written in Eeprom.
                  uint16_t :  Number of bytes to be written

 * Return value    : none

 * description:
            This function is used to write N-bytes of data at specified EEPROM_address.
****************************************************************************************************/
#if ( ENABLE_EEPROM_WriteNBytes == 1)
void EEPROM_WriteNBytes(uint16_t v_eepromAddress_u16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16)
{
    while(v_numOfBytes_u16 !=  0)
    {
        EEPROM_WriteByte(v_eepromAddress_u16,*ptr_ramAddress_u8); //Write a byte from RAM to EEPROM
        v_eepromAddress_u16++;                       //Increment the Eeprom Address
        ptr_ramAddress_u8++;                           //Increment the RAM Address
        v_numOfBytes_u16--;                       //Decrement NoOfBytes after writing each Byte
    }
}
#endif





/***************************************************************************************************
void EEPROM_ReadNBytes(uint16_t EepromAddr, uint8_t *RamAddr, uint16_t NoOfBytes)
***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address from where the N-bytes is to be read.
                  uint8_t*: Pointer to copy the N-bytes read from Eeprom.
                  uint16_t :  Number of bytes to be Read

 * Return value    : none

 * description:
            This function is used to Read N-bytes of data from specified EEPROM_address.
            The data read from the eeprom will be copied into the specified RamAddress.

    ##Note:    Care should be taken to allocate enough buffer to read the data.
****************************************************************************************************/
#if ( ENABLE_EEPROM_ReadNBytes == 1)
void EEPROM_ReadNBytes(uint16_t v_eepromAddress_16, uint8_t *ptr_ramAddress_u8, uint16_t v_numOfBytes_u16)
{
    while(v_numOfBytes_u16 !=  0)
    {
        *ptr_ramAddress_u8 = EEPROM_ReadByte(v_eepromAddress_16);//Read a byte from EEPROM to RAM
        v_eepromAddress_16++;                        //Increment the EEPROM Address
        ptr_ramAddress_u8++;                            //Increment the RAM Address
        v_numOfBytes_u16--;                        //Decrement NoOfBytes after Reading each Byte

    }
}
#endif







/***************************************************************************************************
 void EEPROM_WriteString(uint16_t v_eepromAddress_u16, char *ptr_stringPointer_u8)
***************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address where the String is to be written.
                  char*: Pointer to String which has to be written.

 * Return value    : none

 * description:This function is used to Write a String at specified EEPROM_address.

   NOTE: Null char is also written into the eeprom.
***************************************************************************************************/
#if ( ENABLE_EEPROM_WriteString == 1)
void EEPROM_WriteString(uint16_t v_eepromAddress_u16, char *ptr_stringPointer_u8)
{
    do
    {
        EEPROM_WriteByte(v_eepromAddress_u16,*ptr_stringPointer_u8); //Write a byte from RAM to EEPROM
        ptr_stringPointer_u8++;                                //Increment the RAM Address
        v_eepromAddress_u16++;                                //Increment the Eeprom Address
    }while(*(ptr_stringPointer_u8-1) !=0);
}
#endif




/***************************************************************************************************
void EEPROM_ReadString(uint16_t v_eepromAddress_u16, char *ptr_destStringAddress_u8)
****************************************************************************************************
 * I/P Arguments: uint16_t,: eeprom_address from where the String is to be read.
                  char*: Pointer into which the String is to be read.

 * Return value    : none

 * description:This function is used to Read a String from specified EEPROM_address.
           The string read from eeprom will be copied to specified buffer along with NULL character
****************************************************************************************************/
#if ( ENABLE_EEPROM_ReadString == 1)
void EEPROM_ReadString(uint16_t v_eepromAddress_u16, char *ptr_destStringAddress_u8)
{
    char eeprom_data;

    do
    {
        eeprom_data = EEPROM_ReadByte(v_eepromAddress_u16); //Read a byte from EEPROM to RAM
        *ptr_destStringAddress_u8 = eeprom_data;             //Copy the data into String Buffer
        ptr_destStringAddress_u8++;                         //Increment the RAM Address
        v_eepromAddress_u16++;                             //Increment the Eeprom Address
    }while(eeprom_data!=0);
}
#endif





/***************************************************************************************************
                                   void EEPROM_Erase(void)
****************************************************************************************************
 * I/P Arguments: none

 * Return value    : none

 * description: This function is used to erase the entire Eeprom memory.
               Complete Eeprom(C_MaxEepromSize_U16) is filled with 0xFF to accomplish the Eeprom Erase.
****************************************************************************************************/
#if ( ENABLE_EEPROM_Erase == 1)
void EEPROM_Erase(void)
{
    uint16_t v_eepromAddress_u16;

    for(v_eepromAddress_u16=0;v_eepromAddress_u16<C_MaxEepromSize_U16;v_eepromAddress_u16++)
    {
        EEPROM_WriteByte(v_eepromAddress_u16,0xffu); // Write Each memory location with OxFF
    }
}
#endif
