/**************************************************************************
 *This header file includes the method definitions and default values to be
 *used in the implementation od the count down
 *by Jitendra Selvam
 *************************************************************************/
#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef PROCESS_RING_
#define PROCESS_RING_
#define NPROCS 2
#define NROUNDS 3
#include<xinu.h>

extern volatile int arr[64];
extern volatile int flag;

sid32 semexit;
sid32 sem[64];

extern process poll(int32, int32, int32);
extern void sync(int32,int32,int32);

#endif
