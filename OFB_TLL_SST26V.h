/*
 * OFB_LL_S25HS512T.h
 *
 *  Created on: 14 Nis 2021
 *      Author:  m.omerfarukbulut@gmail.com
 *
 *      *OFB= OMER FARUK BULUT
 *      *TLL=TRANSACTION LOW LAYER
 *      *ST26V=DEVICE CODE
 */

#ifndef INCLUDE_OFB_TLL_SST26V_H_
#define INCLUDE_OFB_TLL_SST26V_H_

////////MACROS ABOUT TRANSACTIONS Commands////////


//Configuration
#define NOP                     0x00
#define RSTEN                   0x66
#define RST                     0x99
#define EQIO                    0x38
#define RSTQIO                  0xFF
#define RDSR                    0x05
#define WRSR                    0x01
#define RDCR                    0x35

//Read
#define READ                    0x03
#define HIGH_SPEED_READ         0x0B
#define SQOR                    0x6B
#define SQIOR                   0xEB
#define SDIOR                   0x3B
#define SB                      0xBB
#define RBSQI                   0xC0
#define RBSPI                   0xEC

//Identification
#define JEDEC_ID                0x9F
#define QUAD__J_ID              0xAF
#define SFDP                    0x5A

//Write
#define WREN                    0x06
#define WRDI                    0x04
#define SE                      0x20
#define BE                      0xD8
#define CE                      0xC7
#define PP                      0x02
#define SPI_QUAD_PP             0x32
#define WRSU                    0xB0
#define WRRE                    0x30

//Protection
#define RBPR                    0x72
#define WBPR                    0x42
#define LBPR                    0x8D
#define nVWLDR                  0xE8
#define ULBPR                   0x98
#define RSID                    0x88
#define PSID                    0xA5
#define LSID                    0x85




#endif /* INCLUDE_OFB_TLL_SST26V_H_ */
