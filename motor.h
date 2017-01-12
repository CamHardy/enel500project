#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdint.h>

class Motor{
	
private:
	int id;

	uint16_t position_limit_low;
	uint16_t position_limit_high;


	//might have to add speed limits too

public:
	Motor();
	Motor(uint16_t low, uint16_t high, int id);
	~Motor();

	bool atLowLimit(uint16_t current);
	uint16_t getLowLimit();
	uint16_t getHighLimit();
	int getID();
};

#endif
