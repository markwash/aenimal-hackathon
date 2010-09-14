#ifndef NEIGHBORFACTORY_H
#define NEIGHBORFACTORY_H

template <typename T>
class NeighborFactory
{
	public:
	virtual T getNeighbor(T state) const = 0;
};

#endif
