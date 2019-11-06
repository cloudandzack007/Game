
// Game_LTYDlg.h : 头文件
//

#pragma once


// CGame_LTYDlg 对话框
class CGame_LTYDlg : public CDialogEx
{
// 构造
public:
	CGame_LTYDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GAME_LTY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void L(void);
	void R(void);
	void INITPIC(void);
	void Up(void);
	void Do(void);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedDiff2();
};
