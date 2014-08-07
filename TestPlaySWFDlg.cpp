// TestPlaySWFDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestPlaySWF.h"
#include "TestPlaySWFDlg.h"
#include ".\testplayswfdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define     WM_ON_START_DIG_TREASURE    WM_USER+5006        //开始挖宝

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTestPlaySWFDlg 对话框



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


// CTestPlaySWFDlg 消息处理程序

BOOL CTestPlaySWFDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_DigTreasureGame.Create(IDD_SWF_PLAYER,this);
	m_DigTreasureGame.setParent(this);
	m_DigTreasureGame.MoveWindow(0,0,1,1);
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestPlaySWFDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
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
