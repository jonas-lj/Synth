/*
 * Delay.h
 *
 *  Created on: Dec 29, 2013
 *      Author: jonas
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "Module.h"

class Delay: public Module {
public:
	//note that repetitions * delay should be smaller than max_delay_time
	Delay(Module* input, double max_delay_time, int repetitions, double delay);
	virtual ~Delay();

public:
	virtual void getOutput(double *signal, int length);

public:
	void setRepetitions(int repetitions);
	void setDelayTime(double delay);

private:
	void updateBuffer(double* newInput, int length);

private:
	Module* input;
	double *buffer;
	long delay_time;
	int repetitions;
	int buffer_size;
	double *repetition_volumes;

};

#endif /* DELAY_H_ */
