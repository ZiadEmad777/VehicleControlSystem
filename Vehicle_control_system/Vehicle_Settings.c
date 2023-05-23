/*************************************************************************************************
 * [File Name]    : Vehicle_Settings.c
 * [Description]  : source file for controlling our vehicle.
 * [Author]       : Ziad Emad
 **************************************************************************************************/
#include "Vehicle_Settings.h"



/*
*****************************************************************************************************

[Function Name]	: MainMenu
[Description]  	: This function is responsible for displaying the main menu of the control system.
[Arguments]    	: This function don't take any arguments.
[Returns]      	: This Function return the character the user choose from the options in the MainMenu.

****************************************************************************************************/
char MainMenu(){
	char state1;
	//taking the choice from the user
	printf("Welcome to the Vehicle control system:\n");
	printf("a. Turn ON the vehicle engine\n");
	printf("b. Turn OFF the vehicle engine\n");
	printf("c. Quit the system\n");
	fflush(stdout);
	scanf(" %c",&state1);
	// Checking the validity of state1
	Checking_state_validation(state1);
	return state1;
}


/*
*****************************************************************************************************

[Function Name]	:  Checking_state_validation
[Description]  	: This function is responsible for take the input then going to next stage of the menu .
[Arguments]    	: This function take the character the user put as input.
[Returns]      	: This Function return the character the user choose from the options in the MainMenu

****************************************************************************************************/
int Checking_state_validation(char state2){
	//using switch statement for decision making for the MainMenu
	switch (state2) {
	case 'C':
	case 'c':
		// By choosing option (c) the program will End
		printf("GOOD BYE :)\n");
		printf("%s\n%s\n",__DATE__,__TIME__);
		break;
	case 'B':
	case 'b':
		// By choosing option (b) engine will be turned OFF then we return to the MainMenu
		printf("\nTurning OFF the Vehicle Engine\n\n");
		MainMenu();
		break;
	case 'A':
	case 'a':
		// By choosing option (a) engine will be turned ON then we go to SetMenu
		printf("\nTurning ON the Vehicle Engine\n\n");
		//display “Sensors set menu”, menu that simulates the vehicle sensors readings.
		Sensors_set_menu();
		break;
	default:
		// in case of entering a wrong button we will warn the user and return to the MainMenu
		printf("\nWARNING! you entered a wrong button\n\n");
		MainMenu();
		break;
	}
	return 0;
}


/*
*****************************************************************************************************

[Function Name]	:  Sensors_set_menu
[Description]  	: This function go through the set Menu which has many options
[Arguments]    	: This function take no arguments.
[Returns]      	: This Function return nothing.

*****************************************************************************************************/
void Sensors_set_menu(){
	char sensor_state;
#if WITH_ENGINE_TEMP_CONTROLLER==0
	printf("Sensors set menu:\n");
	printf("a. Turn off the engine \n");
	printf("b. Set the traffic light color \n");
	printf("c. Set the room temperature (Temperature Sensor) \n");
	printf("d. Set the engine temperature (Engine Temperature Sensor) \n");
	fflush(stdout);
	scanf(" %c",&sensor_state);
	// Checking the validity of sensor state that user entered.
	Sensors_set_menu_check(&sensor_state);


#elif WITH_ENGINE_TEMP_CONTROLLER==1
	printf("Sensors set menu:\n");
	printf("a. Turn off the engine \n");
	printf("b. Set the engine temperature (Engine Temperature Sensor) \n");
	printf("c. Setting vehicle speed=30km/hr.\n");
	fflush(stdout);
	scanf(" %c",&sensor_state);
	// Checking the validity of sensor state that user entered.
	Sensors_set_menu_check(&sensor_state);
#endif
}

