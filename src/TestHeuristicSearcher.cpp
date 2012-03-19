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

class MockNeighborFactory: public NeighborFactory<int, int> {
	public:
	void addNeighbor(int state, int neighbor, int dimension=0) {
		pair<int, int> item(neighbor, dimension);
		neighbors[state] = item;
	}
	int getNeighbor(int &state, int &dimension) const {
		pair<int, int> item = neighbors.find(state)->second;
		dimension = item.second;
		return item.first;
	}

	private:
	map< int, pair<int, int> > neighbors;
};

class MockRecord {
	public:
	MockRecord(const char *label, double cost, int dim):
		label(label), cost(cost), dim(dim) {}
	const char *label;
	double cost;
	int dim;
};

class MockHeuristicRecorder: public HeuristicRecorder<int> {
	public:
	void recordSelection(double cost, const int &dim) {
		MockRecord record("Selection", cost, dim);
		records.push_back(record);
	}

	void recordRejection(double cost, const int &dim) {
		MockRecord record("Rejection", cost, dim);
		records.push_back(record);
	}

	vector<MockRecord> records;
};

struct F {
	MockCostFunction cost_function;
	MockCostHeuristic cost_heuristic;
	MockNeighborFactory neighbor_factory;
	MockHeuristicRecorder recorder;
	int initial_state;
	double initial_state_cost;

	HeuristicSearcher<int, int> searcher;

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
	neighbor_factory.addNeighbor(0, 1, 10);
	cost_function.addCost(1, 1.0);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(recorder.records[0].label, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[0].cost, 1.0);
	BOOST_CHECK_EQUAL(recorder.records[0].dim, 10);
}

BOOST_FIXTURE_TEST_CASE(record_selection_higher, F)
{
	neighbor_factory.addNeighbor(0, 1, 1);
	cost_function.addCost(1, 11.0);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(recorder.records[0].label, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[0].cost, 11.0);
	BOOST_CHECK_EQUAL(recorder.records[0].dim, 1);
}

BOOST_FIXTURE_TEST_CASE(record_rejection, F)
{
	neighbor_factory.addNeighbor(0, 1, 1);
	cost_function.addCost(1, 11.0);
	cost_heuristic.setCannedResponse(-1);
	searcher.runOnce();
	BOOST_CHECK_EQUAL(recorder.records[0].label, "Rejection");
	BOOST_CHECK_EQUAL(recorder.records[0].cost, 11.0);
	BOOST_CHECK_EQUAL(recorder.records[0].dim, 1);
}

BOOST_FIXTURE_TEST_CASE(record_multiples, F)
{
	for (int i = 0; i < 5; i++) {
		neighbor_factory.addNeighbor(i, i + 1, i % 2);
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

	BOOST_CHECK_EQUAL(recorder.records[0].label, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[0].cost, 11.0);
	BOOST_CHECK_EQUAL(recorder.records[0].dim, 0);
	BOOST_CHECK_EQUAL(recorder.records[1].label, "Rejection");
	BOOST_CHECK_EQUAL(recorder.records[1].cost, 12.0);
	BOOST_CHECK_EQUAL(recorder.records[1].dim, 1);
	BOOST_CHECK_EQUAL(recorder.records[2].label, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[2].cost, 12.0);
	BOOST_CHECK_EQUAL(recorder.records[2].dim, 1);
	BOOST_CHECK_EQUAL(recorder.records[3].label, "Selection");
	BOOST_CHECK_EQUAL(recorder.records[3].cost, 13.0);
	BOOST_CHECK_EQUAL(recorder.records[3].dim, 0);
	BOOST_CHECK_EQUAL(recorder.records[4].label, "Rejection");
	BOOST_CHECK_EQUAL(recorder.records[4].cost, 14.0);
	BOOST_CHECK_EQUAL(recorder.records[4].dim, 1);
}
