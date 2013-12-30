/*
 * Controller.h
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Module.h"
#include "../Triggers/Trigger.h"

class Controller : public Module {
public:
	virtual ~Controller() {};

public:
	virtual void getOutput(double* signal, int length) = 0;

public:
	virtual void noteOn(int value) = 0;
	virtual void noteOff(int value) = 0;
};

#endif /* CONTROLLER_H_ */
