#ifndef COSTFUNCTION_H
#define COSTFUNCTION_H

template <typename T>
class CostFunction
{
	public:
	virtual double getCost(T state) const = 0;
};

#endif
