#include "stdafx.h"
#include "DrawLine.h"
#include "Config.h"

DrawLine::DrawLine(LHTest *lh)
{
	offset = CPoint(0, SHOW_H/2);
	//ppline.clear();
	pp_xgap = 1;
	draw_unit = 100;
	this->lh = lh;
}


DrawLine::~DrawLine()
{
}

void DrawLine::Draw(CClientDC *dc)
{
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen *pOldPen = dc->SelectObject(&pen);
	//-------------------------------------draw line
	if (!ppline.empty())
	{
		dc->MoveTo(offset);
		float x = offset.x;
		int y = offset.y;
		for each (auto var in ppline)
		{
			x += pp_xgap;
			y = offset.y + var.mainYL/draw_unit;
			dc->LineTo(x, y);
		}
	}
	//-------------------------------------
	dc->SelectObject(&pOldPen);
}

void DrawLine::UpdatePPLine(void)
{
	PPlineParam pp;
	pp.mainYL = lh->run_param.zy- lh->run_param.zd;
	ppline.push_back(pp);
}
