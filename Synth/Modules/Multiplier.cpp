/*
 * FrequencyMultiplier.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#include "Multiplier.h"

Multiplier::Multiplier(Module* input, double multiplier) {
	this->multiplier = multiplier;
	this->input = input;
}

Multiplier::~Multiplier() {
}

void Multiplier::getOutput(double *signal, int length) {
	input->getOutput(signal, length);
	for (int i = 0; i < length; i++)
		signal[i] = signal[i] * multiplier;
}
