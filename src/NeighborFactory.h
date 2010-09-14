template <typename T>
class NeighborFactory
{
	public:
	virtual T getNeighbor(T state) const = 0;
};

