/*
 *  OFB_SST26V.h
 *
 *  Created on: 6 Nis 2021
 *      Author: m.omerfarukbulut@gmail.com
 *
 *
 *
 *
 */


#ifndef INCLUDE_OFB_SST26V_H_
#define INCLUDE_OFB_SST26V_H_

#include <OFB_TLL_SST26V.h>

///Transmit and Receive Arrays

#define RX_SIZE         255
#define TX_SIZE         255

uint32_t Rx_Array[RX_SIZE];
uint32_t Tx_Array[TX_SIZE];

//////////////Transactions//////////////

//Configuration Commands
#define NO_OPERATION                                               NOP
#define RESET_ENABLE                                               RSTEN
#define RESET_MEMORY                                               RST
#define ENABLE_QUAD_IO                                             EQIO
#define RESET_QUAD_IO                                              RSTQIO
#define READ_STATUS_REGISTER                                       RDSR
#define WRITE_STATUS_REGISTER                                      WRSR
#define READ_CONFIGURATION_REGISTER                                RDCR

//Read Commands
#define READ_MEMORY                                                READ
#define READ_MEMORY_HIGH_SPEED                                     HIGH_SPEED_READ
#define SPI_QUAD_OUTPUT_READ                                       SQOR
#define SPI_QUAD_IO_READ                                           SQIOR
#define SPI_DUAL_IO_READ                                           SDIOR
#define SET_BURST_LENGTH                                           SB
#define SQI_READ_BURST_WRAP                                        RBSQI
#define SPI_READ_BURST_WRAP                                        RBSPI

//Identification Commands
#define SPI_READ_JEDEC_ID                                          JEDEC_ID
#define SQI_READ_JEDEC_ID                                          QUAD__J_ID
#define SERIAL_FLASH_DP                                            SFDP

//Write Commands
#define WRITE_ENABLE                                               WREN
#define WRITE_DISABLE                                              WRDI
#define ERASE_4KBYTES_MEMORY                                       SE
#define ERASE_XKBYTES_MEMORY                                       BE
#define ERASE_FULL_MEMORY                                          CE
#define PAGE_PROGRAM                                               PP
#define SQI_QUAD_PAGE_PROGRAM                                      SPI_QUAD_PP
#define SUSPENDS_PROGRAM_ERASE                                     WRSU
#define RESUMES_PROGRAM_ERASE                                      WRRE

//Protection Commands
#define READ_BLOCK_PROTECT_REG                                     RBPR
#define WRITE_BLOCK_PROTECT_REG                                    WBPR
#define LOCK_DOWN_BLOCK_PROTECT_REG                                LBPR
#define NON_VOLATILE_WRITE_LOCKDOWN_REG                            nVWLDR
#define GLOBAL_BLOCK_PROTECTION_UNLOCK                             ULBPR
#define READ_SECURITY_ID                                           RSID
#define PROGRAM_USER_SECURITY_ID_AREA                              PSID
#define LOCKOUT_SECURITY_ID_PROGRAM                                LSID


////////////Macross////////////


//Scope Of Erase

#define Erase_Sector                                                0
#define Erase_Blocks                                                1
#define Erase_Chip                                                  2

//Delay for Chip Select
#define CS_DELAY_TIME                                               0.000001
#define WRITE_DELAY_TIME                                            0.0016


////////////Enums and Structs////////////


enum SST26_SPI_BitBand {
    BITBAND_8 = 8, BITBAND_16 = 16, BITBAND_24 = 24, BITBAND_32 = 32,

};

typedef enum SPI_Error_State {

    SPI_ERROR, SPI_OK,

} SPI_ERROR_STATE;


typedef enum SPI_Error_Msg_Type {

    Init_Flash_ERR, NO_Operation_ERR, Reset_Enable_ERR, Reset_Memory_ERR, Reset_Quad_IO_ERR, ERASE_Process_Select_ERR, ERASE_Full_Memory_ERR, ERASE_Sector_ERR, ERASE_Sector_Addr_ERR, ERASE_Block_ERR, ERASE_Block_Addr_ERR, Suspend_ERR, Resume_ERR, Write_Enable_ERR, Write_Disable_ERR, Page_Program_ERR, Read_Config_Status_ERR, Read_Status_ERR, Read_Memory_ERR, Write_Config_ERR

} SPI_ERROR_MSG_TYPE;


////////////DECLARATIONS OF FUNCTIONS////////////

void SST26_Init_Flash_Device();
void SST26_Reset();
void SST26_Write_Disable();
void SST26_Write_Enable();
void SST26_Write_Config_Reg(uint8_t conf_data);
void SST26_Erase_Flash(uint8_t Scope_Erase, uint32_t Erase_addr);
void SST26_Flash_Suspend();
void SST26_Flash_Resume();
void SST26_Page_Program(uint32_t addr, uint32_t size);
void SST26_Read_Config_Status();
void SST26_Read_Status();
void SST26_Read_Memory(uint32_t addr, uint32_t size);
void SST26_Read_JEDEC_ID();
void SST26_Read_Serial_Flash_DP();
void SST26_Write_Global_Unlock();

SPI_ERROR_STATE Init_SPI_Flash_Device();
SPI_ERROR_STATE SPI_SEND_CMD(uint32_t *RXdata, uint32_t TXdata, uint8_t data_length, uint8_t SPI_bitband);
SPI_ERROR_STATE SPI_Program_Read(uint32_t *RXdata, uint32_t *TXdata, uint8_t size, uint8_t SPI_bitband);




#endif /* INCLUDE_OFB_SST26V_H_ */
