#include<reg51.h>

void T0Delay(void);

void main(void)
{
	unsigned int i;
	unsigned int Duty=0;
	unsigned char up_down=1;
	
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
		
		if(up_down)
		{
			Duty++;
			if(Duty>255)
			{
				up_down=0;
			}
		}
		else
		{
			Duty--;
			if(Duty==0)
			{
				up_down=1;
			}
		}
	}
}

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