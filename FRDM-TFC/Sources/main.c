#include "derivative.h" /* include peripheral declarations */
#include "TFC\TFC.h"
int media = 64;

void fuzzy(void) {

	int spd =18000;
	int i = 0;
	double grauvl = 0;
	volatile float graul = 0;
	volatile float graum = 0;
	double graur = 0;
	double grauvr = 0;
	volatile float grausl = 0;
	volatile float grauf = 0;
	double graura = 0;
	double ns = 0;
	double nb = 0;
	double z = 0;
	double ps = 0;
	double pb = 0;
	int servang = 1000;
	double area[100];
	double grausaida = 0;
	double cognumerador = 0;
	double cogdenominador = 0;
	double cogfinal = 0;

//	float teste=(float)(media/22.0);

//---------------------OBTENÇÃO DE GRAU DAS FAIXA---------------------	
	if (((TFC_GetDIP_Switch() >> 1) & 0x03)==0) 
		TFC_HBRIDGE_DISABLE;
	else{

		for (i = 0; i < 100; i++) // zerar o vetor da área
				{
			area[i] = 0;
		}

//--------------Very left inicio------------------

		if (media < 21) {
			grauvl = 1; // puxadinho da esquerda
		} else if (media >= 21 && media < 40) {
			grauvl = ((float) (-media / 19.0)) + ((float) (40.0 / 19)); // reta s da folha
		} else
			grauvl = 0;
//----------very left final-------------

//-------------- left inicio------------------

		if (media >= 21 && media < 40) {
			graul = ((float) (media / 19.0)) - ((float) (21.0 / 19)); // reta r da folha
		} else if (media >= 40 && media < 59) {
			graul = ((float) (-media / 19.0)) + ((float) (59.0 / 19)); // reta u da folha
		} else
			graul = 0;
//---------- left final-------------	

//-------------- medium inicio------------------

		if (media >= 40 && media < 64) {
			graum = ((float) (media / 24.0)) - ((float) (5.0 / 3)); // reta t da folha
		} else if (media >= 64 && media < 90) {
			graum = ((float) (-media / 26.0)) + ((float) (43.0 / 13)); // reta w da folha
		} else
			graum = 0;
//---------- medium final-------------	

//-------------- right inicio------------------

		if (media >= 64 && media < 90) {
			graur = ((float) (media / 21.0)) - (23.0 / 7); // reta v da folha
		} else if (media >= 90 && media < 109) {
			graur = ((float) (-media / 19.0)) + ((float) (109.0 / 19)); // reta y da folha
		} else
			graur = 0;
//-------------- right final-------------			

//-------------- very right inicio------------------

		if (media >= 90 && media < 109) {
			grauvr = ((float) (media / 19.0)) - ((float) (90.0 / 19)); // reta x da folha
		} else if (media >= 109) {
			grauvr = 1; // reta y da folha
		} else
			grauvr = 0;
//-------------- very right final-------------			

//----------- FIM DA OBTENÇÃO DOS GRAUS DA FAIXA-------------

//----------- GRAU VELOCIDADE ----------------

//---------- SLOW --------------------------

		if (spd < 2000) {
			grausl = 1;

		} else if (spd >= 2000 && spd < 11000) {
			grausl = ((float) (-spd / 9000.0)) + ((float) (11.0 / 9));
		}

//--------------- FAST ---------------------

		if (spd > 2000 && spd < 11000) {
			grauf = ((float) (spd / 9000.0)) - ((float) (2.0 / 9));
		}

		else if (spd >= 11000 && spd < 18000) {
			grauf = ((float) (-spd / 7000.0)) + ((float) (18.0 / 7));
		}

//------------ RAPID ---------------------

		if (spd > 11000 && spd <= 18000) {
			graura = ((float) (spd / 7000.0)) - ((float) (11.0 / 7));
		} else if (spd > 18000)
			graura = 1;

//------------- FIM DOS GRAUS ---------------	

//---------- COMPARAÇÃO DOS GRAUS -------------

// --------------- SL e VL --------------

		if (grauvl < grausl) {
			ns = grauvl;
		} else
			ns = grausl;

		for (i = 0; i < 100; i++) {
			if (servang < 1250 || servang > 1500) {
				grausaida = 0;
				//if(area[i]<=grausaida) area[i]=grausaida;

			} else if (servang >= 1250 && servang <= 1375) {

				grausaida = ((float) (servang / 125.0)) - (10.0); // reta b

				if (grausaida > ns)
					grausaida = ns;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			else if (servang >= 1375 && servang <= 1500) {

				grausaida = ((float) (-servang / 125.0)) + (12.0); //reta c
				if (grausaida > ns)
					grausaida = ns;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}
			servang = servang + 10;
		}
		servang = 1000;

//-------------- SL e L ---------------
		if (graul < grausl) {
			ns = graul;
		} else
			ns = grausl;

		for (i = 0; i < 100; i++) {
			if (servang < 1250 || servang > 1500) {
				grausaida = 0;
				//if(area[i]<=grausaida) area[i]=grausaida;

			} else if (servang >= 1250 && servang <= 1375) {

				grausaida = ((float) (servang / 125.0)) - (10.0); // reta b
				if (grausaida > ns)
					grausaida = ns;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			else if (servang >= 1375 && servang <= 1500) {

				grausaida = ((float) (-servang / 125.0)) + (12.0); //reta c
				if (grausaida > ns)
					grausaida = ns;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}
			servang = servang + 10;
		}

		servang = 1000;

//-------------- SL e M ---------------
		if (graum < grausl) {
			z = graum;
		} else
			z = grausl;

		for (i = 0; i < 100; i++) {
			if (servang < 1375 || servang > 1625) {
				grausaida = 0;
				//if(area[i]<=grausaida) area[i]=grausaida;

			} else if (servang >= 1375 && servang <= 1500) {

				grausaida = ((float) (servang / 125.0)) - (11.0); // reta d
				if (grausaida > z)
					grausaida = z;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			else if (servang >= 1500 && servang <= 1625) {

				grausaida = ((float) (-servang / 125.0)) + (13.0); //reta e
				if (grausaida > z)
					grausaida = z;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}
			servang = servang + 10;
		}
		servang = 1000;
//------------ SL e R ----------------
		if (graur < grausl) {
			ps = graur;
		} else
			ps = grausl;

		for (i = 0; i < 100; i++) {
			if (servang < 1500 || servang > 1750) {
				grausaida = 0;
				//if(area[i]<=grausaida) area[i]=grausaida;

			} else if (servang >= 1500 && servang <= 1625) {

				grausaida = ((float) (servang / 125.0)) - (12.0); // reta f
				if (grausaida > ps)
					grausaida = ps;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			else if (servang >= 1625 && servang <= 1750) {

				grausaida = ((float) (-servang / 125.0)) + (14.0); //reta g
				if (grausaida > ps)
					grausaida = ps;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}
			servang = servang + 10;
		}
		servang = 1000;
//------------- SL e VR -------------
		if (grauvr < grausl) {
			ps = grauvr;
		} else
			ps = grausl;

		for (i = 0; i < 100; i++) {
			if (servang < 1500 || servang > 1750) {
				grausaida = 0;
				//if(area[i]<=grausaida) area[i]=grausaida;

			} else if (servang >= 1500 && servang <= 1625) {

				grausaida = ((float) (servang / 125.0)) - (12.0); // reta f
				if (grausaida > ps)
					grausaida = ps;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			else if (servang >= 1625 && servang <= 1750) {

				grausaida = ((float) (-servang / 125.0)) + (14.0); //reta g
				if (grausaida > ps)
					grausaida = ps;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}
			servang = servang + 10;
		}
		servang = 1000;
//------------- F e VL ----------
		if (grauvl < grauf) {
			nb = grauvl;
		} else
			nb = grauf;

		for (i = 0; i < 100; i++) {
			if (servang < 1250) {
				grausaida = nb;
				if (area[i] <= grausaida)
					area[i] = grausaida;

			} else if (servang > 1375) {
				grausaida = 0;
			} else if (servang >= 1250 && servang <= 1375) {

				grausaida = ((float) (-servang / (125.0))) + (11.0); // reta a
				if (grausaida > nb)
					grausaida = nb;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			servang = servang + 10;
		}
		servang = 1000;
//------------ F e L -----------
		if (graul < grauf) {
			ns = graul;
		} else
			ns = grauf;

		for (i = 0; i < 100; i++) {
			if (servang < 1250 || servang > 1500) {
				grausaida = 0;
				//if(area[i]<=grausaida) area[i]=grausaida;

			} else if (servang >= 1250 && servang <= 1375) {

				grausaida = ((float) (servang / 125.0)) - (10.0); // reta b
				if (grausaida > ns)
					grausaida = ns;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			else if (servang >= 1375 && servang <= 1500) {

				grausaida = ((float) (-servang / 125.0)) + (12.0); //reta c
				if (grausaida > ns)
					grausaida = ns;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}
			servang = servang + 10;
		}
		servang = 1000;
//----------- F e M -----------
		if (graum < grauf) {
			z = graum;
		} else
			z = grauf;

		for (i = 0; i < 100; i++) {
			if (servang < 1375 || servang > 1625) {
				grausaida = 0;
				//if(area[i]<=grausaida) area[i]=grausaida;

			} else if (servang >= 1375 && servang <= 1500) {

				grausaida = ((float) (servang / 125.0)) - (11.0); // reta d
				if (grausaida > z)
					grausaida = z;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			else if (servang >= 1500 && servang <= 1625) {

				grausaida = ((float) (-servang / 125.0)) + (13.0); //reta e
				if (grausaida > z)
					grausaida = z;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}
			servang = servang + 10;
		}
		servang = 1000;
//---------- F e R ---------
		if (graur < grauf) {
			ps = graur;
		} else
			ps = grauf;
		for (i = 0; i < 100; i++) {
			if (servang < 1500 || servang > 1750) {
				grausaida = 0;
				//if(area[i]<=grausaida) area[i]=grausaida;

			} else if (servang >= 1500 && servang <= 1625) {

				grausaida = ((float) (servang / 125.0)) - (12.0); // reta f
				if (grausaida > ps)
					grausaida = ps;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			else if (servang >= 1625 && servang <= 1750) {

				grausaida = ((float) (-servang / 125.0)) + (14.0); //reta g
				if (grausaida > ps)
					grausaida = ps;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}
			servang = servang + 10;
		}
		servang = 1000;
//---------- F e VR ---------
		if (grauvr < grauf) {
			pb = grauvr;
		} else
			pb = grauf;

		for (i = 0; i < 100; i++) {
			if (servang > 1750) {
				grausaida = pb;

				if (area[i] <= grausaida)
					area[i] = grausaida;

			} else if (servang < 1625) {
				grausaida = 0;
			} else if (servang >= 1625 && servang <= 1750) {
				grausaida = ((float) (servang / 125.0)) - ((float) 13.0); // reta h
				if (grausaida > pb)
					grausaida = pb;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			servang = servang + 10;
		}
		servang = 1000;
//--------- R e VL -----------
		if (grauvl < graura) {
			nb = grauvl;
		} else
			nb = graura;

		for (i = 0; i < 100; i++) {
			if (servang < 1250) {
				grausaida = nb;
				if (area[i] <= grausaida)
					area[i] = grausaida;

			} else if (servang > 1375) {
				grausaida = 0;
			} else if (servang >= 1250 && servang <= 1375) {

				grausaida = ((float) (servang / (-125.0))) + (11.0); // reta a
				if (grausaida > nb)
					grausaida = nb;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			servang = servang + 10;
		}
		servang = 1000;
//--------- R e L -----------
		if (graul < graura) {
			nb = graul;
		} else
			nb = graura;

		for (i = 0; i < 100; i++) {
			if (servang < 1250) {
				grausaida = nb;
				if (area[i] <= grausaida)
					area[i] = grausaida;

			} else if (servang > 1375) {
				grausaida = 0;
			} else if (servang >= 1250 && servang <= 1375) {

				grausaida = ((float) (servang / (-125.0))) + (11.0); // reta a
				if (grausaida > nb)
					grausaida = nb;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			servang = servang + 10;
		}

		servang = 1000;
//--------- R e M-----------
		if (graum < graura) {
			z = graum;
		} else
			z = graura;

		for (i = 0; i < 100; i++) {
			if (servang < 1375 || servang > 1625) {
				grausaida = 0;
				//if(area[i]<=grausaida) area[i]=grausaida;

			} else if (servang >= 1375 && servang <= 1500) {

				grausaida = ((float) (servang / 125.0)) - (11.0); // reta d
				if (grausaida > z)
					grausaida = z;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			else if (servang >= 1500 && servang <= 1625) {

				grausaida = ((float) (-servang / 125.0)) + (13.0); //reta e
				if (grausaida > z)
					grausaida = z;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}
			servang = servang + 10;
		}
		servang = 1000;
//--------- R e R -----------
		if (graur < graura) {
			pb = graur;
		} else
			pb = graura;

		for (i = 0; i < 100; i++) {
			if (servang > 1750) {
				grausaida = pb;
				if (area[i] <= grausaida)
					area[i] = grausaida;

			} else if (servang < 1625) {
				grausaida = 0;
			} else if (servang >= 1625 && servang <= 1750) {
				grausaida = ((float) (servang / 125.0)) - (13.0); // reta h
				if (grausaida > pb)
					grausaida = pb;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			servang = servang + 10;
		}
		servang = 1000;
//--------- R e VR -----------
		if (grauvr < graura) {
			pb = grauvr;
		} else
			pb = graura;

		for (i = 0; i < 100; i++) {
			if (servang > 1750) {
				grausaida = pb;
				if (area[i] <= grausaida)
					area[i] = grausaida;

			} else if (servang < 1625) {
				grausaida = 0;
			} else if (servang >= 1625 && servang <= 1750) {
				grausaida = ((float) (servang / 125.0)) - (13.0); // reta h
				if (grausaida > pb)
					grausaida = pb;
				if (area[i] <= grausaida)
					area[i] = grausaida;
			}

			servang = servang + 10;
		}
		servang = 1000;

//--------------Fim comparação de graus------------------	
		servang = 1000;
		for (i = 0; i < 100; i++) {
			cognumerador = cognumerador + (area[i] * servang * 1.0);
			servang = servang + 10;
		}

		servang = 1000;
		for (i = 0; i < 100; i++) {
			cogdenominador = cogdenominador + area[i];
		}

		cogfinal = cognumerador / cogdenominador;
		TFC_HBRIDGE_ENABLE;
		//if(cogfinal>1500)
		TFC_SetServo(0, cogfinal * 1.0 / 500.0 - 3.0);

		if (cogfinal > 1525) {

			TFC_SetMotorPWM(0.35, 0.2);
		}

		else if (cogfinal < 1475) {
			TFC_SetMotorPWM(0.2, 0.35);
		} else {
			TFC_SetMotorPWM(0.4, 0.4);
		}
	//	TFC_SetMotorPWM(0, 0);
	}
}

int main(void) {
	uint32_t t, i = 0, a = 0, b = 0, limiar = 0xFE0;
	//TFC_SetServo(0,0);
	float teste = 0;
	TFC_Init();

	for (;;) {
		if (LineScanImageReady == 1) {
		//	TFC_SetServo(0,0);
			a = 63;
			b = 64;
			while (LineScanImage0[a] >= limiar || LineScanImage0[b] >= limiar) {
				if (LineScanImage0[a] >= limiar) {
					a--;
				}
				if (LineScanImage0[b] >= limiar) {
					b++;
				}
			}
			if ((b - a) <= 60) {
				a = 10;
				b = 117;
				while (LineScanImage0[a] >= limiar || LineScanImage0[b] >= limiar) {
								if (LineScanImage0[a] >= limiar) {
									a++;
								}
								if (LineScanImage0[b] >= limiar) {
									b--;
								}
							}
				
				//media = media;
			} else {
				media = (int) (a + b) / 2;
			}
			/*if(media<60)TFC_SetServo(0,-0.5);
			 else if (media>70)
			 TFC_SetServo(0,0.5);
			 else TFC_SetServo(0,0);
			 
			 if(LineScanImage0[a]<=limiar)
			 {
			 TFC_SetServo(0,1.0);
			 }
			 else if(LineScanImage0[b]<=limiar)
			 {
			 TFC_SetServo(0,-1.0);
			 }
			 else 
			 TFC_HBRIDGE_ENABLE;
			 
			 if(teste>0.1)	TFC_SetMotorPWM(7.0/20.0,0.2);
			 else if(teste<-0.1)TFC_SetMotorPWM(0.2,7.0/20.0);
			 else 
			 TFC_SetMotorPWM(0.5,0.5);
			 
			 teste = media / 64.0 - 1.0;
			 TFC_SetServo(0, teste);*/
		}

		//Demo Mode 3 will be in Freescale Garage Mode.  It will beam data from the Camera to the 
		//Labview Application

		if (TFC_Ticker[0] > 100 && LineScanImageReady == 1) {
			TFC_Ticker[0] = 0;
			LineScanImageReady = 0;
			TERMINAL_PRINTF("\r\n");
			TERMINAL_PRINTF("L:");

			if (t == 0)
				t = 3;
			else
				t--;

			TFC_SetBatteryLED_Level(t);

			for (i = 0; i < 128; i++) {
				TERMINAL_PRINTF("%X,", LineScanImage0[i]);
			}

			for (i = 0; i < 128; i++) {
				TERMINAL_PRINTF("%X", LineScanImage1[i]);
				if (i == 127)
					TERMINAL_PRINTF("\r\n", LineScanImage1[i]);
				else
					TERMINAL_PRINTF(",", LineScanImage1[i]);
			}

		}

		//TFC_Task must be called in your main loop.  This keeps certain processing happy (I.E. Serial port queue check)
		TFC_Task();
		fuzzy();
		//This Demo program will look at the middle 2 switch to select one of 4 demo modes.
		//Let's look at the middle 2 switches
		/*switch ((TFC_GetDIP_Switch() >> 1) & 0x03) {
		 default:
		 case 0:
		 //Demo mode 0 just tests the switches and LED's
		 if (TFC_PUSH_BUTTON_0_PRESSED)
		 TFC_BAT_LED0_ON;
		 else
		 TFC_BAT_LED0_OFF;

		 if (TFC_PUSH_BUTTON_1_PRESSED)
		 TFC_BAT_LED3_ON;
		 else
		 TFC_BAT_LED3_OFF;

		 if (TFC_GetDIP_Switch() & 0x01)
		 TFC_BAT_LED1_ON;
		 else
		 TFC_BAT_LED1_OFF;

		 if (TFC_GetDIP_Switch() & 0x08)
		 TFC_BAT_LED2_ON;
		 else
		 TFC_BAT_LED2_OFF;

		 break;

		 case 1:

		 //Demo mode 1 will just move the servos with the on-board potentiometers
		 if (TFC_Ticker[0] >= 20) {
		 TFC_Ticker[0] = 0; //reset the Ticker
		 //Every 20 mSeconds, update the Servos
		 TFC_SetServo(0, 0.0);
		 //	TFC_SetServo(1,TFC_ReadPot(1));
		 }
		 //Let's put a pattern on the LEDs
		 if (TFC_Ticker[1] >= 125) {
		 TFC_Ticker[1] = 0;
		 t++;
		 if (t > 4) {
		 t = 0;
		 }
		 TFC_SetBatteryLED_Level(t);
		 }

		 TFC_SetMotorPWM(0, 0); //Make sure motors are off
		 TFC_HBRIDGE_DISABLE;

		 break;

		 case 2:

		 //Demo Mode 2 will use the Pots to make the motors move
		 TFC_HBRIDGE_ENABLE;
		 TFC_SetMotorPWM(TFC_ReadPot(0), TFC_ReadPot(1));

		 //Let's put a pattern on the LEDs
		 if (TFC_Ticker[1] >= 125) {
		 TFC_Ticker[1] = 0;
		 t++;
		 if (t > 4) {
		 t = 0;
		 }
		 TFC_SetBatteryLED_Level(t);
		 }
		 break;

		 case 3:
		 


		 if (LineScanImageReady == 1) {

		 a = 63;
		 b = 64;
		 while (LineScanImage0[a] >= limiar
		 || LineScanImage0[b] >= limiar) {
		 if (LineScanImage0[a] >= limiar) {
		 a--;
		 }
		 if (LineScanImage0[b] >= limiar) {
		 b++;
		 }
		 }
		 if ((b - a) <= 50) {
		 media = media;
		 } else {
		 media = (int) (a + b) / 2;
		 }
		 /*if(media<60)TFC_SetServo(0,-0.5);
		 else if (media>70)
		 TFC_SetServo(0,0.5);
		 else TFC_SetServo(0,0);
		 
		 if(LineScanImage0[a]<=limiar)
		 {
		 TFC_SetServo(0,1.0);
		 }
		 else if(LineScanImage0[b]<=limiar)
		 {
		 TFC_SetServo(0,-1.0);
		 }
		 else 
		 TFC_HBRIDGE_ENABLE;
		 
		 if(teste>0.1)	TFC_SetMotorPWM(7.0/20.0,0.2);
		 else if(teste<-0.1)TFC_SetMotorPWM(0.2,7.0/20.0);
		 else 
		 TFC_SetMotorPWM(0.5,0.5);
		 
		 teste = media / 64.0 - 1.0;
		 TFC_SetServo(0, teste);
		 }

		 //Demo Mode 3 will be in Freescale Garage Mode.  It will beam data from the Camera to the 
		 //Labview Application

		 if (TFC_Ticker[0] > 100 && LineScanImageReady == 1) {
		 TFC_Ticker[0] = 0;
		 LineScanImageReady = 0;
		 TERMINAL_PRINTF("\r\n");
		 TERMINAL_PRINTF("L:");

		 if (t == 0)
		 t = 3;
		 else
		 t--;

		 TFC_SetBatteryLED_Level(t);

		 for (i = 0; i < 128; i++) {
		 TERMINAL_PRINTF("%X,", LineScanImage0[i]);
		 }

		 for (i = 0; i < 128; i++) {
		 TERMINAL_PRINTF("%X", LineScanImage1[i]);
		 if (i == 127)
		 TERMINAL_PRINTF("\r\n", LineScanImage1[i]);
		 else
		 TERMINAL_PRINTF(",", LineScanImage1[i]);
		 }

		 }

		 break;
		 }*/
	}

	return 0;
}
