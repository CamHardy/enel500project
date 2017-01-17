// compile with g++ -std=c++11 motor_movement_tests.cpp motor.cpp -I$HOME/Downloads/DynamixelSDK/c++/build/linux64 -L/opt/lib -l dxl_x64_cpp -o motor_movement_tests

#ifdef __linux__
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "dynamixel_sdk.h"                                  // Uses Dynamixel SDK library
#include "motor_physical_limits.h"			    // Constants for Limb Limitations
#include "motor.h"					    // Motor Data Class

//Tip of Shoulder: x1, shoulder: x2, rest goes down x3-x6, x5 is unplugged

// Control table address
#define ADDR_MX_TORQUE_ENABLE           24                  // Control table address is different in Dynamixel model
#define ADDR_MX_GOAL_POSITION           30
#define ADDR_MX_PRESENT_POSITION        36
#define ADDR_MX_MOVING_SPEED_L		32
#define ADDR_MX_MOVING_SPEED_H		33

// Protocol version
#define PROTOCOL_VERSION                1.0                 // See which protocol version is used in the Dynamixel

// Default setting
//int dxl_ID[15] = {11, 12, 21, 22, 23, 24, 26, 31, 32, 33, 34, 36, 41, 42, 43};                   // Dynamixel ID: 1
#define BAUDRATE                        1000000
#define DEVICENAME                      "/dev/ttyUSB0"      // Check which port is being used on your controller
                                                            // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0"

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque
#define DXL_MINIMUM_POSITION_VALUE      0                 // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE      4095                // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)

#define TEST_MOVEMENT_SPEED 		30
#define DXL_MOVING_STATUS_THRESHOLD     5                  // Dynamixel moving status threshold

#define UP_ASCII_VALUE                 0x77
#define DOWN_ASCII_VALUE				0x73
#define PRINT_ASCII_VALUE				0x7a
int i = 0;

using namespace std;

int getch() {
#ifdef __linux__
  	char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
#endif
}

vector<Motor *> motors;
vector<Motor *>::iterator Iterator;

void displayMenu() {
	cout << "Choose which motor you want to test: " << endl;
	cout << "Motors: " << endl;
	cout << "ID 11: Head Motor || PRESS 1" << endl;
	cout << "ID 12: Neck Motor || PRESS 2" << endl;
	cout << "ID 21: Left Arm Shoulder Tip Motor || PRESS 3" << endl;
	cout << "ID 22: Left Arm Shoulder Motor || PRESS 4" << endl;
	cout << "ID 24: Left Arm Elbow Motor || PRESS 5" << endl;
	cout << "ID 31: Right Arm Shoulder Tip Motor || PRESS 6" << endl;
	cout << "ID 32: Right Arm Shoulder Motor || PRESS 7" << endl;
	cout << "ID 34: Right Arm Elbow Motor || PRESS 8" << endl;
	cout << "ID 43: Waist Motor || PRESS 9" << endl;	
	cout << "OTHER OPTIONS: " << endl;
	cout << "Q to quit the simulation." <<endl;
}

/* Broken code; mainly just used for testing for now */
int whichMotor(int input) {
	switch(input) {
	 	case 49 : return 11;
		case 50 : return 12;
		case 51 : return 21;
		case 52 : return 22;
		case 53 : return 24;
		case 54 : return 31;
		case 55 : return 32;
		case 56 : return 34;
		//case 57 : return 43;
		default : cout << "Invalid input." << endl; return 0;
	}		
}

bool keepThisMotor(){
	cout << "Do you want to continue testing this motor?" <<endl;
	cout << "Y for yes." <<endl;
	cout << "Any other input will assume that you want to change the motor selected." << endl;

	int input = getch();

	return (input == 89 || input == 121) ? true : false;
}

void init() {}

void setupMotors() {
	/* Hacky motor declarations for now; might change it to a data structure in the future */
	// To Do: Add Motor 23 and 33 for testing purposes later
	Motor *motorHead = new Motor(HEAD_MOTOR_LOW_VALUE, HEAD_MOTOR_HIGH_VALUE, 11);
	motors.push_back(motorHead);

	Motor *motorNeck = new Motor(NECK_MOTOR_LOW_VALUE, NECK_MOTOR_HIGH_VALUE, 12);
	motors.push_back(motorNeck);

	Motor *motorLAT = new Motor(LA_SHOULDER_TIP_LOW, LA_SHOULDER_TIP_HIGH, 21);
	motors.push_back(motorLAT);

	Motor *motorLAS = new Motor(LA_SHOULDER_LOW, LA_SHOULDER_HIGH, 22);
	motors.push_back(motorLAS);

	Motor *motorLAE = new Motor(LA_ELBOW_LOW, LA_ELBOW_HIGH, 24);
	motors.push_back(motorLAE);

	Motor *motorRAT = new Motor(RA_SHOULDER_TIP_LOW, RA_SHOULDER_TIP_HIGH, 31);
	motors.push_back(motorRAT);

	Motor *motorRAS = new Motor(RA_SHOULDER_LOW, RA_SHOULDER_HIGH, 32);
	motors.push_back(motorRAS);

	Motor *motorRAE = new Motor(RA_ELBOW_LOW, RA_ELBOW_HIGH, 34);
	motors.push_back(motorRAE);

	//Motor motorWaist= Motor(WAIST_LOW_VALUE, WAIST_HIGH_VALUE, 43);
	//motors.push_back(motorWaist);
}

