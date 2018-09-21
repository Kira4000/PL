#include "stdafx.h"
#include "LHTest.h"
#include "../PLBase/MTRand.h"

#include "../PLCommon/PLCommon.h"

#ifdef _WIN64
#pragma comment (lib, "../x64/Release/PLCommon.lib")
#else
#pragma comment (lib, "../Release/PLCommon.lib")
#endif

LHTest::LHTest()
{
	random = new MTRand();	
}


LHTest::~LHTest()
{
}

void LHTest::Init(void)
{
	for (size_t i = 0; i < MAX_PLAYER; i++)
	{
		player[i].Init();
	}
	pl_param.Init();
	run_param.Init();
	PLCommon_Init(pl_param.cs, pl_param.bd, pl_param.dx);
	printf("抽水:%f, 波动:%lld, 底线:%lld\n", pl_param.cs, pl_param.bd, pl_param.dx);
}

/*---------------------------
概率：
	100|100
	赢 | 输
没算和的结果
----------------------------*/
void LHTest::PlayOneRound(void)
{
	static int test_counter = 0;
	//---------------------------------
	const int unit = 200;
	//player yf
	for (size_t i = 0; i < MAX_PLAYER; i++)
	{
		player[i].ClearYF();
		int yf = player[i].Bet(unit, (random->RandInt(100) < 50)?1:0);
		if (yf <= 0) continue;
	}
	//count all yf
	CountAllYF();

	//出结果
	int rate = PLCommon_GetResult(run_param.zy, run_param.zd);
	int win_rate = 100 + rate;		//赢的概率

	printf("index[%d]:%d%%   zy:%d  zd:%d\n", test_counter++, rate, run_param.zy, run_param.zd);

	//算分
	int win_res = 0;
	if (random->RandInt(200) <= win_rate)
	{
		//win
		if (run_param.round_yf[0]>= run_param.round_yf[1])
			win_res = 0;
		else
			win_res = 1;
	} else
	{
		//lost
		if (run_param.round_yf[0] >= run_param.round_yf[1])
			win_res = 1;
		else
			win_res = 0;
	}

	run_param.zy += run_param.round_yf[0] + run_param.round_yf[1]
		+ run_param.round_yf[2];
	run_param.zd += run_param.round_yf[win_res] * 2;		//2倍
	CountPlayerDF(win_res);
}

void LHTest::CountAllYF(void)
{
	run_param.ClearYF();
	for (size_t i = 0; i < MAX_PLAYER; i++)
	{
		run_param.round_yf[0] += player[i].round_yf[0];
		run_param.round_yf[1] += player[i].round_yf[1];
		run_param.round_yf[2] += player[i].round_yf[2];
	}
}

void LHTest::CountPlayerDF(int res)
{
	for (size_t i = 0; i < MAX_PLAYER; i++)
	{
		player[i].zd += player[i].round_yf[res]*2;
	}
}