#ifndef HEURISTICRECORDER_H
#define HEURISTICRECORDER_H

template <typename DIM>
class HeuristicRecorder {
	public:
	virtual void recordSelection(double cost, const DIM &dim) = 0;
	virtual void recordRejection(double cost, const DIM &dim) = 0;
};

#endif  // HEURISTICRECORDER_H
