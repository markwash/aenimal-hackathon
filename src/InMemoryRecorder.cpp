#include "InMemoryRecorder.h"

using std::endl;

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

void InMemoryRecorder::save(ostream &out) const {
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

void InMemoryRecorder::load(istream &in) {
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
