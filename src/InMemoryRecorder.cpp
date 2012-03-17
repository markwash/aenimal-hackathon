#include "InMemoryRecorder.h"

InMemoryRecorder::InMemoryRecorder(void):
	iteration(0),
	selections_(), rejections_(),
	selections(selections_),
	rejections(rejections_)
{}

unsigned int InMemoryRecorder::iterations(void) const {
	return iteration;
}

void InMemoryRecorder::recordInitial(double cost) {
	if (selections_.size() > 0 && selections_[0].iteration == 0)
		selections_[0].cost = cost;
	else
		selections_.insert(selections_.begin(), Record(0, cost));
}

void InMemoryRecorder::recordSelection(double cost) {
	iteration++;
	selections_.push_back(Record(iteration, cost));
}

void InMemoryRecorder::recordRejection(double cost) {
	iteration++;
	rejections_.push_back(Record(iteration, cost));
}
