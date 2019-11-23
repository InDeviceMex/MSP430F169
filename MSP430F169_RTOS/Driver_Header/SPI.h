/*
 * SPI.h
 *
 * Created: 16/10/2019 08:31:58 p. m.
 *  Author: Lalo
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <msp430f169.h>
#include <stdint.h>
#include <intrinsics.h>
#include <OS.h>

#define SPI_FIFOSIZE (64u)

typedef struct
{
    uint8_t* put;
    uint8_t* get;
    int8_t   counter;
    int8_t   init;
    uint8_t  buffer[SPI_FIFOSIZE];
}SPI_FIFO_TypeDef;



typedef enum
{
	SPI_enModeSlave   =0,
	SPI_enModeMaster  =1,
}SPI_nMode;

typedef enum
{
	SPI_enMSBFirst   =0,
	SPI_enLSBFirst  =1,
}SPI_nDataOrder;

typedef enum
{
	SPI_enClockIdleLow   =0,
	SPI_enClockIdleHigh=1,
}SPI_nClockPolarity;

typedef enum
{
	SPI_enClockSampleFirst   =0,
	SPI_enClockSampleLast=1,
}SPI_nClockPhase;

typedef enum
{
	SPI_enClockDiv4   =0,
	SPI_enClockDiv16  =1,
	SPI_enClockDiv64  =2,
	SPI_enClockDiv128 =3,
	SPI_enClockDiv2   =4,
	SPI_enClockDiv8   =5,
	SPI_enClockDiv32  =6,
	SPI_enClockDiv64_1,
}SPI_nClock;

typedef enum
{
	SPI_enPinSS    =1,
	SPI_enPinMISO  =2,
	SPI_enPinMOSI  =4,
	SPI_enPinCLK   =8,
}SPI_nPin;


void SPI__vInitFifo(SPI_FIFO_TypeDef* sFifo);

void SPI__vInit(SPI_nMode enMode,SPI_nDataOrder enDataOrder,SPI_nClockPolarity enPolarity, SPI_nClockPhase enPhase, SPI_nClock enClockSource );
void SPI__vDeInit(void);

void SPI__vInitPin(SPI_nPin enPin);
void SPI__vDeInitPin(SPI_nPin enPin);

void SPI__vEnableInterrupt(void);
void SPI__vDisableInterrupt(void);

void SPI__vSendReceiveDataMaster(uint8_t* pu8DataOut, uint8_t* pu8DataIn, int16_t s16DataNumber,volatile uint8_t* pu8Port, uint8_t u8Pin  );
void SPI__vSendDataMaster(uint8_t* pu8DataOut,int16_t s16DataNumber,volatile uint8_t* pu8Port, uint8_t u8Pin  );
void SPI__vReceiveDataMaster(uint8_t* pu8DataIn,int16_t s16DataNumber ,volatile uint8_t* pu8Port, uint8_t u8Pin );



#endif /* SPI_H_ */
