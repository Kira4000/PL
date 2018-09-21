#include "stdafx.h"
#include "DrawLine.h"
#include "Config.h"

DrawLine::DrawLine(LHTest *lh)
{
	offset = CPoint(0, SHOW_H / 2);
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
	if (ppline.empty()) return;

	CPen pen1(PS_SOLID, 1, RGB(0, 0, 255));
	CPen pen2(PS_SOLID, 2, RGB(255, 0, 0));
	CPen pen3(PS_SOLID, 1, RGB(255, 0, 0));
	CPen pen4(PS_SOLID, 1, RGB(0, 255, 0));
	CPen *pOldPen = dc->SelectObject(&pen1);
	//-------------------------------------draw line
	float ppx, ppy;
	dc->MoveTo(offset);
	ppx = offset.x;
	ppy = offset.y;
	for each (auto var in ppline)
	{
		ppx += pp_xgap;
		//y = offset.y + var.mainYL / draw_unit;
		ppy = offset.y - var.mainYL / draw_unit;			//Y轴往下增加，所以加-号
		dc->LineTo(ppx, ppy);
	}
	//-------------------------------------

	//-------------------------------------画0线
	pOldPen = dc->SelectObject(&pen2);
	dc->MoveTo(0, offset.y);
	dc->LineTo(SHOW_W, offset.y);
	//-------------------------------------

	//-------------------------------------画设定盈利线
	pOldPen = dc->SelectObject(&pen3);
	dc->MoveTo(offset);
	ppy = offset.y - ppline.back().setYL / draw_unit;
	dc->LineTo(ppx, ppy);
	//-------------------------------------

#pragma region	-------------------------------------画设区域线
	//u1
	pOldPen = dc->SelectObject(&pen4);
	float tmpY = offset.y - (ppline.front().setYL + lh->pl_param.bd / 4) / draw_unit;
	dc->MoveTo(offset.x, tmpY);
	tmpY = offset.y -(ppline.back().setYL + lh->pl_param.bd / 4) / draw_unit;
	dc->LineTo(ppx, tmpY);

	//u2
	tmpY = offset.y - (ppline.front().setYL + lh->pl_param.bd / 2) / draw_unit;
	dc->MoveTo(offset.x, tmpY);
	tmpY = offset.y - (ppline.back().setYL + lh->pl_param.bd / 2) / draw_unit;
	dc->LineTo(ppx, tmpY);

	//u3
	tmpY = offset.y - (ppline.front().setYL + lh->pl_param.bd *3/ 4) / draw_unit;
	dc->MoveTo(offset.x, tmpY);
	tmpY = offset.y - (ppline.back().setYL + lh->pl_param.bd *3/ 4) / draw_unit;
	dc->LineTo(ppx, tmpY);
	
	//u4
	tmpY = offset.y - (ppline.front().setYL + lh->pl_param.bd) / draw_unit;
	dc->MoveTo(offset.x, tmpY);
	tmpY = offset.y - (ppline.back().setYL + lh->pl_param.bd) / draw_unit;
	dc->LineTo(ppx, tmpY);
	//-------------------------------------
	tmpY = offset.y - (ppline.front().setYL - lh->pl_param.bd / 4) / draw_unit;
	dc->MoveTo(offset.x, tmpY);
	tmpY = offset.y - (ppline.back().setYL - lh->pl_param.bd / 4) / draw_unit;
	dc->LineTo(ppx, tmpY);

	//d2
	tmpY = offset.y - (ppline.front().setYL - lh->pl_param.bd / 2) / draw_unit;
	dc->MoveTo(offset.x, tmpY);
	tmpY = offset.y - (ppline.back().setYL - lh->pl_param.bd / 2) / draw_unit;
	dc->LineTo(ppx, tmpY);

	//d3
	tmpY = offset.y - (ppline.front().setYL - lh->pl_param.bd * 3 / 4) / draw_unit;
	dc->MoveTo(offset.x, tmpY);
	tmpY = offset.y - (ppline.back().setYL - lh->pl_param.bd * 3 / 4) / draw_unit;
	dc->LineTo(ppx, tmpY);

	//d4
	tmpY = offset.y - (ppline.front().setYL - lh->pl_param.bd) / draw_unit;
	dc->MoveTo(offset.x, tmpY);
	tmpY = offset.y - (ppline.back().setYL - lh->pl_param.bd) / draw_unit;
	dc->LineTo(ppx, tmpY);
#pragma endregion


	dc->SelectObject(&pOldPen);
}

void DrawLine::UpdatePPLine(void)
{
	PPlineParam pp;
	pp.mainYL = lh->run_param.zy - lh->run_param.zd;
	pp.setYL = (lh->pl_param.cs / 100.0f)*lh->run_param.zy;
	ppline.push_back(pp);
}
