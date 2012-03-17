#include "InMemoryRecorder.h"

unsigned int InMemoryRecorder::iterations(void) const {
	return iteration;
}

void InMemoryRecorder::recordInitial(double cost) {
	if (selections.size() > 0 && selections[0].iteration == 0)
		selections[0].cost = cost;
	else
		selections.insert(selections.begin(), Record(0, cost));
}

void InMemoryRecorder::recordSelection(double cost) {
	iteration++;
	selections.push_back(Record(iteration, cost));
}

void InMemoryRecorder::recordRejection(double cost) {
	iteration++;
	rejections.push_back(Record(iteration, cost));
}
