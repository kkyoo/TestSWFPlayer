// TestPlaySWFDlg.h : ͷ�ļ�
//

#pragma once

#include "DlgSWFPlayer.h"

// CTestPlaySWFDlg �Ի���
class CTestPlaySWFDlg : public CDialog
{
// ����
public:
	CTestPlaySWFDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTPLAYSWF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

public:
	CDlgSWFPlayer                     m_DigTreasureGame;          //�ڱ�


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnWb();
	afx_msg LRESULT OnStartDigTreasure(WPARAM wParam,LPARAM lParam);
};
