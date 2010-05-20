#include "kbc.h"

/** Returns the data read a the data register.
*
*  Waits for OBF on status register up to KBC_TIMEOUT milliseconds,
*  then reads and returns the data read at the data register. Returns
*  -1 on timeout or transmission error.
*/
static int DEBUG = 0;

int kbc_init(int debug)
{
	DEBUG = debug;
	int mouse_found = 1;
	
	//ler dados penedentes do KBC
	if(DEBUG) printf("- Flush OBF -\n");
	int data;
	do { data = read_kbc(); } while(data != -1);
	
	if(DEBUG) printf("- MouseReset -\n");
	write_aux(MouseReset);
	
	read_kbc();
	read_kbc();
	
	if(read_kbc() == 0xAA) //BAT sucessful; senao, lanca 0xFC
	{
		if(read_kbc() == 0) //DeviceID
		{
			if(DEBUG) printf("- DisableMouse -\n");
			write_kbc_cmd(DisableMouse);
	
			if(DEBUG) printf("- StreamDisable -\n");
			write_aux(StreamDisable);
			
			//escrever parametros do rato
			if(DEBUG) printf("- SampleRate -\n");
			write_aux_arg(SampleRate, 100);
			if(DEBUG) printf("- Resolution -\n");
			write_aux_arg(Resolution, 8);
			if(DEBUG) printf("- Scaling -\n");
			write_aux(Scaling1);
			
			//habilitar rato
			if(DEBUG) printf("- Update Command Byte -\n");
			write_kbc_cmd(ReadCommand);
			write_kbc_cmd_arg(WriteCommand, read_kbc() | INT_1 | INT_12 | EN_KBD | EN_MOUSE);
			
			if(DEBUG) printf("- MouseEnable -\n");
			write_aux(EnableMouse);
			
			if(DEBUG) printf("- StreamEnable -\n");
			write_aux(StreamEnable);
		}
	}
	else mouse_found = 0;
	
	if(DEBUG) printf("- EnableKBD -\n");
	write_kbc_data(EnableKBD);
	
	if(DEBUG) printf("- KBDRate -\n");
	write_kbc_data_arg(KBDRate, 0);
	
	return mouse_found;
}

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

void mouse_disable(void)
{
	write_aux(StreamDisable);
	
	write_kbc_cmd(ReadCommand);
	write_kbc_cmd_arg(WriteCommand, read_kbc() & ~(INT_12 | EN_MOUSE));
	
	write_kbc_cmd(DisableMouse);
	//mask_pic(MOUSE_IRQ);
}


int write_kbc_cmd(unsigned data)
{
	return write_kbc(CMD_REG, data);
}


int write_kbc_cmd_arg(unsigned data, unsigned arg)
{
	if(write_kbc_cmd(data)) return -1;
	return write_kbc_data(arg);
}


int has_DOS_mouse_ISR()
{
	return kbc_init(1);
}


int write_kbc_data(unsigned data)
{
	int i, aux;
	for(i = 0; i < 3; i++)
	{
		write_kbc(DATA_REG, data);
		aux = read_kbc();
		if(aux == ACK || aux == Error/* || aux == -1*/)
			return aux;
		
		delay(1);
	}
	
	return -1;
}


int write_kbc_data_arg(unsigned data, unsigned arg)
{
	int resp = write_kbc_data(data);
	if(resp != ACK) return resp;
	return write_kbc_data(arg);
}


int write_aux(unsigned cmd)
{
	int i, data;
	for(i = 0; i < 3; i++)
	{
		data = write_kbc_cmd_arg(WriteMouse, cmd);
		if(data == ACK || data == Error || data == -1)
			return data;
		
		delay(1);
	}
	
	return -1;
}


int write_aux_arg(unsigned cmd, unsigned arg)
{
	int resp = write_aux(cmd);
	if(resp != ACK) return resp;
	return write_aux(arg);
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


void disable_irq(int irq)
{
	mask_pic(irq);
}

void enable_irq(int irq)
{	
	unmask_pic(irq);
}

