//
//  Oscilator.cpp
//  Synthesizer
//
//  Created by Jonas Lindstrøm Jensen on 11/11/13.
//  Copyright (c) 2013 Jonas Lindstrøm Jensen. All rights reserved.
//

#include "Oscilator.h"
#include "Constant.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FPS 44100
#define WAVETABLE_RESOLUTION 256

Oscilator::Oscilator(int max_buffer_size, Module* frequency, Module* amplitude) {
	init(max_buffer_size);
	setFrequency(frequency);
	setAmplitude(amplitude);
}

Oscilator::Oscilator(int max_buffer_size, double frequency, double amplitude) {
	init(max_buffer_size);
	setFrequency(new Constant(frequency));
	setAmplitude(new Constant(amplitude));
}

void Oscilator::init(int buffer_size) {
	frequency_buffer = (double*) malloc(buffer_size * sizeof(double));
	bzero(frequency_buffer, buffer_size);

	amplitude_buffer = (double*) malloc(buffer_size * sizeof(double));
	bzero(amplitude_buffer, buffer_size);

    phi = 0.0;
    waveform = SINE;
    loadWaveTable();
}

Oscilator::~Oscilator() {
	free(frequency_buffer);
	free(amplitude_buffer);
	free(wave_table);
}

void Oscilator::loadWaveTable() {
    wave_table = (double*) malloc(WAVETABLE_RESOLUTION * sizeof(double));
    double d = 1.0 / WAVETABLE_RESOLUTION;
    double x = 0.0;
    
    for (int i = 0; i < 256; i++) {
        wave_table[i] = sin(2*M_PI*x);
        x += d;
    }
}

void Oscilator::getOutput(double *output, int length) {
	frequency->getOutput(frequency_buffer, length);
	amplitude->getOutput(amplitude_buffer, length);

    for (int i = 0; i < length; i++) {
        output[i] = getWaveFunctionValue() * amplitude_buffer[i];
        increment(frequency_buffer[i]);
    }
}

/**
 * Increment the state of the oscilator with the given frequency.
 */
void Oscilator::increment(double freq) {
    phi += freq / FPS;
    if (phi > 1.0)
        phi -= 1.0;
}

double Oscilator::getWaveFunctionValue() {
    switch (waveform) {
        case SINE:
            return getSine(phi);
        case SQUARE:
            return getSquare(phi);
        case TRIANGLE:
            return getTriangle(phi);
        case SAW:
            return getSaw(phi);
    }
    return 0.0;
}

void Oscilator::setWaveform(Waveform w) {
    waveform = w;
}

void Oscilator::setFrequency(Module *freq) {
	frequency = freq;
}

void Oscilator::setAmplitude(Module *amp) {
	amplitude = amp;
}

/**
 * For all wave-functions, it is assumed that 0 <= x < 1
 */
double Oscilator::getSine(double x) {
    double sx = x * WAVETABLE_RESOLUTION;
    int ix = (int) sx;
    double fx = sx - ix;
    return wave_table[ix] * (1-fx) + wave_table[ix+1] * fx;
}

double Oscilator::getSquare(double x) {
    return x < 0.5 ? -1.0 : 1.0;
}

double Oscilator::getSaw(double x) {
    return 0.0; //TODO
}

double Oscilator::getTriangle(double x) {
    return 0.0; //TODO
}
