/*
 *  OFB_SST26V.c
 *
 *  Created on: 6 Nis 2021
 *      Author: m.omerfarukbulut@gmail.com
 *
 *      DP : This library designed work with only traditional SPI. It doesn't support QSPI...
 *
 *
 */


#include "app.h" //be carefull about name of top header file of project

extern SPI_Selections SPI_CFG;


/* ----------------------------------------------------------------------------
 * Function      : static void Flash_Error_Handler(SPI_ERROR_MSG_TYPE message)
 * ----------------------------------------------------------------------------
 * Description   : This function is error handler. Function takes an argument as type as SPI_ERROR_MSG_TYPE.
 *                 That provides find easily error.
 * Inputs        : - message        - Message type
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
static void Flash_Error_Handler(SPI_ERROR_MSG_TYPE message) {

    switch (message) {

        case Init_Flash_ERR:
            while (1)
                ;
            break;
        case NO_Operation_ERR:
            while (1)
                ;
            break;
        case Reset_Enable_ERR:
            while (1)
                ;
            break;
        case Reset_Memory_ERR:
            while (1)
                ;
            break;
        case ERASE_Sector_ERR:
            while (1)
                ;
            break;
        case ERASE_Sector_Addr_ERR:
            while (1)
                ;
            break;
        case ERASE_Block_ERR:
            while (1)
                ;
            break;
        case ERASE_Block_Addr_ERR:
            while (1)
                ;
            break;
        case ERASE_Full_Memory_ERR:
            while (1)
                ;
            break;
        case ERASE_Process_Select_ERR:
            while (1)
                ;
            break;
        case Suspend_ERR:
            while (1)
                ;
            break;
        case Resume_ERR:
            while (1)
                ;
            break;
        case Write_Enable_ERR:
            while (1)
                ;
            break;
        case Page_Program_ERR:
            while (1)
                ;
            break;
        case Read_Config_Status_ERR:
            while (1)
                ;
            break;
        case Read_Status_ERR:
            while (1)
                ;
            break;
        case Read_Memory_ERR:
            while (1)
                ;
            break;
        case Write_Config_ERR:
            while (1)
                ;
            break;

        default:
            while (1)
                ; //unknown error
            break;

    }

}


/* ----------------------------------------------------------------------------
 * Function      : void SST26_Init_Flash_Device()
 * ----------------------------------------------------------------------------
 * Description   : Initialize Flash Device
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Init_Flash_Device() {



    if (!Init_SPI_Flash_Device()) Flash_Error_Handler(Init_Flash_ERR);

    OFB_SPI_CS_High(SPI_CFG.number_SPI);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(SPI_CFG.number_SPI);

    //NO Operation for Nothing
    if (!SPI_SEND_CMD(Rx_Array, NO_OPERATION, 1, 8)) Flash_Error_Handler(NO_Operation_ERR);

    OFB_SPI_CS_High(SPI_CFG.number_SPI);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);

    SST26_Reset();

    //Read Status Register here and check some status bit for is flash device ready to go?

}


/* ----------------------------------------------------------------------------
 * Function      : void SST26_Reset()
 * ----------------------------------------------------------------------------
 * Description   : Send reset command to Flash Device
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Reset() {

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    //Reset Enable to Reset Flash Device
    if (!SPI_SEND_CMD(Rx_Array, RESET_ENABLE, 1, 8)) Flash_Error_Handler(Reset_Enable_ERR);
    OFB_SPI_CS_High(0);

    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);
    //Reset Flash Device
    if (!SPI_SEND_CMD(Rx_Array, RESET_MEMORY, 1, 8)) Flash_Error_Handler(Reset_Memory_ERR);

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);
    //Reset Quad Spý Mode to Traditional SPI Mode
    if (!SPI_SEND_CMD(Rx_Array, RESET_QUAD_IO, 1, 8)) Flash_Error_Handler(Reset_Quad_IO_ERR);
    OFB_SPI_CS_High(0);
}

/* ----------------------------------------------------------------------------
 * Function      : void SST26_Write_Disable()
 * ----------------------------------------------------------------------------
 * Description   : Send write disable command to Flash Device
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Write_Disable() {

    if (!SPI_SEND_CMD(Rx_Array, WRITE_DISABLE, 1, 8)) Flash_Error_Handler(Write_Disable_ERR);

}

/* ----------------------------------------------------------------------------
 * Function      : void SST26_Write_Enable()
 * ----------------------------------------------------------------------------
 * Description   : Send write enable command to Flash Device
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Write_Enable() {

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);
    if (!SPI_SEND_CMD(Rx_Array, WRITE_ENABLE, 1, 8)) Flash_Error_Handler(Write_Enable_ERR);
    OFB_SPI_CS_High(0);
}

/* ----------------------------------------------------------------------------
 * Function      : void SST26_Write_Config_Reg()
 * ----------------------------------------------------------------------------
 * Description   : Send write configuration register command to Flash Device
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Write_Config_Reg(uint8_t conf_data) {

    SST26_Write_Enable();

    /*    SST26_Read_Status();

     if( ((rxfln&0x02)>1) ==0 ){

     SST26_Write_Enable();
     SST26_Read_Status();

     }*/

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);

    if (!SPI_SEND_CMD(Rx_Array, WRITE_STATUS_REGISTER, 1, 8)) Flash_Error_Handler(Write_Config_ERR);
    if (!SPI_SEND_CMD(Rx_Array, WRITE_STATUS_REGISTER, 1, 8)) Flash_Error_Handler(Write_Config_ERR);
    if (!SPI_SEND_CMD(Rx_Array, conf_data, 1, 8)) Flash_Error_Handler(Write_Config_ERR);

    OFB_SPI_CS_High(0);
}

