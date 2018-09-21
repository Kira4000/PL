
// PLTestScrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PLTestScr.h"
#include "PLTestScrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CPLTestScrDlg �Ի���



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


// CPLTestScrDlg ��Ϣ�������

BOOL CPLTestScrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	lh_test = new LHTest();
	lh_test->Init();

	dl = new DrawLine(lh_test);
	test_ena = false;

	SetWindowPos(NULL, 1940, 10, 1500, 1050, NULL);
	SetTimer(1, 10, NULL);		//10ms

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPLTestScrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	} else
	{
		CDialogEx::OnPaint();
		CClientDC dc(this);
		dl->Draw(&dc);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		//���û�־�ֹͣ
		if (lh_test->IsAllPlayerCreditEmpty())
		{
			lh_test->CloseAndDeleteFile();
			//д����
			test_ena = false;
		}
	}
}

void CPLTestScrDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (lh_test->file == NULL)
		lh_test->CreateTxtFile(false);
	OnBnClickedButtonAddfen();
	test_ena = true;
}

void CPLTestScrDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	test_ena = false;
	lh_test->CloseAndDeleteFile();
}

void CPLTestScrDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bool flag = false;
	if (GetKeyState(VK_CONTROL) < 0)
	{
		if (zDelta == 120)		//���Ϲ���
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
		if (zDelta == 120)		//���Ϲ���
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
		if (zDelta == 120)		//���Ϲ���
			dl->offset.x += 50;
		if (zDelta == -120)
			dl->offset.x -= 50;
		flag = true;
	}
	if (!flag)
	{
		if (zDelta == 120)		//���Ϲ���
			dl->offset.y += 10;
		if (zDelta == -120)
			dl->offset.y -= 10;
	}
	Invalidate();
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CPLTestScrDlg::OnBnClickedButtonAddfen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (size_t i = 0; i < MAX_PLAYER; i++)
	{
		lh_test->player[i].credit = 10000 * 5;
	}
}


void CPLTestScrDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	lh_test->CloseAndDeleteFile();
}


void CPLTestScrDlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	dl->pp_xgap = 1;
	Invalidate();
	CDialogEx::OnMButtonDown(nFlags, point);
}


void CPLTestScrDlg::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	lh_test->Reset();
	dl->ppline.clear();
	Invalidate();
	OnBnClickedButtonStart();
}
