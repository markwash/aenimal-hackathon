class SimulatedAnnealingHeuristic {
	public:
	SimulatedAnnealingHeuristic(double temperature):
		temperature(temperature)
		{}

	double getTemp(void) { return temperature; }
	void setTemp(double temperature) { this->temperature = temperature; }

	int compare(double cost1, double cost2) { return 1; }

	private:
	double temperature;
};
