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
int dxl_ID[15] = {11, 12, 21, 22, 23, 24, 26, 31, 32, 33, 34, 36, 41, 42, 43};                   // Dynamixel ID: 1
#define BAUDRATE                        1000000
#define DEVICENAME                      "/dev/ttyUSB0"      // Check which port is being used on your controller
                                                            // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0"

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque
#define DXL_MINIMUM_POSITION_VALUE      0                 // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE      4095                // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)

#define TEST_MOVEMENT_SPEED 		20
#define DXL_MOVING_STATUS_THRESHOLD     5                  // Dynamixel moving status threshold

#define UP_ASCII_VALUE                 0x77
#define DOWN_ASCII_VALUE				0x73
#define PRINT_ASCII_VALUE				0x7a
int i = 0;

int getch() {
#ifdef __linux__
  	struct termios oldt, newt;
  	int ch;
  	tcgetattr(STDIN_FILENO, &oldt);
  	newt = oldt;
  	newt.c_lflag &= ~(ICANON | ECHO);
  	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  	ch = getchar();
  	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  	return ch;
#elif defined(_WIN32) || defined(_WIN64)
  	return _getch();
#endif
}

using namespace std;

int main() {
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
	bool lowLimit = false;				// 

  	// Open port
  	if (portHandler->openPort())
  	{
	    	printf("Succeeded to open the port!\n");
  	}
  	else
  	{
	    	printf("Failed to open the port!\n");
	    	return 0;
  	}

  	// Set port baudrate
  	if (portHandler->setBaudRate(BAUDRATE))
  	{
	    	printf("Succeeded to change the baudrate!\n");
  	}
  	else
  	{
	    	printf("Failed to change the baudrate!\n");
	    	return 0;
  	}

	dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, dxl_ID[i], ADDR_MX_MOVING_SPEED_L, TEST_MOVEMENT_SPEED, &dxl_error);
	    	
	if (dxl_comm_result != COMM_SUCCESS){
		packetHandler->printTxRxResult(dxl_comm_result);
	}

	else if (dxl_error != 0){
		packetHandler->printRxPacketError(dxl_error);
	}

  	while(1) {
  		// read present position
		/*  		
		int value = getch();
      		if (value == UP_ASCII_VALUE)
  			i++;
  		if (value == DOWN_ASCII_VALUE)
  			i--;
  		//i = abs(i%15);
		*/
		//test
		whichMotor(i); 
  		
  		dxl_comm_result = packetHandler->read2ByteTxRx(portHandler, dxl_ID[i], ADDR_MX_PRESENT_POSITION, &dxl_present_position, &dxl_error);
	    	if (dxl_comm_result != COMM_SUCCESS)
	      	{
			packetHandler->printTxRxResult(dxl_comm_result);
	      	}
	      	else if (dxl_error != 0)
	      	{
			packetHandler->printRxPacketError(dxl_error);
	      	}
		/*JANUARY 2ND CHANGES*/
  		if (!lowLimit){
			dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, dxl_ID[i], ADDR_MX_GOAL_POSITION, HEAD_MOTOR_LOW_VALUE, &dxl_error);
		    	if (dxl_comm_result != COMM_SUCCESS)
		      	{
				packetHandler->printTxRxResult(dxl_comm_result);
		      	}
		      	else if (dxl_error != 0)
		      	{
				packetHandler->printRxPacketError(dxl_error);
		      	}
  		}
		else{
			dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, dxl_ID[i], ADDR_MX_GOAL_POSITION, HEAD_MOTOR_HIGH_VALUE, &dxl_error);
		    	if (dxl_comm_result != COMM_SUCCESS)
		      	{
				packetHandler->printTxRxResult(dxl_comm_result);
		      	}
		      	else if (dxl_error != 0)
		      	{
				packetHandler->printRxPacketError(dxl_error);
		      	}		
		}
		

  		if (value == UP_ASCII_VALUE || value == DOWN_ASCII_VALUE || value == PRINT_ASCII_VALUE) {
  			printf("ID: %d | Present Position: %03d\n", dxl_ID[i], dxl_present_position);
  		}

		if (dxl_present_position == HEAD_MOTOR_LOW_VALUE)
			lowLimit = true;
		else
			lowLimit = false;
  	}
	/*JANUARY 2ND CHANGES*/

  	// close port
  	portHandler->closePort();
  	return 0;
}



/* Broken code; mainly just used for testing for now */
void whichMotor(int &value){

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

	value = getch();	
}


void init(){

} 
