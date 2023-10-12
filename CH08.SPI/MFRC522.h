#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////
//  MFRC522 DATA FORMAT CONSTANT
/////////////////////////////////////////////////////////////////////
#define PCD_IDLE              0x00
#define PCD_AUTHENT           0x0E
#define PCD_RESETPHASE        0x0F
#define PCD_TRANSCEIVE        0x0C
#define PCD_CALCCRC           0x03

#define CommandReg            0x01 
#define ModeReg               0x11
#define TxModeReg             0x12
#define RxModeReg             0x13
#define TxControlReg          0x14
#define TxAutoReg             0x15

#define TModeReg              0x2A
#define TPrescalerReg         0x2B
#define TReloadRegH           0x2C
#define TReloadRegL           0x2D

#define Status1Reg            0x07    
#define Status2Reg            0x08  
#define BitFramingReg         0x0D

#define CommandReg            0x01  
#define ComIEnReg             0x02   
#define ComIrqReg             0x04

#define ErrorReg              0x06 
#define FIFOLevelReg          0x0A
#define FIFODataReg           0x09
#define ControlReg            0x0C
#define CollReg               0x0E

              
#define PICC_ANTICOLL1        0x93 
#define PICC_WRITE            0xA0 
#define PICC_READ             0x30 
#define PICC_RESTORE          0xC2 
#define PICC_TRANSFER         0xB0 
#define PICC_HALT             0x50 
#define PICC_REQALL           0x52 
#define PICC_AUTHENT1A        0x60               

#define CommandReg            0x01 
#define DivIrqReg             0x05

#define CRCResultRegM         0x21
#define CRCResultRegL         0x22


/////////////////////////////////////////////////////////////////////
//  MFRC522 CONSTANT
/////////////////////////////////////////////////////////////////////
#define MI_OK               	0
#define MI_NOTAGERR         	1
#define MI_ERR              	2
#define MAXRLEN 	   			18
#define RST                 	16 
#define channel             	0
#define speed         			1000000

/////////////////////////////////////////////////////////////////////
// Function
/////////////////////////////////////////////////////////////////////
char PcdReset(void);
void PcdAntennaOn(void);
void PcdAntennaOff(void);
char PcdRequest(unsigned char req_code,unsigned char *pTagType);   
char PcdAnticoll(unsigned char *pSnr);
char PcdSelect(unsigned char *pSnr);         
char PcdAuthState(unsigned char auth_mode,unsigned char addr,unsigned char *pKey,unsigned char *pSnr);     
char PcdRead(unsigned char addr,unsigned char *pData);     
char PcdWrite(unsigned char addr,unsigned char *pData);    
char PcdValue(unsigned char dd_mode,unsigned char addr,unsigned char *pValue);   
char PcdBakValue(unsigned char sourceaddr, unsigned char goaladdr);                                 
char PcdHalt(void);
char PcdComMF522(unsigned char Command, unsigned char *pInData, unsigned char InLenByte, unsigned char *pOutData, unsigned int  *pOutLenBit);
void CalulateCRC(unsigned char *pIndata,unsigned char len,unsigned char *pOutData);
void WriteRawRC(unsigned char Address,unsigned char value);
unsigned char ReadRawRC(unsigned char Address); 
void SetBitMask(unsigned char reg,unsigned char mask); 
void ClearBitMask(unsigned char reg,unsigned char mask); 
