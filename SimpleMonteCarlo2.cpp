#include<random1.h>
#include"SimpleMonteCarlo2.h"
#include<cmath>

double SimpleMonteCarlo2(const PayOff& thePayOff , double Expiry, double Spot,
	double Vol, double r, unsigned long NumberOfPaths, kiss_state* vstate)
{
	double variance = Vol * Vol * Expiry;
	double std = sqrt(variance);
	double itoCorrection = -0.5 * variance;

	double movedSpot = Spot * exp(r * Expiry + itoCorrection);
	double thisSpot;
	double runningSum = 0;

	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller(vstate);
		thisSpot = movedSpot * exp(std * thisGaussian);
		double thisPayoff =  thePayOff(thisSpot);
		thisPayoff = (thisPayoff > 0 ? thisPayoff : 0);
		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r * Expiry);
	return mean;

}