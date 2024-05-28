/*
 * main.c
 *
 *  Created on: 2024 May 28 11:50:40
 *  Author: Administrator
 */




#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

int delay1000;

void callback() {
	if(delay1000 > 0) delay1000--;
}

void delay(int d) {
	delay1000 = d;
	while(delay1000 > 0);
}

void setFrequency(int freq) {
	PWM_SetDutyCycle(&PWM_0, freq/2);
	PWM_SetFreq(&PWM_0, freq);
}

void stop() {
	PWM_SetDutyCycle(&PWM_0, 0);
}

void sound(char ch) {
	int soundTable[] = {261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493, 523};
	switch(ch) {
		case 'c': setFrequency(soundTable[0]); break;
		case 'C': setFrequency(soundTable[1]); break;
		case 'd': setFrequency(soundTable[2]); break;
		case 'D': setFrequency(soundTable[3]); break;
		case 'e': setFrequency(soundTable[4]); break;
		case 'f': setFrequency(soundTable[5]); break;
		case 'F': setFrequency(soundTable[6]); break;
		case 'g': setFrequency(soundTable[7]); break;
		case 'G': setFrequency(soundTable[8]); break;
		case 'b': setFrequency(soundTable[9]); break;
	}
}

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if (status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  int id = SYSTIMER_CreateTimer(1000, SYSTIMER_MODE_PERIODIC, callback, NULL);
  SYSTIMER_StartTimer(id);

  PWM_Start(&PWM_0);

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
  	const char music[] = {"eDeDebdcaceabeGbceeDeDebdcaceabecba"};
  	for(int i = 0; i < strlen(music); i++) {
  		sound(music[i]);
  		delay(500);
  	}
  }
}
