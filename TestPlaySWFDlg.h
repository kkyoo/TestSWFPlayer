// TestPlaySWFDlg.h : 头文件
//

#pragma once

#include "DlgSWFPlayer.h"

// CTestPlaySWFDlg 对话框
class CTestPlaySWFDlg : public CDialog
{
// 构造
public:
	CTestPlaySWFDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTPLAYSWF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

public:
	CDlgSWFPlayer                     m_DigTreasureGame;          //挖宝


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnWb();
	afx_msg LRESULT OnStartDigTreasure(WPARAM wParam,LPARAM lParam);
};
