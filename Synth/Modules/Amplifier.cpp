/*
 * Amplifier.cpp
 *
 *  Created on: Dec 29, 2013
 *      Author: jonas
 */

#include "Amplifier.h"
#include "Constant.h"

Amplifier::Amplifier(int buffer_size, Module* input, Module* gain) {
	this->gain = gain;
	this->input = input;
	buffer = new double[buffer_size];
}

Amplifier::Amplifier(int buffer_size, Module* input, double gain) {
	this->gain = new Constant(gain);
	this->input = input;
	buffer = new double[buffer_size];
}

Amplifier::~Amplifier() {
	delete[] buffer;
}

void Amplifier::getOutput(double* signal, int length) {
	input->getOutput(signal, length);
	gain->getOutput(buffer, length);
	for (int i = 0; i < length; i++)
		signal[i] = signal[i] * buffer[i];
}


