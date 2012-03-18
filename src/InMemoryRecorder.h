#ifndef INMEMORYRECORDER_H
#define INMEMORYRECORDER_H

#include "HeuristicRecorder.h"

#include <iostream>
#include <vector>

using std::istream;
using std::ostream;
using std::vector;

class Record {
	public:
	Record(void):
		iteration(0), cost(0.0) {}
	Record(unsigned int iteration, double cost):
		iteration(iteration), cost(cost) {}
	unsigned int iteration;
	double cost;
};

class InMemoryRecorder: public HeuristicRecorder {
	public:
	InMemoryRecorder(void);
	void recordSelection(double cost);
	void recordRejection(double cost);
	void recordInitial(double cost);
	unsigned int iterations(void) const;
	void save(ostream &out) const;
	void load(istream &in);

	const vector<Record> &selections;
	const vector<Record> &rejections;

	private:
	vector<Record> selections_;
	vector<Record> rejections_;
	unsigned int iteration;
};

#endif  // INMEMORYRECORDER_H
