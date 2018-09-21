
// PLTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PLTest.h"
#include "PLTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPLTestDlg 对话框



CPLTestDlg::CPLTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PLTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPLTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPLTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CPLTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_START, &CPLTestDlg::OnBnClickedButtonStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CPLTestDlg::OnBnClickedButtonStop)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CPLTestDlg 消息处理程序

BOOL CPLTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	lh_test = new LHTest();
	lh_test->Init();

	dl = new DrawLine(lh_test);
	test_ena = false;

	SetTimer(1, 10, NULL);		//10ms

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPLTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	} else
	{
		CDialogEx::OnPaint();
		CClientDC dc(this);
		dl->Draw(&dc);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPLTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPLTestDlg::DealTesting(void)
{
	static int update_counter = 0;
	if (test_ena)
	{
		lh_test->PlayOneRound();
		dl->UpdatePPLine();
		if (++update_counter%10==0)
		{
			Invalidate();
		}
	}
}

void CPLTestDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CPLTestDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	test_ena = true;
}


void CPLTestDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	test_ena = false;
}


void CPLTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
		DealTesting();
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

BOOL CPLTestDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GetKeyState(VK_CONTROL)<0)
	{
		if (zDelta == 120)		//向上滚动
		{
			dl->draw_unit -= 100;
			if (dl->draw_unit<100)
			{
				dl->draw_unit = 100;
			}
		}
		if (zDelta == -120)
		{
			dl->draw_unit += 100;
			if (dl->draw_unit>100000)
			{
				dl->draw_unit = 100000;
			}
		}
	} else
	{
		if (GetKeyState(VK_SHIFT)<0)
		{
			if (zDelta == 120)		//向上滚动
			{
				dl->offset.x += 5;
			}
			if (zDelta == -120)
			{
				dl->offset.x -= 5;
			}
		} else
		{
			if (zDelta == 120)		//向上滚动
			{
				dl->offset.y += 5;
			}
			if (zDelta == -120)
			{
				dl->offset.y -= 5;
			}
		}
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
