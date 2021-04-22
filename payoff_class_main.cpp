#include <iostream>
#include "payoff1.h"
#include <minmax.h>

using namespace std;

int main()
{
	PayOff callPayOff(10.0, PayOff::call);
	PayOff putPayOff(10.0, PayOff::put);
	cout << callPayOff(12.1) <<endl;
	cout << putPayOff(9.8) << endl;
	
	return 0;
}