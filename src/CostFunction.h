template <typename T>
class CostFunction
{
	public:
	virtual double getCost(T state) const = 0;
};

