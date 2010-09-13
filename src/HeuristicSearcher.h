template <typename T>
class CostFunction
{
	public:
	virtual double getCost(T state) const = 0;
};

class CostHeuristic
{
	public:
	virtual int compare(double cost1, double cost2) const = 0;
};

template <typename T>
class NeighborFactory
{
	public:
	virtual T getNeighbor(T state) const = 0;
};

template <typename T>
class HeuristicSearcher {	
	public:
	HeuristicSearcher(const CostFunction<T> &cost_function,
			  const CostHeuristic &cost_heuristic,
			  const NeighborFactory<T> &neighbor_factory,
			  T initial_state):
		cost_function(cost_function),
		cost_heuristic(cost_heuristic),
		neighbor_factory(neighbor_factory),
		current_state(initial_state),
		current_cost(cost_function.getCost(current_state))
		{}

	T best() { return current_state; }
	double bestCost() { return current_cost; }
	void runOnce(void);

	private:
	T current_state;
	double current_cost;

	const CostFunction<T> &cost_function;
	const CostHeuristic &cost_heuristic;
	const NeighborFactory<T> &neighbor_factory;
};

template <typename T>
void HeuristicSearcher<T>::runOnce(void) {
	T neighbor = neighbor_factory.getNeighbor(current_state);
	double neighbor_cost = cost_function.getCost(neighbor);
	if (cost_heuristic.compare(current_cost, neighbor_cost) > 0) {
		current_state = neighbor;
		current_cost = neighbor_cost;
	}
}
