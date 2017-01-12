#include "motor.h"

Motor::Motor() {
	// lol
}

Motor::Motor(uint16_t low, uint16_t high, int id){
	position_limit_low = low;
	position_limit_high = high;
	this->id = id;
}

Motor::~Motor(){

}

bool Motor::atLowLimit(uint16_t current){
	if(current == position_limit_low)
		return true;
	else
		return false;
}

int Motor::getID(){
	return id;
}

uint16_t Motor::getLowLimit(){
	return position_limit_low;
}

uint16_t Motor::getHighLimit(){
	return position_limit_high;
}
