/***************************************************************
*  		 Copyright (C) 2013-2014 XC group. All rights reserved.
*  		 UserName: Administrator
*  		 FileName: PLBase_do.h
*  		 Version: 1.0
*        Description:
	csH------------
	dll_BoDongGap
	cs-------------
	dll_BoDongGap
	csL------------
	dll_BaseLineL==============

	yl = yf - df;
	cs = yl/yf;
	yl = cs*yf;
*        Created by XC at  6/24/2014 23:45:51
****************************************************************/
#pragma once
#include "PLBase.h"
#include "MTRand.h"
#include "Config.h"
#include <list>

typedef struct
{
	float cs;		//抽税率
	LLong bd;		//波动
	LLong dx;		//底线
	UINT32_pl grade; //波动等级
}PLParam;

class PLBase_do : public PLBase
{
public:
	PLBase_do();
	virtual ~PLBase_do();
public:
	virtual std::string GetVision() override;
	virtual void Init(float cs, LLong bd, LLong dx, UINT32_pl grade = 0) override;
	virtual Xarea GetArea(LLong zy, LLong zd, float curveCS = 0) override;
	virtual INT32_pl GetResult(LLong zy, LLong zd) override;
	virtual bool IsHitTheEndline(LLong zy, LLong zd, LLong cur_round_yl) override;
#ifdef FOR_DEBUG
public:
#else
private:
#endif
	void AreaQPush(Xarea area);
	INT32_pl GetTheLatestAreaCnt(void);
	INT32_pl DealPL(void);
	Xarea AreaFindLess(void);
	Xarea AreaFindTargetNearest(void);
	UINT32_pl AreaStayTimes(bool set_or_get = false);
	INT32_pl GetProbability(Xarea now, Xarea tar, INT32_pl latest_cnt);
#ifdef FOR_DEBUG
public:
#else
private:
#endif
	std::list <Xarea> areaq;		//保存每盘的
	std::list <Xarea> areaq_diff;	//保存不同的
	std::list <Xarea> areaq_target;	//保存TARGET的
	PLParam plp;
	Xarea target;
	UINT32_pl area_stay_times;
	LLong last_zy;
	MTRand *mt;
public:
	static PLBase *pInstance;
};


#ifdef FOR_DEBUG
#define DEBUG_PRINTF(XXX) printf(XXX)
#else
#define DEBUG_PRINTF(XXX) do{}while(0)
#endif