int main() {
	//init();

	// Initialize PortHandler instance
  	// Set the port path
  	// Get methods and members of PortHandlerLinux or PortHandlerWindows
  	dynamixel::PortHandler *portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);

  	// Initialize PacketHandler instance
  	// Set the protocol version
  	// Get methods and members of Protocol1PacketHandler or Protocol2PacketHandler
  	dynamixel::PacketHandler *packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
  	
  	int dxl_comm_result = COMM_TX_FAIL;             // Communication result
  	uint8_t dxl_error = 0;                          // Dynamixel error
  	uint16_t dxl_present_position = 0;              // Present position
	uint16_t dxl_current_speed = 40;		// Present moving speed
	bool lowLimit = true;				// For motor physical limitations
	bool motorChosen = false;			// For choosing an initial motor 

	setupMotors();

	// set default motor ID to head
	int dxl_id = 11;

  	// Open port
  	if (portHandler->openPort())
	    printf("Succeeded to open the port!\n");
  	else {
	    printf("Failed to open the port!\n");
	    return 0;
  	}

  	// Set port baudrate
  	if (portHandler->setBaudRate(BAUDRATE)) {
	    printf("Succeeded to change the baudrate!\n");
  	}
  	else {
	    printf("Failed to change the baudrate!\n");
	    return 0;
  	}

	int i = 0;
	Motor *chosen;

  	while(1) {
		while(!motorChosen) {
			displayMenu();
			int i = whichMotor(getch()); 
			for(Iterator = motors.begin(); Iterator != motors.end(); Iterator++) {
				Motor *motor = *Iterator;
				if(motor->getID() == i) {
					chosen = motor;
					dxl_id = chosen->getID();
					break;
				}
			}
			if (i != 0) {
				motorChosen = true;
			}

		}

		dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, dxl_id, ADDR_MX_MOVING_SPEED_L, TEST_MOVEMENT_SPEED, &dxl_error);
	    	
		if (dxl_comm_result != COMM_SUCCESS) {
			packetHandler->printTxRxResult(dxl_comm_result);
		}

		else if (dxl_error != 0) {
			packetHandler->printRxPacketError(dxl_error);
		}
		
  		dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, dxl_id, ADDR_MX_PRESENT_POSITION, &dxl_present_position, &dxl_error);

	    if (dxl_comm_result != COMM_SUCCESS) {
			packetHandler->printTxRxResult(dxl_comm_result);
	    }
	    else if (dxl_error != 0) {
			packetHandler->printRxPacketError(dxl_error);
	    }

		/*JANUARY 2ND CHANGES*/
  		if (!lowLimit) {
			dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, dxl_id, ADDR_MX_GOAL_POSITION, chosen->getLowLimit() % 4096, &dxl_error);
		    if (dxl_comm_result != COMM_SUCCESS) {
				packetHandler->printTxRxResult(dxl_comm_result);
		    }
		    else if (dxl_error != 0) {
				packetHandler->printRxPacketError(dxl_error);
		    }
  		} 
		else {
			dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, dxl_id, ADDR_MX_GOAL_POSITION, chosen->getHighLimit() % 4096, &dxl_error);
		    if (dxl_comm_result != COMM_SUCCESS) {
				packetHandler->printTxRxResult(dxl_comm_result);
		    }
		    else if (dxl_error != 0) {
				packetHandler->printRxPacketError(dxl_error);
		    }		
		}
		
		/*
  		if (value == UP_ASCII_VALUE || value == DOWN_ASCII_VALUE || value == PRINT_ASCII_VALUE) {
  			printf("ID: %d | Present Position: %03d\n", dxl_id, dxl_present_position);
  		}
  		*/
		
		if(chosen->atALimit(dxl_present_position)){
			if (lowLimit)
				dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, dxl_id, ADDR_MX_GOAL_POSITION, (chosen->getLowLimit() % 4096) + 10, &dxl_error);
		    	if (dxl_comm_result != COMM_SUCCESS) {
					packetHandler->printTxRxResult(dxl_comm_result);
		    	}
		    	else if (dxl_error != 0) {
					packetHandler->printRxPacketError(dxl_error);
		    	}
			else{
				dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, dxl_id, ADDR_MX_GOAL_POSITION, (chosen->getHighLimit() % 4096) - 10, &dxl_error);
		    	if (dxl_comm_result != COMM_SUCCESS) {
					packetHandler->printTxRxResult(dxl_comm_result);
		    	}
		   		else if (dxl_error != 0) {
					packetHandler->printRxPacketError(dxl_error);
		   		}	
			}
		}

  		// Might need to fix the logic later for this
		if (chosen->atLowLimit(dxl_present_position))
			lowLimit = true;
		else
			lowLimit = false;


		motorChosen = keepThisMotor();
  	}
	/*JANUARY 2ND CHANGES*/

  	// close port
  	portHandler->closePort();
  	return 0;
}
