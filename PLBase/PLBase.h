#pragma once
#include <string>

#pragma region MyType
typedef long long LLong;
typedef signed char INT8_pl;
typedef unsigned char UINT8_pl;
typedef signed short INT16_pl;
typedef unsigned short UINT16_pl;
typedef signed int INT32_pl;
typedef unsigned int UINT32_pl;
typedef  int64_t INT64_pl;
typedef  uint64_t UINT64_pl;
#pragma endregion

/*	盈利区间说明
Uout
----------------------------
U4
----------------------------
U3
----------------------------
U2
----------------------------
U1
============================
D1
----------------------------
D2
----------------------------
D3
----------------------------
D4
----------------------------
Dout
------------------Endline
*/
enum Xarea	//判断当前盈利处在哪个区间
{
	XareaUout = 0,
	XareaU4,
	XareaU3,
	XareaU2,
	XareaU1,
	XareaD1,
	XareaD2,
	XareaD3,
	XareaD4,
	XareaDout,
	XareaEndline,
	XareaNone,		//没用11
};

class PLBase
{
public:
	virtual std::string GetVision() = 0;
	virtual void Init(float cs, LLong bd, LLong dx, UINT32_pl grade = 0) = 0;
	//curveCS可以做曲线叠加, 普通牌路不需要用这条函数。dll外面可以获取区间做自己的牌路。
	virtual Xarea GetArea(LLong zy, LLong zd, float curveCS = 0) = 0;
	/*
	获取结果。
	return: -100~100;   0:不控制结果。+平台赢 -平台输
	例: 100出一个平台必赢的结果.
	*/
	virtual INT32_pl GetResult(LLong zy, LLong zd) = 0;
	/*
	输入:cur_round_yl: 计算当场盈利，+场地赢， -场地输
	返回:true:直接赢，false:可以出这个结果。
	*/
	virtual bool IsHitTheEndline(LLong zy, LLong zd, LLong cur_round_yl) = 0;
};

extern "C" PLBase* getInstance(void);