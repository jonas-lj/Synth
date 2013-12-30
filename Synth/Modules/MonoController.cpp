/*
 * MonoController.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#include "MonoController.h"

MonoController::MonoController(Trigger* trigger, double portamento, FrequencyTable *table) {
	setPortamento(portamento);
	this->trigger = trigger;
	current_note = old_note = 45; //middle a
	this->table = table;
}

MonoController::~MonoController() {
}

void MonoController::setPortamento(double portamento) {
	this->portamento = portamento;
}

void MonoController::getOutput(double* signal, int length) {
	for (int i = 0; i < length; i++)
		signal[i] = table->getFrequency(current_note);
}

void MonoController::noteOn(int value) {
	if (trigger) {
		trigger->triggerOff(current_note);
		trigger->triggerOn(value);
	}

	old_note = current_note;
	current_note = value;
}

void MonoController::noteOff(int value) {
	if (trigger && value == current_note)
		trigger->triggerOff(value);
}
