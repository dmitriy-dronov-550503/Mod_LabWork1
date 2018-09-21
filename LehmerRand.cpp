#include "stdafx.h"
#include "LehmerRand.h"

LehmerRand::LehmerRand(float R0, uint32_t A, uint32_t M)
{
	R = R0;
	a = A;
	m = M;
}

double LehmerRand::Rand()
{
	R = fmod(a * R, m);
	return R / m;
}