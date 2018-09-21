
// PLTestScrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PLTestScr.h"
#include "PLTestScrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPLTestScrDlg 对话框



CPLTestScrDlg::CPLTestScrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PLTESTSCR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPLTestScrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPLTestScrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CPLTestScrDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CPLTestScrDlg::OnBnClickedButtonStop)
	ON_WM_TIMER()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_ADDFEN, &CPLTestScrDlg::OnBnClickedButtonAddfen)
	ON_WM_DESTROY()
	ON_WM_MBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CPLTestScrDlg::OnBnClickedButtonReset)
END_MESSAGE_MAP()


// CPLTestScrDlg 消息处理程序

BOOL CPLTestScrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	lh_test = new LHTest();
	lh_test->Init();

	dl = new DrawLine(lh_test);
	test_ena = false;

	SetWindowPos(NULL, 1940, 10, 1500, 1050, NULL);
	SetTimer(1, 10, NULL);		//10ms

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPLTestScrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPLTestScrDlg::OnPaint()
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
HCURSOR CPLTestScrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPLTestScrDlg::DealTesting(void)
{
	static int update_counter = 0;
	if (test_ena)
	{
		lh_test->PlayOneRound();
		dl->UpdatePPLine();
		if (++update_counter % 10 == 0)
		{
			Invalidate();
		}
		//如果没分就停止
		if (lh_test->IsAllPlayerCreditEmpty())
		{
			lh_test->CloseAndDeleteFile();
			//写数据
			test_ena = false;
		}
	}
}

void CPLTestScrDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if (lh_test->file == NULL)
		lh_test->CreateTxtFile(false);
	OnBnClickedButtonAddfen();
	test_ena = true;
}

void CPLTestScrDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	test_ena = false;
	lh_test->CloseAndDeleteFile();
}

void CPLTestScrDlg::OnTimer(UINT_PTR nIDEvent)
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

BOOL CPLTestScrDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	bool flag = false;
	if (GetKeyState(VK_CONTROL) < 0)
	{
		if (zDelta == 120)		//向上滚动
		{
			dl->draw_unit -= 10;
			if (dl->draw_unit < 10)
				dl->draw_unit = 10;
		}
		if (zDelta == -120)
		{
			dl->draw_unit += 10;
			if (dl->draw_unit > 1000)
				dl->draw_unit = 1000;
		}
		flag = true;
	}
	if (GetKeyState(VK_SPACE) < 0)
	{
		if (zDelta == 120)		//向上滚动
		{
			dl->pp_xgap += 0.1f;
			if (dl->pp_xgap > 10)
				dl->pp_xgap = 10;
		}
		if (zDelta == -120)
		{
			dl->pp_xgap -= 0.1f;
			if (dl->pp_xgap < 0.1f)
				dl->pp_xgap = 0.1f;
		}
		flag = true;
	}
	if (GetKeyState(VK_SHIFT) < 0)
	{
		if (zDelta == 120)		//向上滚动
			dl->offset.x += 50;
		if (zDelta == -120)
			dl->offset.x -= 50;
		flag = true;
	}
	if (!flag)
	{
		if (zDelta == 120)		//向上滚动
			dl->offset.y += 10;
		if (zDelta == -120)
			dl->offset.y -= 10;
	}
	Invalidate();
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CPLTestScrDlg::OnBnClickedButtonAddfen()
{
	// TODO: 在此添加控件通知处理程序代码
	for (size_t i = 0; i < MAX_PLAYER; i++)
	{
		lh_test->player[i].credit = 10000 * 5;
	}
}


void CPLTestScrDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	lh_test->CloseAndDeleteFile();
}


void CPLTestScrDlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	dl->pp_xgap = 1;
	Invalidate();
	CDialogEx::OnMButtonDown(nFlags, point);
}


void CPLTestScrDlg::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	lh_test->Reset();
	dl->ppline.clear();
	Invalidate();
	OnBnClickedButtonStart();
}
