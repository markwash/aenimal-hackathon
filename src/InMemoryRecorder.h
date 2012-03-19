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

template <typename DIM>
class InMemoryRecorder: public HeuristicRecorder<DIM> {
	public:
	InMemoryRecorder(void);
	void recordSelection(double cost, const DIM &dimension);
	void recordRejection(double cost, const DIM &dimension);
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

using std::endl;

template <typename DIM>
InMemoryRecorder<DIM>::InMemoryRecorder(void):
	iteration(0),
	selections_(), rejections_(),
	selections(selections_),
	rejections(rejections_)
{}

template <typename DIM>
unsigned int InMemoryRecorder<DIM>::iterations(void) const {
	return iteration;
}

template <typename DIM>
void InMemoryRecorder<DIM>::recordInitial(double cost) {
	if (selections_.size() > 0 && selections_[0].iteration == 0)
		selections_[0].cost = cost;
	else
		selections_.insert(selections_.begin(), Record(0, cost));
}

template <typename DIM>
void InMemoryRecorder<DIM>::recordSelection(double cost,
					    const DIM &dimension) {
	iteration++;
	selections_.push_back(Record(iteration, cost));
}

template <typename DIM>
void InMemoryRecorder<DIM>::recordRejection(double cost,
					    const DIM &dimension) {
	iteration++;
	rejections_.push_back(Record(iteration, cost));
}

template <typename DIM>
void InMemoryRecorder<DIM>::save(ostream &out) const {
	out << iteration << " ";
	out << selections_.size() << " ";
	out << rejections_.size() << endl;
	for (int i = 0; i < selections_.size(); i++) {
		Record record = selections_[i];
		out << record.iteration << " " << record.cost << endl;
	}
	for (int i = 0; i < rejections_.size(); i++) {
		Record record = rejections_[i];
		out << record.iteration << " " << record.cost << endl;
	}
	out.flush();
}

template <typename DIM>
void InMemoryRecorder<DIM>::load(istream &in) {
	int selection_count, rejection_count;
	in >> iteration >> selection_count >> rejection_count;

	selections_ = vector<Record>();
	for (int i = 0; i < selection_count; i++) {
		Record record;
		in >> record.iteration >> record.cost;
		selections_.push_back(record);
	}

	rejections_ = vector<Record>();
	for (int i = 0; i < rejection_count; i++) {
		Record record;
		in >> record.iteration >> record.cost;
		rejections_.push_back(record);
	}
}

#endif  // INMEMORYRECORDER_H