/*
*****************************************************************************************************

[Function Name]	: Sensors_set_menu_check
[Description]  	: This function go through the set Menu which has many options
[Arguments]    	: This function take a pointer to character which contain the value user entered in
				  sensor set menu.

*****************************************************************************************************/
int Sensors_set_menu_check(char *sensor_check){

	int vehicle_velocity=100;
	char traffic_sign;
	int RoomTemp=20,ac_temp;
	int ac_temp_state=OFF,engine_controller_state=OFF;
	int Engine_temp=90,engine_temperature_controller;


#if WITH_ENGINE_TEMP_CONTROLLER==0
	// By choosing option (a) engine will be turned OFF then we return to the MainMenu
	if (('a'== *sensor_check) | ('A'== *sensor_check) ){
		// turning OFF the engine from set menu
		printf("Turning OFF the Engine\n\n");
		MainMenu();
	}
	// By choosing option (b) program go through the traffic light settings
	else if (('b'== *sensor_check) | ('B'== *sensor_check)){
		//  Taking Traffic light color from the sensor
		traffic_sign=Traffic_light_data();
		// Determine the speed of the vehicle
		vehicle_velocity = Traffic_light_data_analysis(&traffic_sign);
		if (vehicle_velocity==30) {

			//printing Values required for the output
			printf("\nEngine: ON\n");
			ac_temp_state= ON; //AC is ON
			AC(ac_temp_state);
			printf("Vehicle Speed: %d Km/hr\n",vehicle_velocity);
			RoomTemp=((RoomTemp*5)/4)+1;
			printf("Room Temperature : %d degree C\n",RoomTemp);
			engine_controller_state=ON; //Controller is  ON
			Controller_ENG(engine_controller_state);
			Engine_temp=((Engine_temp*5)/4)+1;
			printf("Engine Temperature: %d degree C \n\n",Engine_temp);
			// showing the sensor set menu for the user again
			Sensors_set_menu();
		}
		else {
			// printing the values in any other velocities
			printf("\nEngine: ON\n");
			AC(ac_temp_state);
			printf("Vehicle Speed: %d Km/hr\n",vehicle_velocity);
			printf("Room Temperature : %d degree C\n",RoomTemp);
			Controller_ENG(engine_controller_state);
			printf("Engine Temperature: %d degree C \n\n",Engine_temp);
			Sensors_set_menu();
		}
	}

	// By choosing option (c) program go through the temperature settings
	else if (('c'== *sensor_check) | ('C'== *sensor_check)){
		// Temperature Sensor
		RoomTemp=Room_Temperature_data();

		//printing Values required
		printf("\nEngine: ON\n");
		ac_temp=Room_Temperature_analysis(&RoomTemp);
		printf("Vehicle Speed: %d Km/hr\n",vehicle_velocity);
		printf("Room Temperature : %d degree C\n",ac_temp);
		Controller_ENG(engine_controller_state);
		printf("Engine Temperature: %d degree C \n\n",Engine_temp);
		// showing the sensor set menu for the user again
		Sensors_set_menu();

	}

	// By choosing option (d) program go through the Engine temperature settings
	else if (('d'== *sensor_check) | ('D'== *sensor_check)){
		//Engine Temperature Sensor
		Engine_temp= Engine_Temperature_data();

		//printing Values required
		printf("\nEngine: ON\n");
		printf("Vehicle Speed: %d Km/hr\n",vehicle_velocity);
		printf("Room Temperature : %d degree C\n",RoomTemp);
		engine_temperature_controller=Engine_Temperature_analysis(&Engine_temp);
		printf("Engine Temperature: %d degree C \n\n",engine_temperature_controller);
		// showing the sensor set menu for the user again
		Sensors_set_menu();


	}
	else{
		// in case of entering a wrong button we will warn the user and return to the sensor set menu
		printf("\nWARNING! you entered a wrong button\n\n");
		Sensors_set_menu();
	}


#elif WITH_ENGINE_TEMP_CONTROLLER==1
	// By choosing option (a) engine will be turned OFF then we return to the MainMenu
	if (('a'== *sensor_check) | ('A'== *sensor_check) ){
		// turning OFF the engine from set menu
		printf("Turning OFF the Engine\n\n");
		MainMenu();
	}
	else if (('b'== *sensor_check) | ('B'== *sensor_check)){
		//Engine Temperature Sensor
		Engine_temp= Engine_Temperature_data();

		//printing Values required
		printf("\nEngine: ON\n");
		engine_temperature_controller=Engine_Temperature_analysis(&Engine_temp);
		printf("Engine Temperature: %d degree C \n\n",engine_temperature_controller);
		// showing the sensor set menu for the user again
		Sensors_set_menu();
	}
	else if (('c'== *sensor_check) | ('C'== *sensor_check)){
		//printing Values required for the output
		printf("\nEngine: ON\n");
		engine_controller_state=ON; //Controller is  ON
		Controller_ENG(engine_controller_state);
		Engine_temp=((Engine_temp*5)/4)+1;
		printf("Engine Temperature: %d degree C \n\n",Engine_temp);
		// showing the sensor set menu for the user again
		Sensors_set_menu();
	}
	else
	{
		// in case of entering a wrong button we will warn the user and return to the sensor set menu
		printf("\nWARNING! you entered a wrong button\n\n");
		Sensors_set_menu();

	}
#endif
	return 0;
}

