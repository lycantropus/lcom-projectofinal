#include "rtc.h"

typedef enum {S0, S1, S2, S3} State;
int play = 1;
int timepausenote = 0;
int pause_note=10;
static State current_state = S0;
_go32_dpmi_seginfo old_irqRTC;
_go32_dpmi_seginfo new_irqRTC;

volatile unsigned long int rtc_periodic = 0;   
volatile unsigned long int rtc_update = 0;
volatile unsigned long int rtc_alarm = 0;
volatile unsigned long int rtc_ints = 0;
volatile unsigned long int timestopnote = 0;
/** Tamanho de uma string com horas xx:xx:xx. */
#define SIZEOF_TIME_STR 9

static Byte stat_b; /** Guarda o estado antigo do Stat B. */

static Byte stat_a; /** Guarda o estado antigo do Stat a. */
void rtc_intc(void) 
{
	Byte cause = read_rtc(RTC_STAT_C);
	rtc_ints++;
	
	if(cause & RTC_UF) //interrupcao de update
    {
		rtc_update++;
    }
	if(cause & RTC_AF)//interrupcao de alarme
	{
		rtc_alarm++;
    }
	if(cause & RTC_PF)//interrupcao periodica
	{
		rtc_periodic++;
	
		switch (current_state)
		{
			case S0:
			{
				if (play == 1)
				{
					current_state = S1;
					break;
				}
			}
			case S1:
			{
				if (play == 1)
				{
					if ( !isEmptyGQueue(NotesQueue) )
					{
						static Note * nota;
						nota= (Note *) getGQueue(NotesQueue);
						timestopnote=(nota->dur)+(rtc_periodic);
						timepausenote=timestopnote+pause_note;
						play_noteRTC(nota);
						current_state = S2;
					}
					else
					{
						LoadSong();
						current_state = S1;
						play=1;
					}
				}
				else
				{
					current_state = S0;
				}
				break;
			}
			case S2:
			{
				if (play==1)
				{
					if (rtc_periodic >= timestopnote)
					{
						stop_noteRTC();
						current_state = S3;
					}
				}
				else
				{
					stop_noteRTC();
					current_state = S0;
				}
				break;
			}
			case S3:
			{
			if (play==1)
				{
					current_state = S1;
				}
				else
				{
					current_state = S0;
				}	
				break;
			}
		}
	}
	outportb(PIC1_CMD, EOI);
	outportb(PIC2_CMD, EOI);
}


/** converts BCD (Binary Coded Decimal) to decimal
 */
Byte bcd2dec(Byte i)
{
	return((((i)>>4)*10) + (i & 0x0F));
}


/** converts decimal to BCD (Binary Coded Decimal)
 */
Byte dec2bcd(Byte i)
{
	if (i < 10)
		return i;
	else
		return ((i/10) << 4) + (i-(i/10)*10);


//	return(((i / 10)<<4) | (i % 10));
}

/** Wait until data in rtc is valid.
 * Data is valid until +/- 240 usec after this function returns,
 * thus a read/write can be done to the RTC within this time period
 */
void rtc_valid()
{
	int ints_en = disable(); // globally disable interrupts
	outportb(RTC_ADDR_REG, RTC_STAT_A); // read STAT_A
	
	// wait if Update In Progress (UIP)
	while (inportb(RTC_DATA_REG) & RTC_UIP)
	; // data is invalid
	
	if (ints_en)
		enable(); // re-enable interrupts globally
}

/** Returns rtc data from I/O address add. Doesn't check valid bit
 */
Byte read_rtc(Byte add)
{
	int ints_en = disable(); // globally disable interrupts

	outportb(RTC_ADDR_REG, add);
	const Byte ret = inportb(RTC_DATA_REG);

	if (ints_en)
		enable(); // re-enable interrupts globally

	return(ret);
}



/** Returns rtc data from I/O address add. Check valid bit
 */
Byte read_rtcv(Byte add)
{
	rtc_valid();
	return read_rtc(add);
}

/** Write value to I/O address add. Doesn't check valid bit
 */
void write_rtc(Byte add, Byte value)
{
	int ints_en = disable(); // globally disable interrupts

	outportb(RTC_ADDR_REG, add);
	outportb(RTC_DATA_REG, value);

	if (ints_en)
		enable(); // re-enable interrupts globally
}


/** Write value to I/O address add. Check valid bit
 */
void write_rtcv(Byte add, Byte value)
{
	rtc_valid();
	write_rtc(add, value);
}

/** Read RTC stored time
 *
 * Uses read_rtcv() and bcd2dec()
 */
void rtc_read_time(RTC_TIME * atime)
{
	atime->hour = bcd2dec(read_rtcv(HOUR));
	atime->min = bcd2dec(read_rtcv(MIN));
	atime->sec = bcd2dec(read_rtcv(SEC));
}

/** Read RTC stored date
 *
 * Uses read_rtcv() and bcd2dec()
 */
void rtc_read_date(RTC_DATE *adate)
{
	adate->day = bcd2dec(read_rtcv(MONTH_DAY));
	adate->month = bcd2dec(read_rtcv(MONTH));
	adate->year = bcd2dec(read_rtcv(YEAR));
}

/** Read RTC stored alarm
 *
 * Uses read_rtcv() and bcd2dec()
 */