/* ----------------------------------------------------------------------------
 * Function      : SST26_Erase_Flash(uint8_t Scope_Erase, uint32_t Erase_addr)
 * ----------------------------------------------------------------------------
 * Description   : Erase sector,block or all chip
 * Inputs        : - Scope_Erase    - Select Erase Area
 *                 - Erase_addr     - Erase Area Address
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Erase_Flash(uint8_t Scope_Erase, uint32_t Erase_addr) {

    SST26_Write_Enable();

    //check here if write enabled
    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);

    switch (Scope_Erase) {
        case Erase_Sector:
            if (!SPI_SEND_CMD(Rx_Array, ERASE_4KBYTES_MEMORY, 1, 8)) Flash_Error_Handler(ERASE_Sector_ERR);
            if (!SPI_SEND_CMD(Rx_Array, Erase_addr, 1, 24)) Flash_Error_Handler(ERASE_Sector_Addr_ERR); //addr
            break;

        case Erase_Blocks:
            if (!SPI_SEND_CMD(Rx_Array, ERASE_XKBYTES_MEMORY, 1, 8)) Flash_Error_Handler(ERASE_Block_ERR);
            if (!SPI_SEND_CMD(Rx_Array, Erase_addr, 1, 24)) Flash_Error_Handler(ERASE_Block_Addr_ERR); //addr
            break;

        case Erase_Chip:
            if (!SPI_SEND_CMD(Rx_Array, ERASE_FULL_MEMORY, 1, 8)) Flash_Error_Handler(ERASE_Full_Memory_ERR);
            break;

        default:
            Flash_Error_Handler(ERASE_Process_Select_ERR);
            break;

    }

    OFB_SPI_CS_High(0);

}


/* ----------------------------------------------------------------------------
 * Function      : void SST26_Flash_Suspend()
 * ----------------------------------------------------------------------------
 * Description   : - Suspend continue process (program/erase)
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Flash_Suspend() {

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);
    if (!SPI_SEND_CMD(Rx_Array, SUSPENDS_PROGRAM_ERASE, 1, 8)) Flash_Error_Handler(Suspend_ERR);
    OFB_SPI_CS_High(0);
}

/* ----------------------------------------------------------------------------
 * Function      : void SST26_Flash_Resume()
 * ----------------------------------------------------------------------------
 * Description   : - Resume continue process (program/erase)
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Flash_Resume() {

    if (!SPI_SEND_CMD(Rx_Array, RESUMES_PROGRAM_ERASE, 1, 8)) Flash_Error_Handler(Resume_ERR);

}


/* ----------------------------------------------------------------------------
 * Function      : void SST26_Page_Program()
 * ----------------------------------------------------------------------------
 * Description   :
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   : Must be call SST26_Write_Enable function
 * ------------------------------------------------------------------------- */

