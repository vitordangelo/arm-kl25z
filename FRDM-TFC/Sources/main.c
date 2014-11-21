#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"
#include "ServoCtrl.h"

float media = 64.0;
uint32_t a,b,med;
float spd = 10000.0;
float cogfinal = 0.0;
float x=0.0,y=0.0;


  int main(void) {	
	uint32_t t, i = 0, a = 0, b = 0,limiar = 0xFE0;	
	uint8_t transmissao=0; 
	float dInput[2];
	float dServoAngle=0.0;
	TFC_Init();

	TFC_HBRIDGE_ENABLE;	
	
	for (;;) 
	{
		if (LineScanImageReady == 1) 
		{
			a = 0;
			b = 127;
			while (LineScanImage0[a] <= limiar || LineScanImage0[b] <= limiar) 
			{
				if (LineScanImage0[a] <= limiar) 
				{
					a++;
				}
				if (LineScanImage0[b] <= limiar) 
				{
					b--;
				}
			}
			if ((b - a) <=0) 
			{
				media = media;
			}
			else 
			{
				media = (float) (a + b) / 2;
			}
		}

		//Demo Mode 3 will be in Freescale Garage Mode.  It will beam data from the Camera to the 
		//Labview Application

		if (TFC_Ticker[0] > 100 && LineScanImageReady == 1) 
		{
			TFC_Ticker[0] = 0;
			LineScanImageReady = 0;
			TERMINAL_PRINTF("\r\n");
			TERMINAL_PRINTF("L:");

			if (t == 0)
				t = 3;
			else
				t--;

			TFC_SetBatteryLED_Level(t);

			for (i = 0; i < 128; i++) 
			{	
				TERMINAL_PRINTF("%d,", LineScanImage0[i]/16);
			}

/*			for (i = 0; i < 128; i++) 
			{
				TERMINAL_PRINTF("%X", LineScanImage1[i]);
				if (i == 127)
					TERMINAL_PRINTF("\r\n", LineScanImage1[i]);
				else
					TERMINAL_PRINTF(",", LineScanImage1[i]);
			}*/
		}

		//TFC_Task must be called in your main loop.  This keeps certain processing happy (I.E. Serial port queue check)
		TFC_Task(); 		
		dInput[0]= 10000.0;
		dInput[1]= media;
	
		dServoAngle = ServoCtrl_defuzzification(dInput[0],dInput[1]);
		x = ((dServoAngle * 1.0 )/ 500.0) - 3.0;
		TFC_SetServo(0, x);
		if (dServoAngle > 1550) 
		{
			TFC_HBRIDGE_ENABLE;
			//	TFC_SetMotorPWM(0.7,(-1/20.0)*media + 5.0);
			TFC_SetMotorPWM(0.6,0.3);
								

		}
		else if (dServoAngle < 1450) 
		{
		//	TFC_SetMotorPWM((1/20.0)*media - 1.5,0.7) ;
			TFC_SetMotorPWM(0.3,0.6);
			
		} 
		else 
		{
			TFC_SetMotorPWM(0.9,0.9);			
			//if(media >= a && media <= b )TFC_SetServo(0,0);
			
		}
	
	}
	return 0;
}
