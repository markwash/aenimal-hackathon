#include "InMemoryRecorder.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestHeuristicSearcher
#include <boost/test/unit_test.hpp>

using namespace std;

struct F {
	F() {}
	InMemoryRecorder recorder;
};

BOOST_FIXTURE_TEST_CASE(test_interface, F)
{
	HeuristicRecorder &h_recorder = recorder;
}

BOOST_FIXTURE_TEST_CASE(test_initial_iterations, F)
{
	BOOST_CHECK_EQUAL(recorder.iterations(), 0);
}

BOOST_FIXTURE_TEST_CASE(test_initial_selections, F)
{
	BOOST_CHECK_EQUAL(recorder.selections.size(), 0);
}

BOOST_FIXTURE_TEST_CASE(test_initial_rejections, F)
{
	BOOST_CHECK_EQUAL(recorder.rejections.size(), 0);
}

BOOST_FIXTURE_TEST_CASE(test_record_initial, F)
{
	recorder.recordInitial(0.0);
	BOOST_CHECK_EQUAL(recorder.selections.size(), 1);
	BOOST_CHECK_EQUAL(recorder.selections[0].iteration, 0);
	BOOST_CHECK_EQUAL(recorder.selections[0].cost, 0.0);
	BOOST_CHECK_EQUAL(recorder.iterations(), 0);
}

BOOST_FIXTURE_TEST_CASE(test_record_initial_overwrites, F)
{
	recorder.recordInitial(0.0);
	recorder.recordInitial(1.0);
	BOOST_CHECK_EQUAL(recorder.selections.size(), 1);
	BOOST_CHECK_EQUAL(recorder.selections[0].iteration, 0);
	BOOST_CHECK_EQUAL(recorder.selections[0].cost, 1.0);
	BOOST_CHECK_EQUAL(recorder.iterations(), 0);
}

BOOST_FIXTURE_TEST_CASE(test_record_initial_after_data_is_okay, F)
{
	recorder.recordSelection(0.0);
	recorder.recordInitial(1.0);
	BOOST_CHECK_EQUAL(recorder.selections.size(), 2);
	BOOST_CHECK_EQUAL(recorder.selections[0].iteration, 0);
	BOOST_CHECK_EQUAL(recorder.selections[0].cost, 1.0);
	BOOST_CHECK_EQUAL(recorder.selections[1].iteration, 1);
	BOOST_CHECK_EQUAL(recorder.selections[1].cost, 0.0);
	BOOST_CHECK_EQUAL(recorder.iterations(), 1);
}

BOOST_FIXTURE_TEST_CASE(test_record_acceptance, F)
{
	recorder.recordSelection(0.0);
	BOOST_CHECK_EQUAL(recorder.selections.size(), 1);
	BOOST_CHECK_EQUAL(recorder.selections[0].cost, 0.0);
	BOOST_CHECK_EQUAL(recorder.selections[0].iteration, 1);
}

BOOST_FIXTURE_TEST_CASE(test_record_multiple_selections, F)
{
	for (int i = 0; i < 3; i++)
		recorder.recordSelection(1.0 * i);
	BOOST_CHECK_EQUAL(recorder.selections.size(), 3);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_EQUAL(recorder.selections[i].cost, 1.0 * i);
		BOOST_CHECK_EQUAL(recorder.selections[i].iteration, i + 1);
	}
}

BOOST_FIXTURE_TEST_CASE(test_record_rejection, F)
{
	recorder.recordRejection(0.0);
	BOOST_CHECK_EQUAL(recorder.rejections.size(), 1);
	BOOST_CHECK_EQUAL(recorder.rejections[0].cost, 0.0);
	BOOST_CHECK_EQUAL(recorder.rejections[0].iteration, 1);
}

BOOST_FIXTURE_TEST_CASE(test_record_multiple_rejections, F)
{
	for (int i = 0; i < 3; i++)
		recorder.recordRejection(1.0 * i);
	BOOST_CHECK_EQUAL(recorder.rejections.size(), 3);
	for (int i = 0; i < 3; i++) {
		BOOST_CHECK_EQUAL(recorder.rejections[i].cost, 1.0 * i);
		BOOST_CHECK_EQUAL(recorder.rejections[i].iteration, i + 1);
	}
}

BOOST_FIXTURE_TEST_CASE(test_mixed_multiple_selection_rejection, F)
{
	for (int i = 0; i < 10; i++)
		if (i % 2 == 0)
			recorder.recordSelection(1.0 * i);
		else
			recorder.recordRejection(1.0 * i);

	BOOST_CHECK_EQUAL(recorder.iterations(), 10);
	BOOST_CHECK_EQUAL(recorder.selections.size(), 5);
	BOOST_CHECK_EQUAL(recorder.rejections.size(), 5);
	for (int i = 0; i < 5; i++) {
		Record selection = recorder.selections[i];
		BOOST_CHECK_EQUAL(selection.iteration, 2 * i + 1);
		BOOST_CHECK_EQUAL(selection.cost, 2.0 * i);
		Record rejection = recorder.rejections[i];
		BOOST_CHECK_EQUAL(rejection.iteration, 2 * i + 2);
		BOOST_CHECK_EQUAL(rejection.cost, 2.0 * i + 1.0);
	}
}
