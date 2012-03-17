#ifndef INMEMORYRECORDER_H
#define INMEMORYRECORDER_H

#include "HeuristicRecorder.h"

#include <vector>

using std::vector;
using std::pair;

class Record {
	public:
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

	const vector<Record> &selections;
	const vector<Record> &rejections;

	private:
	vector<Record> selections_;
	vector<Record> rejections_;
	unsigned int iteration;
};

#endif  // INMEMORYRECORDER_H
