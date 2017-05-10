#include<reg51.h>

unsigned int i;
int Duty=0;

void T0Delay()
{
	TMOD=0x02;
	TL0=0xFF;
	TH0=0xFF;
	TR0=1;
	while(TF0==0);
	TR0=0;
	TF0=0;
}

void external0_isr(void) interrupt 0
{
	Duty=Duty+64;
}

void external1_isr(void) interrupt 2
{
	Duty=Duty-64;
}

void main(void)
{
	P0=0;
	P1=0;
	P2=0;
	P3=0x0C;
	
	IT0=1;
	EX0=1;
	IT1=1;
	EX1=1;
	EA=1;
	
	P2=0xFF;
	
	while(1)
	{
		for(i=0;i<256;i++)
		{
			if(i<Duty)
			{
				P2=0xFF;
				T0Delay();
			}
			else
			{
				P2=0x00;
				T0Delay();
			}
		}
		
		if(Duty>255) Duty=255;
		if(Duty<=0) Duty=0;
	}
}