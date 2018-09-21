#include "stdafx.h"
#include "Testing.h"


#define _USE_MATH_DEFINES
#include <math.h>

void Testing::Inderect(vector<double> xs)
{
	// Проверка по косвенным признакам
	double count = 0;

	for (int i = 0; i < xs.size(); i += 2)
	{
		double x12 = pow(xs[i], 2);
		double x22 = pow(xs[i + 1], 2);
		if (x12 + x22 < 1) count++;
	}
	cout << endl << string(50, '*').c_str() << endl;
	cout << "Inderect test results:" << endl;
	cout << "Test result    = " << 2 * count / xs.size() << endl;
	cout << "Expected value = " << M_PI / 4 << endl;
	cout << string(50, '*').c_str() << endl << endl;
}

void Testing::Aperiodic(LehmerRand lr)
{
	vector<double> xs;
	uint32_t V = 1000000;
	LehmerRand lr3 = lr;

	// Step 1
	for (uint32_t i = 0; i < V; i++)
	{
		lr.Rand();
	}
	double xv = lr.Rand();

	// Step 2.1
	while (xv != lr.Rand())
	{
		V++;
	}
	uint32_t i1 = V;
	cout << "Compare i1 at " << i1 << endl;

	double xp;
	// Step 2.2
	while (true)
	{
		xp = lr.Rand();
		if (xv == xp) break;
		V++;
	}
	uint32_t i2 = V;
	cout << "Compare i2 at " << i2 << endl;

	// Период последовательности
	uint32_t P = i2 - i1;
	cout << "Period = " << P << endl;

	uint32_t i3 = 0;
	// Step 3
	while (true)
	{
		double x3 = lr3.Rand();
		if (x3 == xp) break;
		i3++;
	}
	cout << "L = " << i3 + P << endl;
}
