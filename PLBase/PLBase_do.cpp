//Copyright (C) 2013-2014 XC group. All rights reserved.
#include "stdafx.h"
#include "PLBase_do.h"
#include <map>
#include <vector>
#include <algorithm> 

using namespace std;

#define QUEUE_LEN 100
#define QUEUE_LEN_DIFF 50


PLBase *PLBase_do::pInstance = new PLBase_do();

extern "C" PLBase* getInstance(void)
{
#if 0
	if (PLBase_do::pInstance == nullptr)
	{
		pthread_mutex_lock(&mutex);
		if (PLBase_do::pInstance == NULL)
		{
			PLBase_do* ptmp = new PLBase_do();
			PLBase_do::pInstance = ptmp;
		}
		pthread_mutex_unlock(&mutex);
	}
#endif
	return PLBase_do::pInstance;
}

#pragma region 排序
static INT32_pl cmp(pair<Xarea, INT32_pl>& x, pair<Xarea, INT32_pl>& y)
{
	return x.second < y.second;			//小到大
}

static void SortMapByValue(map<Xarea, INT32_pl>& tMap, vector<pair<Xarea, INT32_pl> >& tVector)
{
	for (auto curr = tMap.begin(); curr != tMap.end(); curr++)
		tVector.push_back(make_pair(curr->first, curr->second));
	sort(tVector.begin(), tVector.end(), cmp);
}
#pragma endregion

PLBase_do::PLBase_do()
{
	plp.cs = 0;
	plp.bd = 100000;	//10w
	plp.dx = 0;
	plp.grade = 0;
	target = XareaNone;
	mt = new MTRand();
	area_stay_times = 20;
	last_zy = 0;
}

PLBase_do::~PLBase_do()
{
	delete mt;
}

std::string PLBase_do::GetVision()
{
	char buff[1024];
	string vision = "V1.1";
	sprintf_s(buff, sizeof(buff), "%s\n%s\n", vision.c_str(), __DATE__);
	string strReturn(buff);
	return strReturn;
}

void PLBase_do::Init(float cs, LLong bd, LLong dx, UINT32_pl grade)
{
	plp.cs = cs;
	plp.bd = bd;
	plp.dx = dx;
	plp.grade = grade;
	target = XareaNone;
	areaq.clear();
	areaq_diff.clear();
	areaq_target.clear();
}

Xarea PLBase_do::GetArea(LLong zy, LLong zd, float curveCS)
{
	LLong SetYL = (LLong)(((plp.cs + curveCS) / 100.0f)*zy);
	LLong CurYL = zy - zd;
	//------------------------
	LLong H_YL = SetYL + plp.bd;
	LLong L_YL = SetYL - plp.bd;
	if (CurYL <= plp.dx) return Xarea::XareaEndline;
	if (CurYL > H_YL) return Xarea::XareaUout;
	if (CurYL < L_YL) return Xarea::XareaDout;
	if (CurYL <= SetYL)
	{
		if (CurYL < L_YL + plp.bd / 4) return Xarea::XareaD4;
		else if (CurYL < L_YL + plp.bd / 2) return Xarea::XareaD3;
		else if (CurYL < L_YL + plp.bd * 3 / 4) return Xarea::XareaD2;
		else return Xarea::XareaD1;
	} else
	{
		if (CurYL < SetYL + plp.bd / 4) return Xarea::XareaU1;
		else if (CurYL < SetYL + plp.bd / 2) return Xarea::XareaU2;
		else if (CurYL < SetYL + plp.bd * 3 / 4) return Xarea::XareaU3;
		else return Xarea::XareaU4;
	}
}

INT32_pl PLBase_do::GetResult(LLong zy, LLong zd)
{
	//如果本局没有押分， 就不压area
	if (last_zy == zy) return 0;
	last_zy = zy;
	AreaQPush(GetArea(zy, zd));
	return DealPL();
}

bool PLBase_do::IsHitTheEndline(LLong zy, LLong zd, LLong cur_round_yl)
{
	LLong CurYL = zy - zd + cur_round_yl;
	if (CurYL <= plp.dx) return true;
	return false;
}

