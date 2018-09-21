
// PLTestDlg.h : 头文件
//
#include "DrawLine.h"
#include "LHTest.h"

#pragma once

#define XC_LOG(XXX) DrawWithHGE::p_hge->System_Log XXX
#define MBOX_PRINT_USED(XXX) MessageBoxPrint XXX 

// CPLTestDlg 对话框
class CPLTestDlg : public CDialogEx
{
// 构造
public:
	CPLTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	void DealTesting(void);
	LHTest *lh_test;
	DrawLine *dl;
	bool test_ena;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStop();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
