#include <kiss.h>
#include <random1.h>
#include <iostream>
#include <cmath>
#include <payoff1.h>
#include "SimpleMonteCarlo2.h"

using namespace std;

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

	PayOff callPayOff(Strike, PayOff::call);
	PayOff putPayOff(Strike, PayOff::put);

	double result_call = SimpleMonteCarlo2(callPayOff, Expiry, Spot, Vol, r, NumberOfPaths, vstate);
	cout << "\nThe price of call option is " << result_call << "\n";
	double result_put = SimpleMonteCarlo2(putPayOff, Expiry, Spot, Vol, r, NumberOfPaths, vstate);
	cout << "\nThe price of put option is " << result_put << "\n";

	/*free vstate: used by random number generator kiss*/
	free(vstate);

	return 0;
}