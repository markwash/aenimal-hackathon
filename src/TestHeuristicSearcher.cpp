#include "HeuristicSearcher.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestHeuristicSearcher
#include <boost/test/unit_test.hpp>

#include <cstring>
#include <map>
#include <vector>
using namespace std;

class MockCostFunction: public CostFunction<int> {
	public:
	MockCostFunction(int initial_state, double initial_state_cost) {
		costs[initial_state] = initial_state_cost;
	}
	void addCost(int state, double cost) {
		costs[state] = cost;
	}
	double getCost(int &state) const {
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
	int getNeighbor(int &state) const {
		return neighbors.find(state)->second;
	}

	private:
	map<int, int> neighbors;
};

class MockHeuristicRecorder: public HeuristicRecorder {
	public:
	void recordSelection(double cost) {
		pair<const char *, double> item("Selection", cost);
		records.push_back(item);
	}

	void recordRejection(double cost) {
		pair<const char *, double> item("Rejection", cost);
		records.push_back(item);
	}

	vector<pair<const char *, double> > records;
};

struct F {
	MockCostFunction cost_function;
	MockCostHeuristic cost_heuristic;
	MockNeighborFactory neighbor_factory;
	MockHeuristicRecorder recorder;
	int initial_state;
	double initial_state_cost;

	HeuristicSearcher<int> searcher;

	F():
		initial_state(0),
		initial_state_cost(10.0),
		cost_function(0, 10.0),
		searcher(cost_function, cost_heuristic,
			 neighbor_factory, recorder, initial_state)
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

BOOST_FIXTURE_TEST_CASE(ten_runs, F)
{
	for (int i = 0; i < 10; i++) {
		neighbor_factory.addNeighbor(i, i + 1);
		cost_function.addCost(i + 1, 1.0 * (i + 2));
	}
	for (int i = 0; i < 10; i++) 
		searcher.runOnce();
	BOOST_CHECK_EQUAL(searcher.currentState(), 10);
	BOOST_CHECK_EQUAL(searcher.currentCost(), 11.0);
}


BOOST_FIXTURE_TEST_CASE(dont_go_if_heuristic_says_no, F)
{
	neighbor_factory.addNeighbor(0, 1);
	cost_function.addCost(1, 0.0);
	cost_heuristic.setCannedResponse(-1);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(searcher.currentState(), 0);
	BOOST_CHECK_EQUAL(searcher.currentCost(), 10.0);
}

BOOST_FIXTURE_TEST_CASE(initial_is_best_if_no_runs, F)
{
	BOOST_CHECK_EQUAL(searcher.bestState(), 0);
	BOOST_CHECK_EQUAL(searcher.bestCost(), 10.0);
}

BOOST_FIXTURE_TEST_CASE(save_best_state1, F)
{
	neighbor_factory.addNeighbor(0, 1);
	cost_function.addCost(1, 11.0);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(searcher.currentState(), 1);
	BOOST_CHECK_EQUAL(searcher.currentCost(), 11.0);
	BOOST_CHECK_EQUAL(searcher.bestState(), 0);
	BOOST_CHECK_EQUAL(searcher.bestCost(), 10.0);
}

BOOST_FIXTURE_TEST_CASE(save_best_state2, F)
{
	neighbor_factory.addNeighbor(0, 1);
	cost_function.addCost(1, 1.0);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(searcher.currentState(), 1);
	BOOST_CHECK_EQUAL(searcher.currentCost(), 1.0);
	BOOST_CHECK_EQUAL(searcher.bestState(), 1);
	BOOST_CHECK_EQUAL(searcher.bestCost(), 1.0);
}

BOOST_FIXTURE_TEST_CASE(record_selection, F)
{
	neighbor_factory.addNeighbor(0, 1);
	cost_function.addCost(1, 1.0);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(recorder.records[0].first, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[0].second, 1.0);
}

BOOST_FIXTURE_TEST_CASE(record_selection_higher, F)
{
	neighbor_factory.addNeighbor(0, 1);
	cost_function.addCost(1, 11.0);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(recorder.records[0].first, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[0].second, 11.0);
}

BOOST_FIXTURE_TEST_CASE(record_rejection, F)
{
	neighbor_factory.addNeighbor(0, 1);
	cost_function.addCost(1, 11.0);
	cost_heuristic.setCannedResponse(-1);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(recorder.records[0].first, "Rejection");
	BOOST_CHECK_EQUAL(recorder.records[0].second, 11.0);
}

BOOST_FIXTURE_TEST_CASE(record_multiples, F)
{
	for (int i = 0; i < 5; i++) {
		neighbor_factory.addNeighbor(i, i + 1);
		cost_function.addCost(i + 1, 10.0 + i + 1);
	}

	searcher.runOnce();
	cost_heuristic.setCannedResponse(-1);
	searcher.runOnce();
	cost_heuristic.setCannedResponse(1);
	searcher.runOnce();
	searcher.runOnce();
	cost_heuristic.setCannedResponse(-1);
	searcher.runOnce();

	BOOST_CHECK_EQUAL(recorder.records[0].first, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[0].second, 11.0);
	BOOST_CHECK_EQUAL(recorder.records[1].first, "Rejection");
	BOOST_CHECK_EQUAL(recorder.records[1].second, 12.0);
	BOOST_CHECK_EQUAL(recorder.records[2].first, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[2].second, 12.0);
	BOOST_CHECK_EQUAL(recorder.records[3].first, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[3].second, 13.0);
	BOOST_CHECK_EQUAL(recorder.records[4].first, "Rejection");
	BOOST_CHECK_EQUAL(recorder.records[4].second, 14.0);
}
