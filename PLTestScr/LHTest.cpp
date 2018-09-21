#include "stdafx.h"
#include "LHTest.h"
#include "../PLBase/MTRand.h"


//#include "../PLCommon/PLCommon.h"
//
//#ifdef _WIN64
//#pragma comment (lib, "../x64/Release/PLCommon.lib")
//#else
//#pragma comment (lib, "../Release/PLCommon.lib")
//#endif


LHTest::LHTest()
{
	random = new MTRand();
	plbase = new PLBase_do();
	file = NULL;
	counter = 0;
}


LHTest::~LHTest()
{
}

void LHTest::Init(void)
{
	CreateTxtFile();
	//---------------------------------------
	for (size_t i = 0; i < MAX_PLAYER; i++)
	{
		player[i].Init();
	}
	pl_param.Init();
	run_param.Init();
	plbase->Init(pl_param.cs, pl_param.bd, pl_param.dx);
#ifdef OUT_CSV
	DDebugPrintf("index,cs,rate,yl,setYL,nowArea,target,cnt\n");
#else
	DDebugPrintf("啊啊啊抽水:%f, 波动:%lld, 底线:%lld\n", pl_param.cs, pl_param.bd, pl_param.dx);
#endif
}

/*---------------------------
概率：
	100|100
	赢 | 输
没算和的结果
----------------------------*/
void LHTest::PlayOneRound(void)
{
	//---------------------------------
	const int unit = 200;
	//player yf
	for (size_t i = 0; i < MAX_PLAYER; i++)
	{
		player[i].ClearYF();
		int yf = player[i].Bet(unit, (random->RandInt(100) < 50) ? 1 : 0);
		if (yf <= 0) continue;
	}

	//count all yf
	CountAllYF();

	//出结果
	int rate = plbase->GetResult(run_param.zy, run_param.zd);
	int win_rate = 100 + rate;		//赢的概率


	//算分
	int win_res = 0;
	if (random->RandInt(200) <= win_rate)
	{
		//win
		if (run_param.round_yf[0] >= run_param.round_yf[1])
			win_res = 1;
		else
			win_res = 0;
	} else
	{
		//lost
		if (run_param.round_yf[0] >= run_param.round_yf[1])
			win_res = 0;
		else
			win_res = 1;
	}

	run_param.zy += run_param.round_yf[0] + run_param.round_yf[1]
		+ run_param.round_yf[2];
	run_param.zd += run_param.round_yf[win_res] * 2;		//2倍
	CountPlayerDF(win_res);
	//------------------------------------------------------
	//DDebugPrintf("index,cs,rate,yl,setYL,nowArea,target,cnt\n");
#ifdef OUT_CSV
	LLong SetYL = (LLong)((pl_param.cs / 100.0f)*run_param.zy);
	float ccs = (float)(run_param.zy - run_param.zd)*100/ run_param.zy;
	DDebugPrintf("%d,%f,%d%%,", counter++, ccs, rate);
	DDebugPrintf("%lld,%lld,", run_param.zy - run_param.zd, SetYL);
	if (plbase->areaq.empty())
	{
		DDebugPrintf("none,%d,%d\n", plbase->target, plbase->GetTheLatestAreaCnt());
	} else
	{
		DDebugPrintf("%d,%d,%d\n", plbase->areaq.front(), plbase->target, plbase->GetTheLatestAreaCnt());
	}
#else
	DDebugPrintf("index[%d]:%d%%   ", test_counter++, rate);
	DDebugPrintf("zy:%lld  zd:%lld  yl:%lld   ", run_param.zy, run_param.zd, run_param.zy - run_param.zd);
	//	DDebugPrintf("zyf:%d xyf:%d  ", run_param.round_yf[0], run_param.round_yf[1]);
	if (plbase->areaq.empty())
	{
		DDebugPrintf("target:%d nowArea:none  cnt:%d\n", plbase->target, plbase->GetTheLatestAreaCnt());
	} else
	{
		DDebugPrintf("target:%d nowArea:%d  cnt:%d\n", plbase->target, plbase->areaq.front(), plbase->GetTheLatestAreaCnt());
	}
#endif
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
		player[i].zd += player[i].round_yf[res] * 2;
	}
}

bool LHTest::IsAllPlayerCreditEmpty(void)
{
	for (size_t i = 0; i < MAX_PLAYER; i++)
	{
		if (player[i].credit > 0)
			return false;
	}
	return true;
}

void LHTest::DDebugPrintf(LPCSTR format, ...)
{
	char buffer[1024];
	va_list arglist;
	va_start(arglist, format);
	vsprintf_s(buffer, sizeof(buffer), format, arglist);
	va_end(arglist);
	//--------------------------------
	if (file)
		file->Write(buffer, strlen(buffer));
	printf(buffer);
}

void LHTest::CreateTxtFile(bool clr)
{
	char buff[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, buff);
	CString csFullPath(buff);
#ifdef OUT_CSV
	csFullPath += "\\debug.csv";
#else
	csFullPath += "\\debug.txt";
#endif

	file = new CFile();
	if (clr)
		file->Open(csFullPath, CFile::modeCreate | CFile::modeWrite);
	else
		file->Open(csFullPath, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	file->SeekToEnd();
}

void LHTest::CloseAndDeleteFile(void)
{
	//lh_test->file->Flush();
	if (file)
	{
		file->Close();
		delete file;
		file = NULL;
	}
}

void LHTest::Reset(void)
{
	counter = 0;
	pl_param.Init();
	run_param.Init();
	for (size_t i = 0; i < MAX_PLAYER; i++)
		player[i].Init();

}