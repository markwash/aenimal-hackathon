#ifndef DUMMYHEURISTICRECORDER_H
#define DUMMYHEURISTICRECORDER_H
#include "HeuristicRecorder.h"

class DummyHeuristicRecorder : public HeuristicRecorder {
	public:
	void recordSelection(double cost) {}
	void recordRejection(double cost) {}
};

#endif  // DUMMYHEURISTICRECORDER_H
