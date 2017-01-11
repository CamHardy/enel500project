#ifndef MOTOR_H_
#define MOTOR_H_

#include <string>

template<typename T>
class Motor{
	
private:
	String model;
	int id;

	T position_limit_low;
	T position_limit_high;


	//might have to add speed limits too

public:
	Motor(T low, T high);
	~Motor();

	bool atALimit(T current);
}

#endif
