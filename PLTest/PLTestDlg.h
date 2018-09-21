
// PLTestDlg.h : ͷ�ļ�
//
#include "DrawLine.h"
#include "LHTest.h"

#pragma once

#define XC_LOG(XXX) DrawWithHGE::p_hge->System_Log XXX
#define MBOX_PRINT_USED(XXX) MessageBoxPrint XXX 

// CPLTestDlg �Ի���
class CPLTestDlg : public CDialogEx
{
// ����
public:
	CPLTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	void DealTesting(void);
	LHTest *lh_test;
	DrawLine *dl;
	bool test_ena;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
