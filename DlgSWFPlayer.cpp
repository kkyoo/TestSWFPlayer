// DlgDlgTreasure.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgSWFPlayer.h"
#define WND_W		640
#define WND_H		480

// CDlgDlgTreasure 对话框

IMPLEMENT_DYNAMIC(CDlgSWFPlayer, CDialog)
CDlgSWFPlayer::CDlgSWFPlayer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSWFPlayer::IDD, pParent)
{
	m_flashVect.clear();
	m_bIsPlaying=false;
	m_pFlashWidget=NULL;
	m_hMemDC=NULL;
	m_pParent=NULL;
	m_curFlashData=NULL;
	m_CurGameState = STATE_NULL;
	m_hMemDCEx= NULL;
	m_bPaint = TRUE;
}

CDlgSWFPlayer::~CDlgSWFPlayer()
{
	if(m_pFlashWidget)
	{
		delete m_pFlashWidget;
		m_pFlashWidget = NULL;
	}
}

void CDlgSWFPlayer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSWFPlayer, CDialog)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_NEW_GAME, OnBnClickedBtnNewGame)
	ON_BN_CLICKED(IDC_BTN_EXIT_GAME, OnBnClickedBtnExitGame)
END_MESSAGE_MAP()



void CDlgSWFPlayer::AddFlashData(FlashData* p)
{
	m_flashVect.push_back(p);
	if (!m_bIsPlaying)
	{
		m_bIsPlaying=true;
		SetTimer(11,100,NULL);
	}
}
// CDlgDlgTreasure 消息处理程序
BOOL CDlgSWFPlayer::OnInitDialog()
{
	CDialog::OnInitDialog();

	//RemoveWindowSkin(m_hWnd);

	//加入WS_EX_LAYERED扩展属性
	SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
		GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	HINSTANCE hInst = LoadLibrary("User32.DLL"); 
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC fun = NULL;
		//取得SetLayeredWindowAttributes函数指针 
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)fun(this->GetSafeHwnd(),RGB(240,240,240),128,1); 
		FreeLibrary(hInst); 
	}


	HDC hDC = ::GetDC(m_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	// vietdoor's code start here
	::SetMapMode(m_hMemDC, MM_TEXT);
	// vietdoor's code end here

	::SetBkColor(m_hMemDC,RGB(255,255,255));
	::SetBkMode(m_hMemDC,TRANSPARENT);

	m_hMemDCEx = CreateCompatibleDC(hDC);
	::SetMapMode(m_hMemDCEx, MM_TEXT);
	// vietdoor's code end here

	::SetBkColor(m_hMemDCEx,RGB(255,255,255));
	::SetBkMode(m_hMemDCEx,TRANSPARENT);

	BITMAPINFO bmpinfo;
	memset(&bmpinfo,0, sizeof(bmpinfo));
	bmpinfo.bmiHeader.biSize = sizeof(bmpinfo);
	bmpinfo.bmiHeader.biPlanes = 1;
	bmpinfo.bmiHeader.biBitCount = 32;
	bmpinfo.bmiHeader.biCompression = BI_RGB;
	bmpinfo.bmiHeader.biWidth = WND_W;
	bmpinfo.bmiHeader.biHeight = -WND_H;
	void* pBuffer = NULL;

	SelectObject(m_hMemDCEx,CreateDIBSection(m_hMemDCEx, &bmpinfo, DIB_RGB_COLORS, &pBuffer, NULL, 0) );
	SelectObject(m_hMemDC,CreateDIBSection(m_hMemDC, &bmpinfo, DIB_RGB_COLORS, &pBuffer, NULL, 0) );
	::ReleaseDC(m_hWnd,hDC);

	m_pFlashWidget = new FlashPlayer;
	string strr=GetFullPath("flash000001.swf");
	if (m_pFlashWidget)
	{
		//m_pFlashWidget->StartAnimation(strr,WND_W,WND_H,m_hWnd);
		//m_pFlashWidget->SetLoop(TRUE);
		m_pFlashWidget->SetQuality(FlashPlayer::QUALITY_HIGH);
		//SetTimer(10,800,NULL);
	}
	// 	m_pFlashWidget->StartAnimation(str,WND_W,WND_H,m_hWnd);

	// 	SetTimer(10,50,NULL);

	//SetButtonSkin(GetDlgItem(IDC_BTN_NEW_GAME)->GetSafeHwnd(),"Button_zlyj");
	//SetButtonSkin(GetDlgItem(IDC_BTN_EXIT_GAME)->GetSafeHwnd(),"Button_tch");//137 33
	GetDlgItem(IDC_BTN_NEW_GAME)->MoveWindow(20,440,137,33);
	GetDlgItem(IDC_BTN_EXIT_GAME)->MoveWindow(350,440,137,33);
	return TRUE;
}


