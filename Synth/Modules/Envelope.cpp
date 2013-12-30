/*
 * Envelope.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: jonas
 */

#include "Envelope.h"
#include <stdio.h>

#define SCALE 44100

Envelope::Envelope(double attack_time, double decay_time, double sustain_level, double release_time) {
	attack = SCALE*attack_time;
	decay = SCALE*decay_time;
	release = SCALE*release_time;
	sustain = sustain_level;
	mode = OFF;
}

Envelope::~Envelope() {
	// TODO Auto-generated destructor stub
}

void Envelope::triggerOn(int value) {
	phi = 0;
	mode = ATTACK;
}

void Envelope::triggerOff(int value) {
	phi = 0;
	mode = RELEASE;
}

void Envelope::getOutput(double *signal, int length) {
	for (int i = 0; i < length; i++) {
		increment();
		signal[i] = getValue();
	}
}

void Envelope::increment() {
	switch (mode) {

	case ATTACK:
		phi++;
		if (phi > attack) {
			phi = 0;
			mode = DECAY;
		}
		break;

	case DECAY:
		phi++;
		if (phi > decay) {
			phi = 0;
			mode = SUSTAIN;
		}
		break;

	case RELEASE:
		phi++;
		if (phi > release) //phi has been reset on trigger off
			mode = OFF;
		break;

	case SUSTAIN:
	case OFF:
		break;
	}
}


/*
 * Attack Decay Sustain Release
 *    /     \    ______
 *   /                     \
 *  /                       \
 */
double Envelope::getValue() {
	switch (mode) {
	case ATTACK:
		return (double) phi / (double) attack;
	case DECAY:
		return ((double) (decay - phi) + sustain * phi) / (double) decay;
	case SUSTAIN:
		return sustain;
	case RELEASE:
		return sustain * (double) (release - phi) / (double) release;
	case OFF:
		return 0.0;
	}
	return 0.0;
}
