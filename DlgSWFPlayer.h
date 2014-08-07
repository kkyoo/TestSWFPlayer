#pragma once
#include "resource.h"
#include "flashplayer/FlashPlayer.h"
using namespace std;
#include <vector>
typedef unsigned long uint32;
typedef unsigned char uint8;

enum GAME_STATE
{
	STATE_NULL = 0,//����
	STATE_WAITDIG, //�ȴ�������ڱ�
	STATE_SEND_SVR,//�ȴ�����������
	STATE_DIG,     //����������Ŷ���
	STATE_OVER     //�ڱ��������ȴ��رջ�����һ��
};

struct FlashData
{
	uint8 treasureIndex;
	string treasureName;
	uint32  treasureValue;
};	
// CDlgDlgTreasure �Ի���

class CDlgSWFPlayer : public CDialog
{
	DECLARE_DYNAMIC(CDlgSWFPlayer)

public:
	CDlgSWFPlayer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSWFPlayer();

// �Ի�������
	enum { IDD = IDD_SWF_PLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
	BOOL OnInitDialog();
	CWnd*					m_pParent;					//����ָ��
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
	bool			m_bIsPlaying;				//���ڲ���
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