void CDlgSWFPlayer::OnTimer(UINT nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (10==nIDEvent)
	{
		if (m_pFlashWidget)
		{
			m_pFlashWidget->Update();
			if(m_pFlashWidget->IsRender())
			{
				LONG nWidth,nHeight;
				m_pFlashWidget->GetFlashSize(&nWidth,&nHeight);

				//SelectObject(g_hTempDC,g_hBitmapFlashBack);
				//BitBlt(g_hMemDC,0,0,nWidth,nHeight,g_hTempDC,0,0,SRCCOPY);

				// 绘制FLASH到后台缓冲DC
				m_pFlashWidget->Render(m_hMemDC,/*FALSE*/TRUE);

				// 绘制到窗口
				HDC dc = ::GetDC(m_hWnd);
				BitBlt(dc,0,0,nWidth,nHeight,m_hMemDC,0,0,SRCCOPY);
				::ReleaseDC(m_hWnd,dc);
			}
		}
		if (m_pFlashWidget && !m_pFlashWidget->IsPlaying())
		{
			m_pFlashWidget->Stop();
			KillTimer(10);
		}
	}
	else if (nIDEvent == 11)
	{
		KillTimer( 11);
		ShowFlash();
	}
	else if (nIDEvent == 12)
	{
		KillTimer(12);
		StartPlayCurFlash();
		SetTimer(13,100,NULL);
	}
	else if (nIDEvent == 13)
	{
		if ( m_pFlashWidget && !m_pFlashWidget->IsPlaying())
		{
			m_bPaint = FALSE;
			delete m_curFlashData;
			m_curFlashData=NULL;
			m_pFlashWidget->Stop();
			m_CurGameState = STATE_OVER;
			KillTimer(13);
			//ShowFlash();
			//::PostMessage(CKTVDlg::getInstance().m_hWnd,WM_USER+5007,0,NULL);
			//GetDlgItem(IDC_BTN_NEW_GAME)->ShowWindow(SW_SHOWNA);
			//GetDlgItem(IDC_BTN_EXIT_GAME)->ShowWindow(SW_SHOWNA);
			//OnBnClickedBtnExitGame();

 			LONG nWidth,nHeight;
 			m_pFlashWidget->GetFlashSize(&nWidth,&nHeight);
 
 			HDC dc = ::GetDC(m_hWnd);
 			BitBlt(dc,0,0,nWidth,nHeight,m_hMemDCEx,0,0,SRCCOPY);
 			::ReleaseDC(m_hWnd,dc);

			delete m_pFlashWidget;
			m_pFlashWidget = NULL;

			GetDlgItem(IDC_BTN_NEW_GAME)->ShowWindow(SW_SHOWNA);
			GetDlgItem(IDC_BTN_EXIT_GAME)->ShowWindow(SW_SHOWNA);

			//SetTimer(14,100,NULL);
		}
		else if (m_pFlashWidget)
		{
			//m_bPaint = TRUE;
			m_pFlashWidget->Update();
			if(m_pFlashWidget->IsRender())
			{
				LONG nWidth,nHeight;
				m_pFlashWidget->GetFlashSize(&nWidth,&nHeight);

				//SelectObject(g_hTempDC,g_hBitmapFlashBack);
				//BitBlt(g_hMemDC,0,0,nWidth,nHeight,g_hTempDC,0,0,SRCCOPY);

				// 绘制FLASH到后台缓冲DC
				COLORREF cr=RGB(240,240,240);
				m_pFlashWidget->Render(m_hMemDC,/*FALSE*/TRUE,cr);

				static index =0;
				if (index++%2==0)
				{
					m_pFlashWidget->Render(m_hMemDCEx,/*FALSE*/TRUE,cr);
				}
				/*int i=m_pFlashWidget->GetCurrentFrame();
				char buf[64];
				sprintf(buf,"%d,%d,%d\n",i,m_pFlashWidget->GetTotalFrames(),m_pFlashWidget->GetFrameNum());
				TRACE(buf);*/

				// 绘制到窗口
				HDC dc = ::GetDC(m_hWnd);
				BitBlt(dc,0,0,nWidth,nHeight,m_hMemDC,0,0,SRCCOPY);
				::ReleaseDC(m_hWnd,dc);
			}
		}
		
	}else if(nIDEvent == 14)
	{
		KillTimer(14);
		GetDlgItem(IDC_BTN_NEW_GAME)->ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_BTN_EXIT_GAME)->ShowWindow(SW_SHOWNA);
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgSWFPlayer::ShowFlash()
{
	if (m_flashVect.size()>0)
	{
		m_curFlashData=m_flashVect.at(0);
		m_flashVect.erase(m_flashVect.begin());
		SetTimer(12,100,NULL);


		if (/*!(CKTVDlg::getInstance().GetSizeStatusTopKTV()==2)*/TRUE)
		{
			ShowWindow(SW_SHOWNA);
			GetDlgItem(IDC_BTN_NEW_GAME)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_BTN_EXIT_GAME)->ShowWindow(SW_HIDE);
		}
		else
		{
			ShowWindow(SW_HIDE);
		}
	}
	else
	{
		m_bIsPlaying=false;
		ShowWindow(SW_HIDE);
	}
	return;
}

