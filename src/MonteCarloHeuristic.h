class MonteCarloHeuristic {
	public:
	MonteCarloHeuristic():
		temperature(1.0)
		{}

	double getTemp(void) { return temperature; }

	private:
	double temperature;
};
