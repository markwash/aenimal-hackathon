template <typename T>
class CostFunction
{
//	double getCost(T state) = 0;
};

class CostHeuristic
{
};

template <typename T>
class HeuristicSearcher {
	public:
	HeuristicSearcher(const CostFunction<T> &cost_function,
			  const CostHeuristic &heuristic)
		{}
};