void SST26_Page_Program(uint32_t addr, uint32_t size) {

    uint32_t null_RX_array[size];

    SST26_Write_Enable();
    Sys_Delay_ProgramROM(SystemCoreClock * 0.1);
    //check here if write enabled

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);

    if (!SPI_SEND_CMD(Rx_Array, PAGE_PROGRAM, 1, 8)) Flash_Error_Handler(Page_Program_ERR);
    if (!SPI_SEND_CMD(Rx_Array, addr, 1, 24)) Flash_Error_Handler(Page_Program_ERR);
    if (!SPI_Program_Read(Rx_Array, Tx_Array, size, 8)) Flash_Error_Handler(Page_Program_ERR);


    OFB_SPI_CS_High(0);
}


/* ----------------------------------------------------------------------------
 * Function      : void SST26_Read_Status()
 * ----------------------------------------------------------------------------
 * Description   : Send read configuration status command to Flash Device
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Read_Config_Status() {

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);

    if (!SPI_SEND_CMD(Rx_Array, READ_CONFIGURATION_REGISTER, 2, 8)) Flash_Error_Handler(Read_Config_Status_ERR);

    OFB_SPI_CS_High(0);

}

/* ----------------------------------------------------------------------------
 * Function      : void SST26_Read_Status()
 * ----------------------------------------------------------------------------
 * Description   : Send read status command to Flash Device
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Read_Status() {

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);

    if (!SPI_SEND_CMD(Rx_Array, READ_STATUS_REGISTER, 2, 8)) Flash_Error_Handler(Read_Status_ERR);

    OFB_SPI_CS_High(0);
}

/* ----------------------------------------------------------------------------
 * Function      : void SST26_Read_Memory()
 * ----------------------------------------------------------------------------
 * Description   : - Read Memory
 * Inputs        : - addr           - Address for page of Flash Device
 *                 - size           - Amount of read data from Memory
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Read_Memory(uint32_t addr, uint32_t size) {

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);

    if (!SPI_SEND_CMD(Rx_Array, READ_MEMORY, 1, 8)) Flash_Error_Handler(Read_Memory_ERR);
    if (!SPI_SEND_CMD(Rx_Array, addr, 1, 24)) Flash_Error_Handler(Read_Memory_ERR);
    if (!SPI_Program_Read(Rx_Array, Tx_Array, size, 8)) Flash_Error_Handler(Read_Memory_ERR);

    OFB_SPI_CS_High(0);

}

/* ----------------------------------------------------------------------------
 * Function      : void SST26_Read_JEDEC_ID()
 * ----------------------------------------------------------------------------
 * Description   : - Read JEDEC ID
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Read_JEDEC_ID() {

    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);

    if (!SPI_SEND_CMD(Rx_Array, SPI_READ_JEDEC_ID, 4, 8)) Flash_Error_Handler(Resume_ERR);

    OFB_SPI_CS_High(0);

}

/* ----------------------------------------------------------------------------
 * Function      : void SST26_Read_Serial_Flash_DP()
 * ----------------------------------------------------------------------------
 * Description   :
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Read_Serial_Flash_DP() {

}


/* ----------------------------------------------------------------------------
 * Function      : void SST26_Write_Global_Unlock()
 * ----------------------------------------------------------------------------
 * Description   : Send Global Write Protection Unlock Command
 * Inputs        : - None           - void
 * Outputs       : - Return value   - None (void)
 * Assumptions   :
 * ------------------------------------------------------------------------- */
void SST26_Write_Global_Unlock() {

    SST26_Write_Enable();
    OFB_SPI_CS_High(0);
    Sys_Delay_ProgramROM(SystemCoreClock * CS_DELAY_TIME);
    OFB_SPI_CS_Low(0);

    if (!SPI_SEND_CMD(Rx_Array, GLOBAL_BLOCK_PROTECTION_UNLOCK, 1, 8)) Flash_Error_Handler(Resume_ERR);

    OFB_SPI_CS_High(0);
}


//and you should continue Protection section





