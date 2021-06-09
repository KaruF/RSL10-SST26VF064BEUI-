/*
 * OFB_SPI_SST26V.c
 *
 *  Created on: 14 Nis 2021
 *      Author: m.omerfarukbulut@gmail.com
 */


#include "app.h"

SPI_Selections SPI_CFG;

/* ----------------------------------------------------------------------------
 * Function      : SPI_ERROR_STATE Init_SPI_Flash_Device()
 * ----------------------------------------------------------------------------
 * Description   : Initiliaze Flash Device to traditional SPI
 * Inputs        : - None           - void
 * Outputs       : - Return value   - SPI Error State (OK/ERROR)
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
SPI_ERROR_STATE Init_SPI_Flash_Device() {

    SPI_CFG.number_SPI = 0; //we will use SPI0 for with communication to flash device

    SPI_CFG.Cfg_CTRL0.SPI_Clk_Pol = SPI0_CLK_POLARITY_NORMAL;
    SPI_CFG.Cfg_CTRL0.SPI_Controller = SPI0_CONTROLLER_CM3;
    SPI_CFG.Cfg_CTRL0.SPI_Enable = SPI0_ENABLE;
    SPI_CFG.Cfg_CTRL0.SPI_Mode_Select = SPI0_MODE_SELECT_MANUAL;
    SPI_CFG.Cfg_CTRL0.SPI_Overrun_Int = SPI0_OVERRUN_INT_DISABLE;
    SPI_CFG.Cfg_CTRL0.SPI_Prescale = SPI0_PRESCALE_16;
    SPI_CFG.Cfg_CTRL0.SPI_Slave = SPI0_SELECT_MASTER;
    SPI_CFG.Cfg_CTRL0.SPI_Underrun_Int = SPI0_UNDERRUN_INT_DISABLE;

    SPI_CFG.Cfg_CTRL1.SPI_CS = SPI0_CS_0;
    SPI_CFG.Cfg_CTRL1.SPI_RW_CMD = SPI0_RW_DATA;
    SPI_CFG.Cfg_CTRL1.SPI_Word_Size = SPI0_WORD_SIZE_8;

    SPI_CFG.SPI_DATA_Int_ENABLE = 1;
    SPI_CFG.SPI_DIOs.clk = 12;
    SPI_CFG.SPI_DIOs.cs = 10;
    SPI_CFG.SPI_DIOs.miso = 4;
    SPI_CFG.SPI_DIOs.mosi = 11;

    OFB_SPI_Setup(SPI_CFG);




    return SPI_OK;

}

/* ----------------------------------------------------------------------------
 * Function      : SPI_ERROR_STATE SPI_SEND_CMD()
 * ----------------------------------------------------------------------------
 * Description   : Send SPI Command with that function.
 * Inputs        : - RXdata           - Receive data pointer
 *                 - TXdata           - Transmit data value
 *                 - data_length      - Value of count of send data (8 bit/ 16 bit/ 24 bit/ 32 bit)
 *                 - SPI_bitband      - Select SPI bit band
 * Outputs       : - Return value     - SPI Error State (OK/ERROR)
 * Assumptions   : Init_SPI_Flash_Device function has been call.
 * ------------------------------------------------------------------------- */
SPI_ERROR_STATE SPI_SEND_CMD(uint32_t *RXdata, uint32_t TXdata, uint8_t data_length, uint8_t SPI_bitband) {



    switch (SPI_bitband) {

        case BITBAND_8:
            SPI_CFG.Cfg_CTRL1.SPI_Word_Size = SPI0_WORD_SIZE_8;
            break;

        case BITBAND_16:
            SPI_CFG.Cfg_CTRL1.SPI_Word_Size = SPI0_WORD_SIZE_16;
            break;

        case BITBAND_24:
            SPI_CFG.Cfg_CTRL1.SPI_Word_Size = SPI0_WORD_SIZE_24;
            break;

        case BITBAND_32:
            SPI_CFG.Cfg_CTRL1.SPI_Word_Size = SPI0_WORD_SIZE_32;
            break;
        default:
            return SPI_ERROR;
            break;

    }

    SPI_CFG.Cfg_CTRL1.SPI_RW_CMD = SPI0_RW_DATA;


    for (int i = 0; i < data_length; i++) {
        OFB_SPI_FullDuplex_INT(SPI_CFG, &RXdata[i], &TXdata); //you have to configuration about return value from SPI function
        Sys_Delay_ProgramROM(SystemCoreClock * WRITE_DELAY_TIME);
    }


    return SPI_OK;

}

/* ----------------------------------------------------------------------------
 * Function      : SPI_ERROR_STATE SPI_Program_Read()
 * ----------------------------------------------------------------------------
 * Description   : Send SPI Command with that function.
 * Inputs        : - RXdata           - Receive data array pointer
 *                 - TXdata           - Transmit data value
 *                 - Size             - Size of array
 *                 - SPI_bitband      - Select SPI bit band
 * Outputs       : - Return value     - SPI Error State (OK/ERROR)
 * Assumptions   : Init_SPI_Flash_Device function has been call.
 * ------------------------------------------------------------------------- */
SPI_ERROR_STATE SPI_Program_Read(uint32_t *RXdata, uint32_t *TXdata, uint8_t size, uint8_t SPI_bitband) {



    switch (SPI_bitband) {

        case BITBAND_8:
            SPI_CFG.Cfg_CTRL1.SPI_Word_Size = SPI0_WORD_SIZE_8;
            break;

        case BITBAND_16:
            SPI_CFG.Cfg_CTRL1.SPI_Word_Size = SPI0_WORD_SIZE_16;
            break;

        case BITBAND_24:
            SPI_CFG.Cfg_CTRL1.SPI_Word_Size = SPI0_WORD_SIZE_24;
            break;

        case BITBAND_32:
            SPI_CFG.Cfg_CTRL1.SPI_Word_Size = SPI0_WORD_SIZE_32;
            break;
        default:
            return SPI_ERROR;
            break;

    }

    SPI_CFG.Cfg_CTRL1.SPI_RW_CMD = SPI0_RW_DATA;

    for (int i = 0; i < size; i++) {
        OFB_SPI_FullDuplex_INT(SPI_CFG, &RXdata[i], &TXdata[i]); //you have to configuration about return value from SPI function
        Sys_Delay_ProgramROM(SystemCoreClock * WRITE_DELAY_TIME);
    }



    return SPI_OK;

}










