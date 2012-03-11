#include "SimulatedAnnealingStatistics.h"

unsigned long SimulatedAnnealingStatistics::acceptCount(void) const
{
	return greedy_accept_count + speculative_accept_count;
}

unsigned long SimulatedAnnealingStatistics::totalCount(void) const
{
	return greedy_accept_count + speculative_accept_count
		+ reject_count;
}

double SimulatedAnnealingStatistics::acceptRatio(void) const
{
	unsigned long accept_count = acceptCount();
	if (accept_count == 0)
		return 0.0;
	return 1.0 * acceptCount() / totalCount();
}

double SimulatedAnnealingStatistics::greedyAcceptRatio(void) const
{
	if (greedy_accept_count == 0)
		return 0.0;
	return 1.0 * greedy_accept_count / totalCount();
}

double SimulatedAnnealingStatistics::speculativeAcceptRatio(void) const
{
	if (speculative_accept_count == 0)
		return 0.0;
	return 1.0 * speculative_accept_count / totalCount();
}

double SimulatedAnnealingStatistics::rejectRatio(void) const
{
	if (reject_count == 0)
		return 0.0;
	return 1.0 * reject_count / totalCount();
}
