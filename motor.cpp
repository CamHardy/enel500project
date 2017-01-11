#include "motor.h"

template <class T>
Motor::Motor(T low, T high){
	position_limit_low = low;
	position_limit_high = high;
}

Motor::~Motor(){

}

template <class T>
bool Motor::atALimit(T current){
	if(current == position_limit_low || current == position_limit_high)
		return true;
	else
		return false;
}
