#ifndef HEURISTICSEARHER_H
#define HEURISTICSEARHER_H

#include "CostFunction.h"
#include "CostHeuristic.h"
#include "NeighborFactory.h"

template <typename T>
class HeuristicSearcher {	
	public:
	HeuristicSearcher(const CostFunction<T> &cost_function,
			  const CostHeuristic &cost_heuristic,
			  const NeighborFactory<T> &neighbor_factory,
			  T initial_state):
		cost_function(cost_function),
		cost_heuristic(cost_heuristic),
		neighbor_factory(neighbor_factory),
		current_state(initial_state),
		current_cost(cost_function.getCost(current_state)),
		best_state(initial_state),
		best_cost(current_cost)
		{}

	T currentState() { return current_state; }
	double currentCost() { return current_cost; }
	T bestState() { return best_state; }
	double bestCost() { return best_cost; }

	void runOnce(void);

	private:

	void saveCurrentIfBest(void);

	T current_state;
	double current_cost;
	T best_state;
	double best_cost;

	const CostFunction<T> &cost_function;
	const CostHeuristic &cost_heuristic;
	const NeighborFactory<T> &neighbor_factory;
};

template <typename T>
void HeuristicSearcher<T>::runOnce(void) {
	T neighbor = neighbor_factory.getNeighbor(current_state);
	double neighbor_cost = cost_function.getCost(neighbor);
	if (cost_heuristic.compare(current_cost, neighbor_cost) > 0) {
		current_state = neighbor;
		current_cost = neighbor_cost;
	}
	saveCurrentIfBest();
}

template <typename T>
void HeuristicSearcher<T>::saveCurrentIfBest(void) {
	if (current_cost < best_cost) {
		best_state = current_state;
		best_cost = current_cost;
	}
}

#endif
