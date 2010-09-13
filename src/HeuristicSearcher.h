template <typename T>
class CostFunction
{
//	double getCost(T state) = 0;
};

template <typename T>
class Collation
{
};

template <typename T>
class HeuristicSearcher {
	private:
	const CostFunction<T> &cost_function;
	public:
	HeuristicSearcher(const CostFunction<T> &cost_function):
		cost_function(cost_function)
		{}
};