void rtc_read_alarm(RTC_TIME *alarmtime)
{
	alarmtime->hour = bcd2dec(read_rtcv(HOUR_ALARM));
	alarmtime->min = bcd2dec(read_rtcv(MIN_ALARM));
	alarmtime->sec = bcd2dec(read_rtcv(SEC_ALARM));
}

/** Write alarm to RTC
 *
 * Uses write_rtcv() and dec2bcd()
 */
void rtc_write_alarm(RTC_TIME *alarmtime)
{
	write_rtcv(SEC_ALARM, dec2bcd(alarmtime->sec));
	write_rtcv(MIN_ALARM, dec2bcd(alarmtime->min));
	write_rtcv(HOUR_ALARM, dec2bcd(alarmtime->hour));
}

/** begin RTC
 *
 *
 */
void rtcBegin(void)
{
	stat_b = read_rtcv(RTC_STAT_B); // guardar o valor do antigo stat b
	stat_a = read_rtcv(RTC_STAT_A); //guardar o valor do antigo stat a
	// activar os 3 tipos de interrupcäes
	write_rtc(RTC_STAT_B, stat_b | RTC_PIE | RTC_UIE | RTC_AIE);
	
	// activar a interrupçao	
	install_c_irq_handler(RTC_IRQ, rtc_intc, &old_irqRTC, &new_irqRTC);
	
	unmask_pic(RTC_IRQ);
}
/** End RTC
 *
 *
 */
void rtcEnd(void)
{
	// restaurar antigo stat b
	write_rtcv(RTC_STAT_B, stat_b);
	//reinstalar o antigo handler
	reinstall_c_irq_handler(RTC_IRQ, &old_irqRTC, &new_irqRTC);

}
//constroi a string da hora passada por parametro
char* timeRTC2STR(RTC_TIME* atime)
{
	char* ret = (char*)malloc(SIZEOF_TIME_STR*sizeof(char));

	// construir a string com zeros intermedios
	sprintf(ret, "%s%d:%s%d:%s%d", atime->hour < 10 ? "0" : "", 
	atime->hour, atime->min < 10 ? "0" : "", atime->min,
			atime->sec < 10 ? "0" : "", atime->sec);

	return(ret);
}
//imprime as hora corrente no ecra
void printf_time(RTC_TIME* atime)
{
	printf("current time: %s", timeRTC2STR( atime));
}
//constroi a string da data passada por parametro
char* dateRTC2STR(RTC_DATE *adate)
{
	char* ret = (char*)malloc(SIZEOF_TIME_STR*sizeof(char));

	// construir a string com zeros intermedios
	sprintf(ret, "%s%d-%s%d-20%s%d", adate->day < 10 ? "0" : "", 
			adate->day, adate->month < 10 ? "0" : "", adate->month,
			adate->month < 10 ? "0" : "",adate->year);

	return(ret);
}

//imprimr a data corrente no ecra
void printf_date(RTC_DATE *adate)
{
	printf("current date: %s",dateRTC2STR( adate));
}

//dependendo do modo escreve o alarm corrente ou o set alarm (so muda a frase pois o valor do alarm passa por argumento) 
void printf_alarm(RTC_TIME *aalarm, int mode)
{
	if (mode==0)
		printf("current alarm: %s", timeRTC2STR( aalarm));
	else
		printf("set alarm: %s", timeRTC2STR( aalarm));
}

void print_Bin(Byte hx)
{
	int i;
	for (i=7; i>=0; i--)
	{
		if (hx & (0x1 << i))
			printf("1");
		else
			printf("0");
	}
}

void LoadSong()
{
	static Note notes[] ={{Las3, 300*2}, {Fa4, 300*2}, {Res4, 300*2}, {Fa4, 300*2}, {Sols4, 300*2}, {Fa4, 300*2},
					{0, 200*2}, {Las3, 300*2}, {Fa4, 300*2}, {Res4, 300*2}, {Fa4, 300*2}, {Las5, 300*2}, {Fa4, 300*2},
					{0, 200*2}, {Dos5, 300*2}, {Do5, 300*2}, {Las4, 300*2},
					{Sols4, 300*2}, {Las4, 300*2}, {Fa4, 300*2},
					{0, 200*2}, {Dos5, 300*2}, {Do5, 300*2}, {Las4, 300*2},
					{Sols4, 300*2}, {Do5, 300*2}, {Fa4, 300*2},
					{0, 200*2}, {Las3, 300*2}, {Fa4, 300*2}, {Res4, 300*2}, {Fa4, 300*2}, {Sols4, 300*2}, {Fa4, 300*2},
					{0, 200*2}, {Las3, 300*2}, {Fa4, 300*2}, {Res4, 300*2}, {Fa4, 300*2}, {Las5, 300*2}, {Fa4, 300*2},
					{0, 200*2}, {Dos5, 300*2}, {Do5, 300*2}, {Las4, 300*2},
					{Sols4, 300*2}, {Las4, 300*2}, {Fa4, 300*2},
					{0, 200*2}, {Dos5, 300*2}, {Do5, 300*2}, {Las4, 300*2},
					{Sols4, 300*2}, {Do5, 300*2}, {Fa4, 300*2},
					{0, 200*2}}; 
	NotesQueue = (GQueue*)newGQueue(30, sizeof(Note));
	int SongSize=(sizeof(notes)/sizeof(Note));
	int i;
	for (i=0; i<SongSize; i++)
	{
		putGQueue(NotesQueue, &notes[i]);
	}
	

}
/** @} end of RealTimeController */
