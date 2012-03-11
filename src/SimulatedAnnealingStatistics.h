#ifndef SIMULATEDANNEALINGSTATISTIC_H
#define SIMULATEDANNEALINGSTATISTIC_H

template <class T>
class SimulatedAnnealingHeuristic;

class SimulatedAnnealingStatistics {
	public:
	SimulatedAnnealingStatistics(void):
		greedy_accept_count(0),
		speculative_accept_count(0),
		reject_count(0) {}

	double acceptRatio(void) const;
	double greedyAcceptRatio(void) const;
	double speculativeAcceptRatio(void) const;
	double rejectRatio(void) const; 

	unsigned long acceptCount(void) const;
	unsigned long totalCount(void) const;

	void registerGreedyAccept(void) { greedy_accept_count++; }
	void registerSpeculativeAccept(void) { speculative_accept_count++; }
	void registerReject(void) { reject_count++; }

	private:
	unsigned long greedy_accept_count;
	unsigned long speculative_accept_count;
	unsigned long reject_count;
};


#endif  // SIMULATEDANNEALINGSTATISTIC_H
