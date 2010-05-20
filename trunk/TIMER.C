#include "timer.h"
#include <stdio.h>

/** Program timer (0,1,2) with mode
 */
void timer_init(int timer, int mode)
{
	if( timer < 0 || timer > 2 )
		return;
	
	//printf("Timer %d (0x%x) is now in mode 0x%x!\n", timer, TIMER_0 + timer, mode);
	
	mode |= timer << 6;
	outportb(TIMER_CTRL, mode);	
}

void timer_get(int timer, int* value)
{
	int mode = (timer << 6) | LCOM_MODE;
	outportb(TIMER_CTRL, mode);
	
	int value_lsb = inportb(TIMER_0 + timer);
	int value_msb = inportb(TIMER_0 + timer);
	
	if( value )
		*value = (value_msb << 8) | value_lsb;		
}

/** Load timer (0,1,2) with value
 */
void timer_load(int timer, int value)
{
	if( timer < 0 || timer > 2 )
		return;
	
	//printf("Timer %d (0x%x): LSB = %d; MSB = %d; Value = %d \n", timer, timer + TIMER_0, LSB(value), MSB(value), value);
	
	timer = TIMER_0 + timer;
	
	outportb(timer, LSB(value));
	outportb(timer, MSB(value));	
}

/** Wait mili miliseconds, indirectly counting T0 interrupts
*/
void mili_sleep(int mili)
{
	int endtime = contador_mili + mili;
	while(contador_mili <= endtime) { }
}

/** wait secs seconds, indirectly counting T0 interrupts
 */
void sec_sleep(int secs)
{
	mili_sleep(secs * 1000);
}
