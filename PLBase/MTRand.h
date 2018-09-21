#pragma once
#include <random>

class MTRand
{
public:
	MTRand();
	virtual ~MTRand();
public:
	int RandInt(unsigned int _max);
	int RandInt(unsigned int _min, unsigned int _max);
	float RandFloat(float _max);
	float RandFloat(float _min, float _max);
private:
	double RandDblExc(void);
public:
	std::mt19937 *mt;
};

