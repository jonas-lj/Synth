/*
 * Amplifier.h
 *
 *  Created on: Dec 29, 2013
 *      Author: jonas
 */

#ifndef AMPLIFIER_H_
#define AMPLIFIER_H_

#include "Module.h"

class Amplifier: public Module {
public:
	Amplifier(int buffer_size, Module* input, Module* gain);
	Amplifier(int buffer_size, Module* input, double gain);
	virtual ~Amplifier();

public:
	virtual void getOutput(double* signal, int length);

private:
	Module *gain;
	Module *input;
	double *buffer;
};

#endif /* AMPLIFIER_H_ */
