#include <iostream>
#include <random1.h>
#include <kiss.h>
#include <cmath>
#include <payoff1.h>

using namespace std;

double SimpleMonteCarlo1(double Expiry, double Strike, double Spot,
	double Vol, double r, unsigned long NumberOfPaths, kiss_state* vstate);

int main()
{
	/*vstate for random number generator kiss*/
	struct kiss_state* vstate = (struct kiss_state*)malloc(sizeof(struct kiss_state));
	vstate->x = 123456789;
	vstate->y = 987654321;
	vstate->z = 43219876;
	vstate->c = 6543217;
	init_kiss(vstate);

	//input parameters
	double Expiry; //expiry date
	double Strike; //strike price
	double Spot; //current price of underlying asset
	double Vol; //volatility
	double r; //interest rate
	unsigned long NumberOfPaths; //total number of iteration for Monte Carlo simulation
	cout << "\nEnter expiry\n";
	cin >> Expiry;
	cout << "\nEnter strike price\n";
	cin >> Strike;
	cout << "\nEnter current price\n";
	cin >> Spot;
	cout << "\nEnter volatility\n";
	cin >> Vol;
	cout << "\nEnter interest rate\n";
	cin >> r;
	cout << "\nEnter the total number of paths\n";
	cin >> NumberOfPaths;

	double result = SimpleMonteCarlo1(Expiry, Strike, Spot, 
		Vol, r, NumberOfPaths, vstate);
	cout << "the price is " << result << endl;


	/*free vstate: used by random number generator kiss*/
	free(vstate);
	return 0;
}

double SimpleMonteCarlo1(double Expiry, double Strike, double Spot,
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
		double thisPayoff = thisSpot - Strike;
		thisPayoff = (thisPayoff > 0 ? thisPayoff : 0);
		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r * Expiry);
	return mean;

}