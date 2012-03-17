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
	InMemoryRecorder(void): iteration(0) {}
	void recordSelection(double cost);
	void recordRejection(double cost);
	void recordInitial(double cost);
	unsigned int iterations(void) const;

	vector<Record> selections;
	vector<Record> rejections;

	private:
	unsigned int iteration;
};

#endif  // INMEMORYRECORDER_H
