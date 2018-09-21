#pragma once
#include <vector>
#include "LHTest.h"

typedef struct
{
	long mainYL;
}PPlineParam;

class DrawLine
{
public:
	DrawLine(LHTest *lh);
	~DrawLine();
public:
	void Draw(CClientDC *dc);
	void UpdatePPLine(void);
public:
	std::vector<PPlineParam> ppline;
	CPoint offset;
	float pp_xgap;
	int draw_unit;
private:
	LHTest *lh;
};