//前面压进去， 后面出， 实现队列
void PLBase_do::AreaQPush(Xarea area)
{
	areaq.push_front(area);
	if (areaq.size() > QUEUE_LEN)
		areaq.pop_back();
	//------------------------------
	if (areaq_diff.empty())
	{
		areaq_diff.push_front(area);
	} else
	{
		if (areaq_diff.front() != area)
		{
			areaq_diff.push_front(area);
			if (areaq_diff.size() > QUEUE_LEN_DIFF)
				areaq_diff.pop_back();
		}
	}
}

//获取最新一个状态持续了几次
INT32_pl PLBase_do::GetTheLatestAreaCnt(void)
{
	INT32_pl sum = 0;
	auto first_area = areaq.front();
	for each (auto var in areaq)
	{
		if (first_area == var) sum++;
		else break;
	}
	return sum;
}

INT32_pl PLBase_do::DealPL(void)
{
	INT32_pl ret = 0;
	Xarea now_area = areaq.front();
	INT32_pl latestAreaCnt = 0;
	if (now_area == XareaEndline)
	{
		ret = 100;   //必赢，  已经触碰到底线了。
		target = XareaNone;
		return ret;
	}
	latestAreaCnt = GetTheLatestAreaCnt();
	if (now_area == XareaUout || now_area == XareaDout)
	{
		ret = 70;
		ret += latestAreaCnt * 5;
		if (ret > 100) ret = 100;
		target = XareaNone;
		if (now_area == XareaUout) return (-1 * ret);
		else return ret;
	}
	//-------------------------------------
#if	0
		
#else
	if (target < XareaNone)	//有target
	{
		if (now_area == target)
		{
			target = XareaNone;
			ret = 0;
		} else
		{
			ret = GetProbability(now_area, target, latestAreaCnt);
		}
	} else	//无target		
	{
		//寻找下一个target
		if (latestAreaCnt >= AreaStayTimes())
		{
			target = AreaFindTargetNearest();
			areaq.clear();		//清一下， 再考虑是否清
			AreaStayTimes(true);
		}
		ret = 0;
	}
#endif
	return ret;
}

Xarea PLBase_do::AreaFindLess(void)
{
	INT32_pl counter[XareaNone];
	memset(counter, 0, sizeof(counter));
	for each (auto var in areaq_diff)
		counter[var]++;
	//只选择一下区域
	map<Xarea, INT32_pl> mp;
	vector< pair<Xarea, INT32_pl> > tVector;
	for (int i = XareaU4; i <= XareaD4; i++)
		mp.insert(make_pair((Xarea)i, counter[i]));
	//放到vector里面排序
	SortMapByValue(mp, tVector);
	return tVector[0].first;
}

Xarea PLBase_do::AreaFindTargetNearest(void)
{
	Xarea ret = XareaD1;
	Xarea now = areaq.front();
	Xarea tar = AreaFindLess();
	if (now == tar)
	{
		if (now <= XareaU4) ret = XareaU3;
		else if (now >= XareaD4) ret = XareaD3;
		else
		{
			if (mt->RandInt(99) < 50) ret = (Xarea)(now + 1);
			else ret = (Xarea)(now - 1);
		}
	} else if (now > tar) ret = (Xarea)(now - 1);
	else ret = (Xarea)(now + 1);
	return ret;
}

UINT32_pl PLBase_do::AreaStayTimes(bool set_or_get)
{
	const UINT32_pl MIN_TIMES = 20;
	if (set_or_get)		//set
	{
		area_stay_times = mt->RandInt(MIN_TIMES, MIN_TIMES + 20);	//根据grade来
	} else
	{
		if (area_stay_times < MIN_TIMES)
			area_stay_times = mt->RandInt(MIN_TIMES, MIN_TIMES + 20);	//根据grade来
	}
	return area_stay_times;
}

INT32_pl PLBase_do::GetProbability(Xarea now, Xarea tar, INT32_pl latest_cnt)
{
	INT32_pl dir = 1;
	INT32_pl ret = 0;
	if (now == tar) return 0;
	if (now > tar) dir = 1;		//win
	else dir = -1;				//lost
	ret = mt->RandInt(1, 5) + latest_cnt * 2;		//根据grade来,  决定柔和度
	if (ret > 100) ret = 100;
	return (ret*dir);
}

