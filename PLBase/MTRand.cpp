#include "stdafx.h"
#include "MTRand.h"
//using namespace std;

MTRand::MTRand()
{
	std::random_device rd;
	mt = new std::mt19937(rd());
}


MTRand::~MTRand()
{
	delete mt;
}

int MTRand::RandInt(unsigned int _max)
{
	return (*mt)() % (_max + 1);
}

int MTRand::RandInt(unsigned int _min, unsigned int _max)
{
	if (_max > _max)
		return _min + (*mt)() % (_max - _min + 1);
	else return _max;
}

float MTRand::RandFloat(float _max)
{
	return (float)(RandDblExc() * _max);
}

float MTRand::RandFloat(float _min, float _max)
{
	return _min + RandFloat(_max - _min);
}

double MTRand::RandDblExc(void)
{
	return (double((*mt)()) + 0.5) * (1.0 / 4294967296.0);
}
