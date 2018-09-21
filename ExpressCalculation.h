#pragma once
class ExpressCalculation
{
public:
	double m;	// Expected value
	double D;	// Variance
	double sd;	// Standard deviation
	double n;	// Sample size

	ExpressCalculation();
	~ExpressCalculation();

	void Input(double x);
};

