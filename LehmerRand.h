#pragma once
#include <iostream>
using namespace std;

class LehmerRand
{
private:
	static constexpr double cDefaultR = 4294965757;
	static constexpr uint32_t cDefaultA = 4294967279;
	static constexpr uint32_t cDefaultM = 2147483629;

	double R;
	uint32_t a;
	uint32_t m;
public:
	LehmerRand(float R0 = cDefaultR, uint32_t A = cDefaultA, uint32_t M = cDefaultM);
	double Rand();
};

