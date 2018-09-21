#include "stdafx.h"
#include "StandardCalculation.h"


double StandardCalculation::ExpectedValue(vector<double> xs)
{
	double sum = 0;
	for (int i = 0; i < xs.size(); i++)
	{
		sum += xs[i];
	}

	return sum / xs.size();
}

double StandardCalculation::Variance(vector<double> xs)
{
	float ev = ExpectedValue(xs);
	float sum = 0;

	for (int i = 0; i < xs.size(); i++)
	{
		sum += pow(xs[i] - ev, 2);
	}

	return sum / xs.size();
}