/*
 * Delay.cpp
 *
 *  Created on: Dec 29, 2013
 *      Author: jonas
 */

#include "Delay.h"
#include <string.h>

#define SCALE 44100

// Make sure that max_delay_time > repetitions*delay
Delay::Delay(Module* input, double max_delay_time, int repetitions, double delay) {
	this->input = input;
	this->repetitions = repetitions;
	this->delay_time = delay * SCALE;
	this->buffer_size = SCALE*max_delay_time;
	buffer = new double[buffer_size];
	bzero(buffer, buffer_size);

	// For now, the volumes decreases linear
	repetition_volumes = new double[repetitions];
	for (int i = 0; i < repetitions; i++)
		repetition_volumes[i] = (double) (repetitions - i) / (double) repetitions;

}

Delay::~Delay() {
	delete[] buffer;
	delete[] repetition_volumes;
}

//TODO: Make this work...
void Delay::getOutput(double *signal, int length) {
	input->getOutput(signal, length);
	updateBuffer(signal, length);
	for (int i = 0; i < length; i++) {
		for (int r = 1; r < repetitions; r++) {
			double delay_contribution = repetition_volumes[r] * buffer[i + r*delay_time];
			signal[i] += delay_contribution;
		}
	}
}

void Delay::updateBuffer(double *signal, int length) {
	for (int i = length; i < buffer_size; i++)
		buffer[i] = buffer[i-length];
	for (int i = 0; i < length; i++)
		buffer[i] = signal[i];
}
