/*
 * OS.h
 *
 * Created: 12/10/2019 01:54:22 a. m.
 *  Author: Lalo
 */ 


#ifndef OS_H_
#define OS_H_

#include <msp430f169.h>
#include <intrinsics.h>
#include <stdint.h>
#include <stdarg.h>
#include "Watchdog.h"
#include "TimerB.h"
#include "GPIO.h"

#define NUMTHREADS  (3)        // maximum number of threads
#define STACKSIZE   (0x100)      // number of 8-bit words in stack per thread

struct TCB{ //Thread control block
	int16_t *sp;       // pointer to stack (valid for threads not running)
	struct TCB *next;  // linked-list pointer
	int8_t *blockedPointer;
	int8_t  blockedValue;
};
typedef struct TCB TCB_TypeDef;

typedef struct
{
    uint32_t data;
    int8_t   semaphore;
    uint8_t  lost  ;
}OS_nMailBox;

typedef enum
{
	OS_enOK  =0,
	OS_enERROR,
}OS_nStatus;

typedef enum
{
    OS_enUnblocked  =0,
}OS_nBlocked;


void OS__vLaunch(void);

/*Threads*/
OS_nStatus OS__enAddMainThreads(int8_t s8Cant,...);
/*,
void(*vTask2)(void),
void(*vTask3)(void));
*/
OS_nStatus OS__enAddPeriodicThreads(int8_t s8Cant,...);

typedef enum
{
	SEMAPHORE_enInitSYNC =0, /* 0 means event not occurs, 1 event occurs*/
	SEMAPHORE_enInitMUTEX=1, /* 1 means free, 0 busy*/
}SEMAPHORE_nTypeInit;

/*SpinLock Semaphore (MUTEX MUTual EXclusion)*/
void OS__vInitSemaphore(int8_t *ps8Semaphore, SEMAPHORE_nTypeInit enInitValue);
void OS__vWaitSemaphore(int8_t *ps8Semaphore);
void OS__vSignalSemaphore(int8_t *ps8Semaphore);

/* MailBox*/
void OS__vInitMailBox(OS_nMailBox* enMailBox);
void OS__vSendMailBox(OS_nMailBox* enMailBox,uint32_t u32Data);
uint32_t OS__u32ReadMailBox(OS_nMailBox* enMailBox);


/*Critical Sections*/
uint16_t OS__u16StartCriticalSection(void);
void OS__vEndCriticalSection(uint16_t u16Status);


void OS__vSuspendMainThead(void);


#endif /* OS_H_ */
