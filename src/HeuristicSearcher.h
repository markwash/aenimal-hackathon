template <typename T>
class CostFunction
{
	public:
	virtual double getCost(T state) const = 0;
};

class CostHeuristic
{
};

template <typename T>
class NeighborFactory
{
};

template <typename T>
class HeuristicSearcher {	
	public:
	HeuristicSearcher(const CostFunction<T> &cost_function,
			  const CostHeuristic &heuristic,
			  const NeighborFactory<T> &neighbor_factory,
			  T initial_state):
		current_state(initial_state),
		current_cost(cost_function.getCost(current_state))
		{}

	T best() { return current_state; }
	double bestCost() { return current_cost; }

	private:
	T current_state;
	double current_cost;
};
