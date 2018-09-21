
// PLTestScrDlg.h : ͷ�ļ�
//
#include "DrawLine.h"
#include "LHTest.h"

#pragma once


// CPLTestScrDlg �Ի���
class CPLTestScrDlg : public CDialogEx
{
// ����
public:
	CPLTestScrDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLTESTSCR_DIALOG };
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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedButtonAddfen();
	afx_msg void OnDestroy();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonReset();
};
