#ifndef GREEDYHEURISTIC_H
#define GREEDYHEURISTIC_H

#include "CostHeuristic.h"

class GreedyHeuristic: public CostHeuristic
{
	public:
	int compare(double cost1, double cost2) const {
		return cost2 < cost1 ? 1 : -1;
	}
};

#endif
