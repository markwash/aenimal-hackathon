#ifndef COSTHEURISTIC_H
#define COSTHEURISTIC_H
class CostHeuristic
{
	public:
	virtual int compare(double cost1, double cost2) const = 0;
};
#endif
