#pragma once
#include "resource.h"
#include "flashplayer/FlashPlayer.h"
using namespace std;
#include <vector>
typedef unsigned long uint32;
typedef unsigned char uint8;

enum GAME_STATE
{
	STATE_NULL = 0,//空闲
	STATE_WAITDIG, //等待鼠标点击挖宝
	STATE_SEND_SVR,//等待服务器返回
	STATE_DIG,     //鼠标点击，播放动画
	STATE_OVER     //挖宝结束，等待关闭或再来一局
};

struct FlashData
{
	uint8 treasureIndex;
	string treasureName;
	uint32  treasureValue;
};	
// CDlgDlgTreasure 对话框

class CDlgSWFPlayer : public CDialog
{
	DECLARE_DYNAMIC(CDlgSWFPlayer)

public:
	CDlgSWFPlayer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSWFPlayer();

// 对话框数据
	enum { IDD = IDD_SWF_PLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

protected:
	BOOL OnInitDialog();
	CWnd*					m_pParent;					//父亲指针
	std::vector<FlashData*> m_flashVect; 
	FlashPlayer*			 m_pFlashWidget;
	HDC						m_hMemDC ;
	HDC						m_hMemDCEx ;
	BOOL                    m_bPaint;
public:
	void setParent(CWnd* pParent) { m_pParent = pParent; };
	afx_msg void OnTimer(UINT nIDEvent);
	VOID ChangeFlash(const char* str,uint32 goodscount);
	char* GetFullPath(const char* lpsFile);
public:
	FlashData*      m_curFlashData;
	bool			m_bIsPlaying;				//正在播放
	UINT            m_CurGameState;
	void ShowFlash();
	void StartPlayCurFlash();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void ShowDlg(int x=0,int y=0);
	afx_msg void OnPaint();
	void AddFlashData(FlashData* p);
	void InvalidateClinet();

	afx_msg void OnBnClickedBtnNewGame();
	afx_msg void OnBnClickedBtnExitGame();
};
