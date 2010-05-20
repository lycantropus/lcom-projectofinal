#include "kbc.h"

/** Returns the data read a the data register.
*
*  Waits for OBF on status register up to KBC_TIMEOUT milliseconds,
*  then reads and returns the data read at the data register. Returns
*  -1 on timeout or transmission error.
*/
int read_kbc(void)
{
	int milis_begin = contador_mili;
	char stat;
	int data;
	while((contador_mili - milis_begin) < KBC_TIMEOUT) 
	{  
		stat = inportb(STAT_REG);  /* loop until 8042 output buffer full */  
		if((stat & OBF) != 0) 
		{  
			data = inportb(DATA_REG);  /* or parity error or receive timeout */  
			if((stat & (PAR_ERR | TO_ERR)) == 0)  
				return data;  
			else  
				return -1;  
		}
		delay(1); 
	} 
	return -1;
}

/** Write 'data' at IO address 'adr' , returning -1 on error or timeout.
 *
 * Waits for IBF on status register , than writes data to 'adr',
 * return -1 on timeout.
 */
int write_kbc(unsigned adr, unsigned data)
{
	int milis_begin = contador_mili;
	char stat;
	while((contador_mili - milis_begin) < KBC_TIMEOUT) 
	{	
		stat = inportb(STAT_REG);  /* loop until 8042 input buffer empty */  
		if((stat & IBF) == 0) 
		{  
			outportb(adr, data); /* argumentos da função */  
			return 0;  
		} 
		delay(1);
	} // terminou o tempo 
	
	return -1;
}

/** Write 'data' to the data register, returning ACK, Error or -1 on timeout.
 *
 * If a Resend reply is received from the KBC, it retries up to 3 times to
 * write the data.
 *
 * Uses write_kbc() and read_kbc()
 */
int write_kbc_data(unsigned data)
{
	int tries = 3;
	int value;
	do
	{
		//testa timeout
		if (write_kbc(DATA_REG, data) == -1)
		{
			return -1;
		}
		
		value = read_kbc();
		
		if (value == Resend)
		{
			tries--;
		}
		else	return value;
	}
	while (tries > 0);
	
	return value;
}

void disable_irq(int irq)
{
	mask_pic(irq);
}

void enable_irq(int irq)
{	
	unmask_pic(irq);
}
