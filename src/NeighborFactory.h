#ifndef NEIGHBORFACTORY_H
#define NEIGHBORFACTORY_H

template <typename T, typename DIM>
class NeighborFactory
{
	public:
	virtual T getNeighbor(T &state, DIM &dimension) const = 0;
};

#endif
