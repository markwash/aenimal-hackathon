class SimulatedAnnealingHeuristic {
	public:
	SimulatedAnnealingHeuristic(double temperature):
		temperature(temperature)
		{}

	double getTemp(void) { return temperature; }

	private:
	double temperature;
};
