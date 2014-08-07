// TestPlaySWFDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestPlaySWF.h"
#include "TestPlaySWFDlg.h"
#include ".\testplayswfdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define     WM_ON_START_DIG_TREASURE    WM_USER+5006        //��ʼ�ڱ�

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestPlaySWFDlg �Ի���



CTestPlaySWFDlg::CTestPlaySWFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPlaySWFDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestPlaySWFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestPlaySWFDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_WB, OnBnClickedBtnWb)
	ON_MESSAGE(WM_ON_START_DIG_TREASURE,OnStartDigTreasure)
END_MESSAGE_MAP()


// CTestPlaySWFDlg ��Ϣ�������

BOOL CTestPlaySWFDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	m_DigTreasureGame.Create(IDD_SWF_PLAYER,this);
	m_DigTreasureGame.setParent(this);
	m_DigTreasureGame.MoveWindow(0,0,1,1);
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CTestPlaySWFDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestPlaySWFDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CTestPlaySWFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
LRESULT CTestPlaySWFDlg::OnStartDigTreasure(WPARAM wParam,LPARAM lParam)
{
	OnBnClickedBtnWb();
	return 1L;
}

void CTestPlaySWFDlg::OnBnClickedBtnWb()
{
	FlashData* p =new FlashData;
	p->treasureIndex = 0;
	p->treasureName = "whg";
	p->treasureValue = 1000;
	m_DigTreasureGame.AddFlashData(p);
	CPoint pt;
	//GetCursorPos(&pt);
	CRect rt;
	GetClientRect(&rt);
	ClientToScreen(&rt);
	
	pt.x=rt.left+(rt.Width()-320)/2+100;
	pt.y=rt.top+(rt.Height()-240)/2;
	m_DigTreasureGame.ShowDlg(pt.x - 320,pt.y - 240);
}
