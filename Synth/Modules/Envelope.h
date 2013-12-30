/*
 * Envelope.h
 *
 *  Created on: Dec 26, 2013
 *      Author: jonas
 */

#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include "Module.h"
#include "../Triggers/Trigger.h"

enum Mode {ATTACK, DECAY, SUSTAIN, RELEASE, OFF};

class Envelope: public Module, public Trigger {
public:
	Envelope(double attack_time,
			double decay_time,
			double sustain_level,
			double release);
	virtual ~Envelope();

public:
    // Implements Module
	virtual void getOutput(double* buffer, int length);

public:
	// Triggers
	virtual void triggerOn(int value);
	virtual void triggerOff(int value);

private:
	//Helpers
	void increment();
	double getValue();

private:
	long phi, attack, decay, release;
	double sustain;
	Mode mode;
};

#endif /* ENVELOPE_H_ */
