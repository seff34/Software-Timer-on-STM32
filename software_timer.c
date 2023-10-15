/*
 * software_timer.c
 *
 *  Created on: Oct 14, 2023
 *  Author: Sefa Eren AKDOĞAN
 */
#include "software_timer.h"

static char runTimeString[20] ;
static int timerCount = 0 ;
static sw_timer_t* timerArrays[SW_TIMER_LIMIT];

extern uint32_t uwTick;
extern uint32_t uwTickFreq;

sw_timer_t* swTimer_init(const uint32_t target,const bool type,void(*callback)(void))
{
	if ( timerCount == SW_TIMER_LIMIT )
		return NULL;

	sw_timer_t* newTimer = (sw_timer_t*)malloc(sizeof(sw_timer_t));
	if ( newTimer == NULL )
		return NULL;
	newTimer->counter  = 0;
	newTimer->target   = target;
	newTimer->status   = SW_TIMER_STOP;
	newTimer->type     = type;
	newTimer->callback = callback;
	timerArrays[timerCount++] = newTimer;
	return newTimer;
}

bool swTimer_status(sw_timer_t* swTimer)
{
	if ( swTimer == NULL )
		return SW_TIMER_STOP;
	return swTimer->status;
}

void swTimer_start(sw_timer_t* swTimer)
{
	if ( swTimer == NULL )
		return;
	swTimer->status = SW_TIMER_START;
}

void swTimer_stop(sw_timer_t* swTimer)
{
	if ( swTimer == NULL )
		return;
	swTimer->status = SW_TIMER_STOP;
}

void swTimer_reset(sw_timer_t* swTimer)
{
	if ( swTimer == NULL )
		return;
	swTimer->counter = 0;
}

void swTimer_restart(sw_timer_t* swTimer)
{
	if ( swTimer == NULL )
		return;
	swTimer_reset(swTimer);
	swTimer_start(swTimer);
}

uint32_t swTimer_setTargetValue(sw_timer_t* swTimer,uint32_t newTarget)
{
	if ( swTimer == NULL )
		return 0;
	uint32_t oldValue = swTimer->target;
	swTimer->target = newTarget;
	return oldValue;
}

uint32_t swTimer_getTargetValue(const sw_timer_t* swTimer)
{
	if ( swTimer == NULL )
		return 0;
	return swTimer->target;
}

#ifdef USE_SYSTICK_TIMER
	static
#endif
void swTimer_proses(sw_timer_t* swTimer)
{
	if ( swTimer->status == SW_TIMER_START ){
		if( ++swTimer->counter >= swTimer->target ){
			swTimer_reset(swTimer);
			if ( swTimer->type == SW_TIMER_ONESHOT)
				swTimer->status = SW_TIMER_STOP;
			if ( swTimer->callback != NULL )
				swTimer->callback();
		}
	}
}

void swTimer_delay(const uint32_t delay)
{
	uint32_t start = uwTick;
	while ( uwTick <= (start + delay));
}

bool swTimer_waitFlag(const uint32_t delay,bool* flag)
{
	if ( flag == NULL )
		return false;
	*flag = false;
	uint32_t start = uwTick;
	while ( uwTick <= (start + delay)){
		if ( *flag ){
			return true;
		}
	}
	return false;
}

bool swTimer_waitDoubleFlag(const uint32_t delay,bool* flag1,bool* flag2)
{
	if ( flag1 == NULL || flag2 == NULL )
		return false;
	*flag1 = false;
	*flag2 = false;
	uint32_t start = uwTick;
	while ( uwTick <= (start + delay)){
		if ( *flag1 || *flag2){
			return true;
		}
	}
	return false;
}

uint32_t getRunTimeSec()
{
	return (uwTick/1000);
}

uint32_t getRunTimeMsec()
{
	return (uwTick%1000);
}

const char* getRunTimeStr()
{
	sprintf(runTimeString,"[%ld:%03ld]",getRunTimeSec(),getRunTimeMsec());
	return runTimeString;
}

#ifdef USE_SYSTICK_TIMER
void HAL_IncTick(void)
{
	uwTick += uwTickFreq;
	for ( int i = 0 ; i < timerCount ; ++i)
		swTimer_proses(timerArrays[i]);
}
#endif

