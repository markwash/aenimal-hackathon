#include "CostHeuristic.h"

template <class Generator>
class SimulatedAnnealingHeuristic: public CostHeuristic {
	public:
	SimulatedAnnealingHeuristic(Generator gen, double temperature):
		temperature(temperature)
		{}

	double getTemp(void) { return temperature; }
	void setTemp(double temperature) { this->temperature = temperature; }

	int compare(double cost1, double cost2) const { return 1; }

	private:
	double temperature;
};
