#ifndef SIMULATEDANNEALINGHEURISTIC_H
#define SIMULATEDANNEALINGHEURISTIC_H

#include "CostHeuristic.h"
#include "SimulatedAnnealingStatistics.h"
#include <cmath>


template <class RNG>
class SimulatedAnnealingHeuristic: public CostHeuristic {
	public:
	SimulatedAnnealingHeuristic(RNG &rng, double temperature):
		rng(rng),
		temperature(temperature)
		{}

	double getTemp(void) const { return temperature; }
	void setTemp(double temperature) { this->temperature = temperature; }

	int compare(double cost1, double cost2);

	const SimulatedAnnealingStatistics statistics(void) const;
	void resetStatistics(void);

	private:
	RNG &rng;
	double temperature;
	SimulatedAnnealingStatistics stats;
};


template <class RNG>
int SimulatedAnnealingHeuristic<RNG>::compare(double cost1, double cost2)
{
	if (cost2 < cost1) {
		stats.registerGreedyAccept();
		return 1;
	}
	else if (exp((cost1 - cost2)/temperature) > rng()) {
		stats.registerSpeculativeAccept();
		return 1;
	}
	else {
		stats.registerReject();
		return -1;
	}
}


template <class RNG>
void SimulatedAnnealingHeuristic<RNG>::resetStatistics(void)
{
	stats = SimulatedAnnealingStatistics();
}


template <class RNG>
const SimulatedAnnealingStatistics
SimulatedAnnealingHeuristic<RNG>::statistics(void) const
{
	return stats;
}
#endif
