AM_CPPFLAGS = $(GRAPHICSMAGICK_CFLAGS)

noinst_PROGRAMS = \
	TestHeuristicSearcher \
	TestSimulatedAnnealingHeuristic \
	TestGreedyHeuristic \
	TestIntegration \
	magick \
	runci \
	run-circles \
	display \
	TestCircleImage \
	TestCircleImageNeighborFactory \
	TestImageDrawerCostFunction

TestHeuristicSearcher_SOURCES = \
	TestHeuristicSearcher.cpp

TestHeuristicSearcher_LDFLAGS = -lboost_unit_test_framework-mt

TestSimulatedAnnealingHeuristic_SOURCES = \
	TestSimulatedAnnealingHeuristic.cpp

TestSimulatedAnnealingHeuristic_LDFLAGS = -lboost_unit_test_framework-mt

TestGreedyHeuristic_SOURCES = \
	TestGreedyHeuristic.cpp

TestGreedyHeuristic_LDFLAGS = -lboost_unit_test_framework-mt

TestIntegration_SOURCES = \
	TestIntegration.cpp

TestIntegration_LDFLAGS = -lboost_unit_test_framework-mt

magick_SOURCES = \
	magick.cpp

magick_LDADD = $(GRAPHICSMAGICK_LIBS)

runci_SOURCES = \
	runci.cpp

runci_LDADD = $(GRAPHICSMAGICK_LIBS)

run_circles_SOURCES = \
	run-circles.cpp

run_circles_LDADD = $(GRAPHICSMAGICK_LIBS)

display_SOURCES = \
	display.cpp

display_LDADD = $(GRAPHICSMAGICK_LIBS)

TestCircleImage_SOURCES = \
	TestCircleImage.cpp

TestCircleImage_LDFLAGS = -lboost_unit_test_framework-mt
TestCircleImage_LDADD = $(GRAPHICSMAGICK_LIBS)

TestCircleImageNeighborFactory_SOURCES = \
	TestCircleImageNeighborFactory.cpp

TestCircleImageNeighborFactory_LDFLAGS = -lboost_unit_test_framework-mt
TestCircleImageNeighborFactory_LDADD = $(GRAPHICSMAGICK_LIBS)

TestImageDrawerCostFunction_SOURCES = \
	TestImageDrawerCostFunction.cpp

TestImageDrawerCostFunction_LDFLAGS = -lboost_unit_test_framework-mt
TestImageDrawerCostFunction_LDADD = $(GRAPHICSMAGICK_LIBS)