void CDlgSWFPlayer::StartPlayCurFlash()
{
	if (m_curFlashData)
	{
		m_CurGameState = STATE_DIG;
		uint32 goodsid=m_curFlashData->treasureIndex;
		CString flashName = "wb.swf";
		//flashName.Format("flash%06d.swf",goodsid);
		
		ChangeFlash(flashName,1);
	}
	return;
}

VOID CDlgSWFPlayer::ChangeFlash(const char* str,uint32 goodscount)
{
	string strr=GetFullPath(str);
	if(!m_pFlashWidget)
	{
		m_pFlashWidget = new FlashPlayer;
	}
	if (m_pFlashWidget)
	{
		m_pFlashWidget->StartAnimation(strr,WND_W,WND_H,m_hWnd);
		m_pFlashWidget->SetQuality(FlashPlayer::QUALITY_HIGH);

		char str[100];
		/*if(CKTVDlg::getInstance().m_userInfo.bCloseGoodsFlashSound)
		{
			sprintf(str,"%u",0);
		}
		else
		{
			sprintf(str,"%u",1);
		}
		m_pFlashWidget->SetVariable("bsound",str);

		goodscount%=1000;
		if (goodscount==0)
		{
			goodscount=1;
		}
		int temp=goodscount;
		int num=goodscount/100;
		goodscount%=100;

		sprintf(str,"%01d",num);
		m_pFlashWidget->SetVariable("x",str);
		num=goodscount/10;
		goodscount%=10;
		sprintf(str,"%01d",num);
		m_pFlashWidget->SetVariable("y",str);
		num=goodscount;
		sprintf(str,"%01d",num);
		m_pFlashWidget->SetVariable("z",str);*/

		sprintf(str,"%01d",m_curFlashData->treasureIndex);//m_curFlashData->treasureIndex);
		m_pFlashWidget->SetVariable("jx",str);
 
		CString strScore=" ";
		switch(m_curFlashData->treasureIndex)
		{
		case 1:
			strScore = "一等奖";
			break;
		case 2:
			strScore = "二等奖";
			break;
		case 3:
			strScore = "三等奖";
			break;
		case 4:
			strScore = "四等奖";
			break;
		case 5:
			strScore = "五等奖";
			break;
		default:
			strScore = " ";
			break;

		}
		sprintf(str,"%s",strScore);
		m_pFlashWidget->SetVariable("jx_txt",str);

		sprintf(str,"%s",m_curFlashData->treasureName.c_str());
		m_pFlashWidget->SetVariable("mc_txt",str);

		sprintf(str,"%d",m_curFlashData->treasureValue);
		m_pFlashWidget->SetVariable("jj_txt",str);

		sprintf(str,"%s","K豆"/*CKTVDlg::getInstance().m_configInfo.money_names.first_money_name*/);
		
		m_pFlashWidget->SetVariable("bz_txt",str);

		m_pFlashWidget->SetLoop(TRUE);

	}
}

