/*************************************************************************************************
 * [File Name]    : Vehicle_Settings.h
 * [Description]  : Header file for controlling our vehicle.
 * [Author]       : Ziad Emad
 **************************************************************************************************/

#ifndef VEHICLE_SETTINGS_H_
#define VEHICLE_SETTINGS_H_
#include <stdio.h>
/*================================================================================================
 	 	 	 	 	 	 	 	 	 	 Definitions
 ================================================================================================*/
#define WITH_ENGINE_TEMP_CONTROLLER 0

/*================================================================================================
 	 	 	 	 	 	 	 	 	 	 Types Declaration
 ================================================================================================*/

/*
 ===================================================================================================
 [enum]           : Vehicle_Control_System.c
 [enum description]	  : this ( enum ) responsible for making the code  OFF/ON states more readable.
 ===================================================================================================
 */
enum{
	OFF,ON
};




/*================================================================================================
 	 	 	 	 	 	 	 	 	 	 Functions Prototypes
 ================================================================================================*/


/*
*****************************************************************************************************

[Function Name]	: MainMenu
[Description]  	: This function is responsible for displaying the main menu of the control system.
[Arguments]    	: This function don't take any arguments.
[Returns]      	: This Function return the character the user choose from the options in the MainMenu.

****************************************************************************************************/
char MainMenu();

/*
*****************************************************************************************************

[Function Name]	:  Checking_state_validation
[Description]  	: This function is responsible for take the input then going to next stage of the menu .
[Arguments]    	: This function take the character the user put as input.
[Returns]      	: This Function return the character the user choose from the options in the MainMenu

****************************************************************************************************/
int Checking_state_validation(char state2);

/*
*****************************************************************************************************

[Function Name]	:  Sensors_set_menu
[Description]  	: This function go through the set Menu which has many options
[Arguments]    	: This function take no arguments.
[Returns]      	: This Function return nothing.

*****************************************************************************************************/
void Sensors_set_menu();

/*
*****************************************************************************************************

[Function Name]	: Sensors_set_menu_check
[Description]  	: This function go through the set Menu which has many options
[Arguments]    	: This function take a pointer to character which contain the value user entered in
				  sensor set menu.

*****************************************************************************************************/
int Sensors_set_menu_check(char *sensor_check);

/*
*****************************************************************************************************

[Function Name]	: Traffic_light_data
[Description]  	: This function go through the traffic light options.
[Arguments]    	: This function take no arguments.
[Returns]      	: This Function return the option user has entered.

*****************************************************************************************************/
char Traffic_light_data();

/*
*****************************************************************************************************

[Function Name]	: Traffic_light_data_analysis
[Description]  	: This function go through the traffic light options and choose one option to be applied.
[Arguments]    	: This function take  a pointer to character which contain the value user entered in
				  Traffic Light Data.
[Returns]      	: This Function return velocity of the Vehicle to be displayed.

*****************************************************************************************************/
int Traffic_light_data_analysis(char *traffic_status_analysis);

/*
*****************************************************************************************************

[Function Name]	: Room_Temperature_data
[Description]  	: This function take the room temperature from the user.
[Arguments]    	: This function take no arguments.
[Returns]      	: This Function return room temperature user has entered.

*****************************************************************************************************/
int Room_Temperature_data();

/*
*****************************************************************************************************

[Function Name]	: Room_Temperature_analysis
[Description]  	: This function go through the Room Temperature options and choose one option to be applied.
[Arguments]    	: This function take a pointer to character which contain the value user entered in
				  Room_Temperature_data.
[Returns]      	: This Function return Temperature of the AC

*****************************************************************************************************/
int Room_Temperature_analysis(int *temp_analysis);

/*
*****************************************************************************************************

[Function Name]	: AC
[Description]  	: This function control whether the AC is ON/OFF depending on the Value passed.
[Arguments]    	: This function take the state of the AC (ON/OFF).
[Returns]      	: This Function return nothing.

*****************************************************************************************************/
void AC(int x);

/*
*****************************************************************************************************

[Function Name]	: Controller_ENG
[Description]  	: This function control whether the Controller Engine is ON/OFF depending on the Value passed.
[Arguments]    	: This function take the state of the Controller Engine (ON/OFF).
[Returns]      	: This Function return nothing.

*****************************************************************************************************/
void Controller_ENG(int y);

/*
*****************************************************************************************************

[Function Name]	: Engine_Temperature_data
[Description]  	: This function take the Engine temperature from the user.
[Arguments]    	: This function take no arguments.
[Returns]      	: This Function return Engine temperature user has entered.

*****************************************************************************************************/
int Engine_Temperature_data();

/*
*****************************************************************************************************

[Function Name]	: Engine_Temperature_analysis
[Description]  	: This function go through the Engine Temperature options and choose one option to be applied.
[Arguments]    	: This function take a pointer to character which contain the value user entered in
				  Engine_Temperature_data.
[Returns]      	: This Function return Temperature of the Engine.

*****************************************************************************************************/
int Engine_Temperature_analysis(int *etemp_analysis);



#endif /* VEHICLE_SETTINGS_H_ */
