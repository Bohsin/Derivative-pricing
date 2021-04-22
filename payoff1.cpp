#include "payoff1.h"
#include <minmax.h>


PayOff::PayOff(double strike_, optionType theOptionType_) :
	strike(strike_), theOptionType(theOptionType_)
{
}

double PayOff::operator() (double spot) const
{
	switch (theOptionType)
	{
	case call: 
		return max(spot - strike, 0);
	case put:
		return max(strike - spot, 0);
	case digitalCall:
		return (spot > strike ? 1 : 0);
	default:
		throw("Unknow option type.");
	}
}
