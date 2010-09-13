#include "HeuristicSearcher.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestHeuristicSearcher
#include <boost/test/unit_test.hpp>

#include <map>
using namespace std;

class MockCostFunction: public CostFunction<int> {
	public:
	MockCostFunction(int initial_state, double initial_state_cost) {
		costs[initial_state] = initial_state_cost;
	}
	void addCost(int state, double cost) {
		costs[state] = cost;
	}
	double getCost(int state) const {
		return costs.find(state)->second;
	}

	private:
	map<int, double> costs;
};

class MockCostHeuristic: public CostHeuristic {
	public:
	MockCostHeuristic(): response(1) {}
	void setCannedResponse(int response) {
		this->response = response;
	}
	int compare(double cost1, double cost2) const {
		return response;
	}
	private:
	int response;
};

class MockNeighborFactory: public NeighborFactory<int> {
	public:
	void addNeighbor(int state, int neighbor) {
		neighbors[state] = neighbor;
	}
	int getNeighbor(int state) const {
		return neighbors.find(state)->second;
	}

	private:
	map<int, int> neighbors;
};

struct F {
	MockCostFunction cost_function;
	MockCostHeuristic cost_heuristic;
	MockNeighborFactory neighbor_factory;
	int initial_state;
	double initial_state_cost;

	HeuristicSearcher<int> searcher;

	F():
		initial_state(0),
		initial_state_cost(10.0),
		cost_function(0, 10.0),
		searcher(cost_function, cost_heuristic,
			 neighbor_factory, initial_state)
	{};
	
};

BOOST_FIXTURE_TEST_CASE(initial_is_current_state, F)
{
	BOOST_CHECK_EQUAL(searcher.currentState(), initial_state);
	BOOST_CHECK_EQUAL(searcher.currentCost(), initial_state_cost);
}

BOOST_FIXTURE_TEST_CASE(one_run_goes_to_next_state, F)
{
	neighbor_factory.addNeighbor(0, 1);
	cost_function.addCost(1, 8.0);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(searcher.currentState(), 1);
	BOOST_CHECK_EQUAL(searcher.currentCost(), 8.0);
}
