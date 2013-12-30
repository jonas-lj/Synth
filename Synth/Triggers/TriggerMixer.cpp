/*
 * TriggerMixer.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#include "TriggerMixer.h"

TriggerMixer::TriggerMixer(int channels) {
	this->channels = channels;
	inputs = new Trigger*[channels];
}

TriggerMixer::~TriggerMixer() {
	delete[] inputs;
}

void TriggerMixer::addInput(Trigger *input, int channel) {
	inputs[channel] = input;
}

void TriggerMixer::triggerOn(int value) {
	for (int i = 0; i < channels; i++)
		if (inputs[i])
			inputs[i]->triggerOn(value);
}

void TriggerMixer::triggerOff(int value) {
	for (int i = 0; i < channels; i++)
		if (inputs[i])
			inputs[i]->triggerOff(value);
}
