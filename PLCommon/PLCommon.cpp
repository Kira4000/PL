// PLCommon.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "PLCommon.h"
//#include <cstdio>

#include "../PLBase/PLBase.h"
#ifdef _WIN64		//64
#pragma comment (lib, "../x64/Release/PLBase.lib")
#else
#pragma comment (lib, "../Release/PLBase.lib")
#endif

#if 0
// 这是导出变量的一个示例
PLCOMMON_API int nPLCommon=0;

// 这是导出函数的一个示例。
PLCOMMON_API int fnPLCommon(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 PLCommon.h
CPLCommon::CPLCommon()
{
    return;
}
#endif


PLBase *pl = nullptr;

PLCOMMON_API void PLCommon_Init(float cs, LLong bd, LLong dx)
{
	if (pl == nullptr) pl = getInstance();
	pl->Init(cs, bd, dx);
}

PLCOMMON_API INT32_pl PLCommon_GetResult(LLong zy, LLong zd)
{
	return pl->GetResult(zy, zd);
}

PLCOMMON_API bool IsHitTheEndline(LLong zy, LLong zd, LLong cur_round_yl)
{
	return pl->IsHitTheEndline(zy, zd, cur_round_yl);
}