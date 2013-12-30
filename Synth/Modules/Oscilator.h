//
//  OscilatorImpl.h
//  Synthesizer
//
//  Created by Jonas Lindstrøm Jensen on 12/23/13.
//  Copyright (c) 2013 Jonas Lindstrøm Jensen. All rights reserved.
//

#include "Module.h"

#ifndef Synthesizer_Oscilator_h
#define Synthesizer_Oscilator_h

enum Waveform { SQUARE, SINE, SAW, TRIANGLE };

class Oscilator : public Module {
    
public:
	Oscilator(int max_buffer_size, Module* frequency, Module* amplitude);
	Oscilator(int max_buffer_size, double frequency, double amplitude);
    ~Oscilator();

public:
    // Setters
    void setWaveform(Waveform w);
    void setAmplitude(Module *amp);
    void setFrequency(Module *freq);

public:
    // Implements Module
    virtual void getOutput(double* output, int length);
    
private:
    // Wave functions
    double getSine(double x);
    double getSquare(double x);
    double getSaw(double x);
    double getTriangle(double x);
    
private:
    // Helpers
    void init(int buffer_size);
    void loadWaveTable();
    void increment(double freq);
    double getWaveFunctionValue();
    
private:
    Waveform waveform;
    double phi;
    double *wave_table;
    double *frequency_buffer;
    double *amplitude_buffer;
    
public:
    Module *frequency;
    Module *amplitude;
    
};

#endif
