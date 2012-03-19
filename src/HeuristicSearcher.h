#ifndef HEURISTICSEARHER_H
#define HEURISTICSEARHER_H

#include "CostFunction.h"
#include "CostHeuristic.h"
#include "HeuristicRecorder.h"
#include "NeighborFactory.h"


template <typename T, typename DIM>
class HeuristicSearcher {	
	public:
	HeuristicSearcher(const CostFunction<T> &cost_function,
			  const CostHeuristic &cost_heuristic,
			  const NeighborFactory<T, DIM> &neighbor_factory,
			  HeuristicRecorder<DIM> &recorder,
			  T &initial_state):
		cost_function(cost_function),
		cost_heuristic(cost_heuristic),
		neighbor_factory(neighbor_factory),
		recorder(recorder),
		current_state(initial_state),
		current_cost(cost_function.getCost(current_state)),
		best_state(initial_state),
		best_cost(current_cost)
		{}

	HeuristicSearcher(const CostFunction<T> &cost_function,
			  const CostHeuristic &cost_heuristic,
			  const NeighborFactory<T, DIM> &neighbor_factory,
			  HeuristicRecorder<DIM> &recorder,
			  T &initial_state, T &best_state):
		cost_function(cost_function),
		cost_heuristic(cost_heuristic),
		neighbor_factory(neighbor_factory),
		recorder(recorder),
		current_state(initial_state),
		current_cost(cost_function.getCost(current_state)),
		best_state(best_state),
		best_cost(cost_function.getCost(best_state))
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
	const NeighborFactory<T, DIM> &neighbor_factory;
	HeuristicRecorder<DIM> &recorder;
};

template <typename T, typename DIM>
void HeuristicSearcher<T, DIM>::runOnce(void) {
	DIM dimension;
	T neighbor = neighbor_factory.getNeighbor(current_state, dimension);
	double neighbor_cost = cost_function.getCost(neighbor);
	if (cost_heuristic.compare(current_cost, neighbor_cost) > 0) {
		recorder.recordSelection(neighbor_cost, dimension);
		current_state = neighbor;
		current_cost = neighbor_cost;
	} else {
		recorder.recordRejection(neighbor_cost, dimension);
	}
	saveCurrentIfBest();
}

template <typename T, typename DIM>
void HeuristicSearcher<T, DIM>::saveCurrentIfBest(void) {
	if (current_cost < best_cost) {
		best_state = current_state;
		best_cost = current_cost;
	}
}

#endif
