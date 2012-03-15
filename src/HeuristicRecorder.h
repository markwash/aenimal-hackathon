#ifndef HEURISTICRECORDER_H
#define HEURISTICRECORDER_H

class HeuristicRecorder {
	public:
	virtual void recordSelection(double cost) = 0;
	virtual void recordRejection(double cost) = 0;
};

#endif  // HEURISTICRECORDER_H
