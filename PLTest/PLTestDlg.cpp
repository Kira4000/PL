
// PLTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PLTest.h"
#include "PLTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPLTestDlg �Ի���



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


// CPLTestDlg ��Ϣ�������

BOOL CPLTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	lh_test = new LHTest();
	lh_test->Init();

	dl = new DrawLine(lh_test);
	test_ena = false;

	SetTimer(1, 10, NULL);		//10ms

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPLTestDlg::OnPaint()
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CPLTestDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	test_ena = true;
}


void CPLTestDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	test_ena = false;
}


void CPLTestDlg::OnTimer(UINT_PTR nIDEvent)
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

BOOL CPLTestDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (GetKeyState(VK_CONTROL)<0)
	{
		if (zDelta == 120)		//���Ϲ���
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
			if (zDelta == 120)		//���Ϲ���
			{
				dl->offset.x += 5;
			}
			if (zDelta == -120)
			{
				dl->offset.x -= 5;
			}
		} else
		{
			if (zDelta == 120)		//���Ϲ���
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
