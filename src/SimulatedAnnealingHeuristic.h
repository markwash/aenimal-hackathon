#ifndef SIMULATEDANNEALINGHEURISTIC_H
#define SIMULATEDANNEALINGHEURISTIC_H

#include "CostHeuristic.h"
#include <cmath>

template <class RNG>
class SimulatedAnnealingHeuristic: public CostHeuristic {
	public:
	SimulatedAnnealingHeuristic(RNG &rng, double temperature):
		rng(rng),
		temperature(temperature)
		{}

	double getTemp(void) { return temperature; }
	void setTemp(double temperature) { this->temperature = temperature; }

	int compare(double cost1, double cost2) const;

	private:
	RNG &rng;
	double temperature;
};

template <class RNG>
int SimulatedAnnealingHeuristic<RNG>::compare(double cost1, double cost2) const {
	if (cost2 < cost1) 
		return 1;
	else if (exp((cost1 - cost2)/temperature) > rng())
		return 1;
	else
		return -1;
}
#endif
