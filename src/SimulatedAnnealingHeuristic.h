class SimulatedAnnealingHeuristic {
	public:
	SimulatedAnnealingHeuristic(double temperature):
		temperature(temperature)
		{}

	double getTemp(void) { return temperature; }
	void setTemp(double temperature) { this->temperature = temperature; }

	private:
	double temperature;
};