char* CDlgSWFPlayer::GetFullPath(const char* lpsFile)
{
	static char sPath[MAX_PATH]={0};
	static char sFull[MAX_PATH]={0};

	if (strlen(lpsFile)>=2&&lpsFile[1]==':')
		return (char*)lpsFile;

	if (sPath[0] == '\0')
	{
		// 第一次使用时自动填充应用程序目录
		GetModuleFileName(GetModuleHandle(NULL), sPath, sizeof(sPath));
		for(int i = (int)strlen(sPath) - 1; i > 0; i--)
			if(sPath[i]=='\\')
				break;
		sPath[i+1]=0;	//格式 -> "驱动器:\路径\"
	}
	sprintf(sFull,"%sface\\flash\\%s",sPath,lpsFile);
	return sFull;
}


int CDlgSWFPlayer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

void CDlgSWFPlayer::ShowDlg(int x, int y)
{
	m_bPaint = TRUE;

	if (x&& y)
	{
		MoveWindow(x,y,640,480);
		
	}
	if(FALSE)
	{
		ShowWindow(SW_HIDE);
	}
	else if ((m_flashVect.size()>0||m_curFlashData) )
	{
		ShowWindow(SW_SHOWNA);
		GetDlgItem(IDC_BTN_NEW_GAME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BTN_EXIT_GAME)->ShowWindow(SW_HIDE);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
}

void CDlgSWFPlayer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	if(!m_bPaint)
		return;
	CRect    rect;     
	GetClientRect(rect);     
	dc.FillSolidRect(rect,    RGB(240,240,240));     
}

void CDlgSWFPlayer::OnBnClickedBtnNewGame()
{
	GetDlgItem(IDC_BTN_NEW_GAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_EXIT_GAME)->ShowWindow(SW_HIDE);
	InvalidateClinet();
	::PostMessage(m_pParent->GetSafeHwnd(),WM_USER+5006,NULL,NULL);
	OnBnClickedBtnExitGame();
}

void CDlgSWFPlayer::OnBnClickedBtnExitGame()
{
	GetDlgItem(IDC_BTN_NEW_GAME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BTN_EXIT_GAME)->ShowWindow(SW_HIDE);
	InvalidateClinet();
	m_CurGameState = STATE_NULL;
	ShowFlash();
}

void CDlgSWFPlayer::InvalidateClinet()
{
	HDC dc = ::GetDC(m_hWnd);
	CRect    rect;     
	GetClientRect(rect);     
	CDC cdcMem;
	cdcMem.Attach(dc);
	cdcMem.FillSolidRect(rect,RGB(240,240,240)); 
	::ReleaseDC(m_hWnd,dc);
}
