AM_CPPFLAGS = $(GRAPHICSMAGICK_CFLAGS)

noinst_PROGRAMS = \
	TestHeuristicSearcher \
	TestSimulatedAnnealingHeuristic \
	TestIntegration \
	magick \
	TestCircleImage

TestHeuristicSearcher_SOURCES = \
	TestHeuristicSearcher.cpp

TestHeuristicSearcher_LDFLAGS = -lboost_unit_test_framework-mt

TestSimulatedAnnealingHeuristic_SOURCES = \
	TestSimulatedAnnealingHeuristic.cpp

TestSimulatedAnnealingHeuristic_LDFLAGS = -lboost_unit_test_framework-mt

TestIntegration_SOURCES = \
	TestIntegration.cpp

TestIntegration_LDFLAGS = -lboost_unit_test_framework-mt

magick_SOURCES = \
	magick.cpp

magick_LDADD = $(GRAPHICSMAGICK_LIBS)

TestCircleImage_SOURCES = \
	TestCircleImage.cpp

TestCircleImage_LDFLAGS = -lboost_unit_test_framework-mt
TestCircleImage_LDADD = $(GRAPHICSMAGICK_LIBS)
