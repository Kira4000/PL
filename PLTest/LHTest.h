#pragma once
#include "../PLBase/MTRand.h"
#include "Config.h"

typedef struct
{
	int credit;
	int zy;
	int zd;
	int round_yf[3];		//×¯ÏÐºÍÑº·Ö
	void Init(void)
	{
		credit = 10000*5;
		zy = 0;
		zd = 0;
		memset(round_yf, 0, sizeof(round_yf));
	}
	void ClearYF(void)
	{
		memset(round_yf, 0, sizeof(round_yf));
	}
	int Bet(int fen, int index)
	{
		if (credit <= 0) return 0;
		if (fen>credit)
			fen = credit;
		credit -= fen;
		zy += fen;
		round_yf[index]+=fen;
		return fen;
	}
}Player;

typedef struct
{
	float cs;
	long long bd;
	long long dx;
	void Init(void)
	{
		cs = 1.0f;
		bd = 30000;
		dx = 50000;
	}
}PLParamT;

typedef struct
{
	long long zy;
	long long zd;
	long round_yf[3];
	void Init(void)
	{
		zy = 0;
		zd = 0;
		memset(round_yf, 0, sizeof(round_yf));
	}
	void ClearYF(void)
	{
		memset(round_yf, 0, sizeof(round_yf));
	}
}RunParam;

class LHTest
{
public:
	LHTest();
	~LHTest();
public:
	void Init(void);
	void PlayOneRound(void);
	Player player[MAX_PLAYER];
	MTRand *random;
private:
	void CountAllYF(void);
	void CountPlayerDF(int res);
public:
	PLParamT pl_param;
	RunParam run_param;
};

