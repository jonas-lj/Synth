/*
 * Mixer.cpp
 *
 *  Created on: Dec 26, 2013
 *      Author: jonas
 */

#include "Mixer.h"
#include <stdlib.h>
#include <string.h>

/*
 * Create a new mixer with the given number of channels (starting from 0)
 */
Mixer::Mixer(int buffer_size, int channels) {
	mix_buffer = (double*) malloc(buffer_size * sizeof(double*));

	this->channels = channels;
	inputs = new Module*[channels];
	gain = new double[channels];
}

Mixer::~Mixer() {
	free(mix_buffer);
	delete[] gain;
	delete[] inputs;
}

void Mixer::getOutput(double* buffer, int length) {
	bzero(buffer, sizeof(double) * length);
	for (int i = 0; i < channels; i++) {
		if (inputs[i]) {
			inputs[i]->getOutput(mix_buffer, length);
			for (int j = 0; j < length; j++)
				buffer[j] += gain[i] * mix_buffer[j];
		}
	}
}

void Mixer::addInput(Module *o, int channel, double gain) {
	inputs[channel] = o;
	setGain(channel, gain);
}

void Mixer::setGain(int channel, double gain) {
	this->gain[channel] = gain;
}

