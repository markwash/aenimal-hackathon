class SimulatedAnnealingHeuristic {
	public:
	SimulatedAnnealingHeuristic():
		temperature(1.0)
		{}

	double getTemp(void) { return temperature; }

	private:
	double temperature;
};