/*
*****************************************************************************************************

[Function Name]	: Traffic_light_data
[Description]  	: This function go through the traffic light options.
[Arguments]    	: This function take no arguments.
[Returns]      	: This Function return the option user has entered.

*****************************************************************************************************/
char Traffic_light_data(){
	char traffic_status;
	/*Based on traffic light data (Take it as input from console, we will assume that this is the sensor read value)*/
	printf("if The traffic light is (green) then press: (G)\n");
	printf("if The traffic light is (orange) then press: (O)\n");
	printf("if The traffic light is (Red) then press: (R)\n");
	fflush(stdout);
	scanf(" %c",&traffic_status);
	return traffic_status;
}

/*
*****************************************************************************************************

[Function Name]	: Traffic_light_data_analysis
[Description]  	: This function go through the traffic light options and choose one option to be applied.
[Arguments]    	: This function take  a pointer to character which contain the value user entered in
				  Traffic Light Data.
[Returns]      	: This Function return velocity of the Vehicle to be displayed.

*****************************************************************************************************/
int Traffic_light_data_analysis(char *traffic_status_analysis){
	int vehicle_speed=0;
	/*Based on traffic light data (Take it as input from console, we will assume that this is the sensor read value)
			i. If the traffic light is ‘G’ set vehicle speed to 100 km/hr
			ii. If the traffic light is ‘O’ set vehicle speed to 30 km/hr
			iii. If the traffic light is ‘R’ set vehicle speed to 0 km/hr
	 */
	if (('G'==*traffic_status_analysis) | ('g'==*traffic_status_analysis)) {
		vehicle_speed=100;
	}
	else if (('O'==*traffic_status_analysis) | ('o'==*traffic_status_analysis)) {
		vehicle_speed=30;

	}
	else if (('R'==*traffic_status_analysis) | ('r'==*traffic_status_analysis)) {
		vehicle_speed=0;
	}
	else{
		printf("\nWARNING! you entered a wrong button\n\n");
	}
	return vehicle_speed;
}


/*
*****************************************************************************************************

[Function Name]	: AC
[Description]  	: This function control whether the AC is ON/OFF depending on the Value passed.
[Arguments]    	: This function take the state of the AC (ON/OFF).
[Returns]      	: This Function return nothing.

*****************************************************************************************************/
void AC(int x){
	// 1 means ON , zero means OFF
	if (x==ON) {
		printf("AC: ON\n");
	}
	else{
		printf("AC: OFF\n");
	}
}

/*
*****************************************************************************************************

[Function Name]	: Room_Temperature_data
[Description]  	: This function take the room temperature from the user.
[Arguments]    	: This function take no arguments.
[Returns]      	: This Function return room temperature user has entered.

*****************************************************************************************************/
int Room_Temperature_data(){
	//Take it as input from console, we will assume that this is the sensor read value)
	int room_temp;
	printf("Enter the room Temperature required:  ");
	fflush(stdout);
	scanf(" %d",&room_temp);
	return room_temp;
}

