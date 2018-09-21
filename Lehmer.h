#pragma once
#include <iostream>

class Lehmer
{
private:
	const double cDefaultR = 4294965757;
	const uint32_t cDefaultA = 4294967279;
	const uint32_t cDefaultM = 2147483629;

	double R;
	uint32_t a;
	uint32_t m;
public:
	Lehmer();
	~Lehmer();
};

