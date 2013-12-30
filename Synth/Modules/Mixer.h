/*
 * Mixer.h
 *
 *  Created on: Dec 26, 2013
 *      Author: jonas
 */

#ifndef MIXER_H_
#define MIXER_H_

#include <set>
#include "Module.h"

class Mixer: public Module {
public:
	Mixer(int buffer_size, int channels);
	virtual ~Mixer();

public:
    // Implements Module
	virtual void getOutput(double* signal, int length);

public:
	void addInput(Module *o, int channel, double gain);
	void setGain(int channel, double gain);

private:
	int channels;
	double*	mix_buffer;
	Module** inputs;
	double* gain;
};

#endif /* MIXER_H_ */
