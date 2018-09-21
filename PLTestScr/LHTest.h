#pragma once
#include "../PLBase/MTRand.h"
#include "../PLBase/PLBase_do.h"
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
}PlayerA;

typedef struct
{
	float cs;
	long long bd;
	long long dx;
	void Init(void)
	{
		cs = PL_CS;
		bd = PL_BD;
		dx = PL_DX;
	}
}PLParamA;

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
}RunParamA;

class LHTest
{
public:
	LHTest();
	~LHTest();
public:
	void Init(void);
	void PlayOneRound(void);
	bool IsAllPlayerCreditEmpty(void);
	void CreateTxtFile(bool clr = true);
	void CloseAndDeleteFile(void);
	void Reset(void);
	PlayerA player[MAX_PLAYER];
	MTRand *random;
private:
	void CountAllYF(void);
	void CountPlayerDF(int res);
	void DDebugPrintf(LPCSTR format, ...);
public:
	PLParamA pl_param;
	RunParamA run_param;
	PLBase_do *plbase;
	CFile *file;
	int counter;
};

