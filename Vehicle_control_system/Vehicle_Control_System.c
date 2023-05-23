/*
 ===================================================================================================
 [FILE NAME]      : Vehicle_Control_System.c
 [AUTHOR]         : Ziad Emad (MT_73)
 [DATE CREATED]	  : 21/2/2022
 [DESCRIPTION]    : Vehicle Control system with the specifications.(with Bonus Requirement)
 ===================================================================================================
 */
#include <stdio.h>
#include "Vehicle_Settings.h"


int main()
{
#if WITH_ENGINE_TEMP_CONTROLLER ==0
	MainMenu();
#elif WITH_ENGINE_TEMP_CONTROLLER==1
	MainMenu();
#endif
	return 0;
}