/*
*****************************************************************************************************

[Function Name]	: Room_Temperature_analysis
[Description]  	: This function go through the Room Temperature options and choose one option to be applied.
[Arguments]    	: This function take a pointer to character which contain the value user entered in
				  Room_Temperature_data.
[Returns]      	: This Function return Temperature of the AC

*****************************************************************************************************/
int Room_Temperature_analysis(int *temp_analysis){
	/*Based on room temperature data
	 *		i. If temperature less than 10  set temperature to 20
			ii. If temperature is greater than 30, set temperature to 20
			iii. If temperature is otherwise, Turn AC OFF.
	 */
	int AC_temp=OFF;
	if ((*temp_analysis<=10) | (*temp_analysis>=30)) {
		AC_temp=20;
		AC(ON);
	}
	else {
		AC(OFF);
	}
	return AC_temp;
}


#if WITH_ENGINE_TEMP_CONTROLLER==0
/*
*****************************************************************************************************

[Function Name]	: Controller_ENG
[Description]  	: This function control whether the Controller Engine is ON/OFF depending on the Value passed.
[Arguments]    	: This function take the state of the Controller Engine (ON/OFF).
[Returns]      	: This Function return nothing.

*****************************************************************************************************/
void Controller_ENG(int y){
	if (y==ON) {
		printf("Engine Temperature Controller: ON\n");
	}
	else{
		printf("Engine Temperature Controller: OFF\n");
	}
}

/*
*****************************************************************************************************

[Function Name]	: Engine_Temperature_data
[Description]  	: This function take the Engine temperature from the user.
[Arguments]    	: This function take no arguments.
[Returns]      	: This Function return Engine temperature user has entered.

*****************************************************************************************************/
int Engine_Temperature_data(){
	int engines_temp;
	printf("Enter the Engine Temperature required:  ");
	fflush(stdout);
	scanf(" %d",&engines_temp);
	return engines_temp;
}

/*
*****************************************************************************************************

[Function Name]	: Engine_Temperature_analysis
[Description]  	: This function go through the Engine Temperature options and choose one option to be applied.
[Arguments]    	: This function take a pointer to character which contain the value user entered in
				  Engine_Temperature_data.
[Returns]      	: This Function return Temperature of the Engine.

*****************************************************************************************************/
int Engine_Temperature_analysis(int *etemp_analysis){
	int temp_engine;
	if ((*etemp_analysis<=100) | (*etemp_analysis>=150)) {
		Controller_ENG(ON);
		temp_engine=125;
	}
	else {
		Controller_ENG(OFF);
	}
	return temp_engine;
}

#elif WITH_ENGINE_TEMP_CONTROLLER==1
/*
*****************************************************************************************************

[Function Name]	: Controller_ENG
[Description]  	: This function control whether the Controller Engine is ON/OFF depending on the Value passed.
[Arguments]    	: This function take the state of the Controller Engine (ON/OFF).
[Returns]      	: This Function return nothing.

*****************************************************************************************************/
void Controller_ENG(int y){
	if (y==ON) {
		printf("Engine Temperature Controller: ON\n");
	}
	else{
		printf("Engine Temperature Controller: OFF\n");
	}
}

/*
*****************************************************************************************************

[Function Name]	: Engine_Temperature_data
[Description]  	: This function take the Engine temperature from the user.
[Arguments]    	: This function take no arguments.
[Returns]      	: This Function return Engine temperature user has entered.

*****************************************************************************************************/
int Engine_Temperature_data(){
	int engines_temp;
	printf("Enter the Engine Temperature required:  ");
	fflush(stdout);
	scanf(" %d",&engines_temp);
	return engines_temp;
}

/*
*****************************************************************************************************

[Function Name]	: Engine_Temperature_analysis
[Description]  	: This function go through the Engine Temperature options and choose one option to be applied.
[Arguments]    	: This function take a pointer to character which contain the value user entered in
				  Engine_Temperature_data.
[Returns]      	: This Function return Temperature of the Engine.

*****************************************************************************************************/
int Engine_Temperature_analysis(int *etemp_analysis){
	int temp_engine;
	if ((*etemp_analysis<=100) | (*etemp_analysis>=150)) {
		Controller_ENG(ON);
		temp_engine=125;
	}
	else {
		Controller_ENG(OFF);
	}
	return temp_engine;
}
#endif

