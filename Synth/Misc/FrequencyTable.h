/*
 * FrequencyTable.h
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#ifndef FREQUENCYTABLE_H_
#define FREQUENCYTABLE_H_

class FrequencyTable {
public:
	FrequencyTable();
	virtual ~FrequencyTable();

public:
	double getFrequency(int note);

private:
	double* frequencies;
};

#endif /* FREQUENCYTABLE_H_ */
