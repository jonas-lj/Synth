/*
 * MonoController.h
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#ifndef MONOCONTROLLER_H_
#define MONOCONTROLLER_H_

#include "Controller.h"
#include "../Triggers/Trigger.h"
#include "../Misc/FrequencyTable.h"

class MonoController : public Controller {
public:
	MonoController(Trigger *trigger, double portamento, FrequencyTable *table);
	virtual ~MonoController();

public:
	virtual void getOutput(double* signal, int length);

public:
	virtual void noteOn(int value);
	virtual void noteOff(int value);

public:
	void setPortamento(double portamento);

private:
	void loadFrequencies();

private:
	int current_note, old_note;
	double *frequencies;
	bool isOn;
	double portamento, portamento_progress;
	Trigger *trigger;
	FrequencyTable *table;
};

#endif /* MONOCONTROLLER_H_ */
