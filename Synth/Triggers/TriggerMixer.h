/*
 * TriggerMixer.h
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#ifndef TRIGGERMIXER_H_
#define TRIGGERMIXER_H_

#include "Trigger.h"

class TriggerMixer: public Trigger {
public:
	TriggerMixer(int channels);
	virtual ~TriggerMixer();

public:
	void addInput(Trigger *input, int channel);

public:
	virtual void triggerOn(int value);
	virtual void triggerOff(int value);

private:
	int channels;
	Trigger** inputs;
};

#endif /* TRIGGERMIXER_H_ */
