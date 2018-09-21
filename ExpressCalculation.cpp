#include "stdafx.h"
#include "ExpressCalculation.h"
#include <cmath>

ExpressCalculation::ExpressCalculation()
{
	m = 0.5;
	D = 0;
	sd = 0;
	n = 3;
}


ExpressCalculation::~ExpressCalculation()
{
}

void ExpressCalculation::Input(double x)
{
	D = (D * ((n - 2) / (n - 1))) + ((1 / n) * pow(x - m, 2));
	m = (m * ((n - 1) / n)) + (x / n);
	n++;
}

