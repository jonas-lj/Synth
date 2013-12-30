/*
 * Trigger.h
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#ifndef TRIGGER_H_
#define TRIGGER_H_

class Trigger {

public:
	virtual ~Trigger() {}

public:
	virtual void triggerOn(int value) = 0;
	virtual void triggerOff(int value) = 0;

};

#endif /* TRIGGER_H_ */
