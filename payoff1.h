#ifndef PAYOFF1_H
#define PAYOFF1_H

class PayOff
{
public:
	enum optionType {call, put};
	//constructor
	PayOff(double strike_, optionType theOptionType_);
	//functions
	double operator() (double spot) const; //return the payoff with the spot price

private:
	double strike;
	optionType theOptionType;


};

#endif // !PAYOFF1_H
