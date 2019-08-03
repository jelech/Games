// BejeweledV4Dlg.h: 头文件
//

#pragma once

// CBejeweledV4Dlg 对话框
class CBejeweledV4Dlg : public CDialogEx
{
	// 构造
public:
	CBejeweledV4Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BEJEWELEDV4_DIALOG };
#endif

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

	void InitNewMap();
	void RestartGame();
	void OnLButtonDown(UINT nFlags, CPoint point);
	bool Swap2Block(int a, int b, int curx, int cury);
	void ChooseAndDraw(int x, int y);
	bool CheckMap(int x, int y);
	bool CheckAllMap();
	void DrawAndUpdate();
	void AnimationDrawBlock(int nx, int ny, int tx, int ty);

private:
	int matchMap[10][10];// 地图信息
	bool visMap[10][10];

	int GOALSCORE = 200;		// 地图目标分数
	const int MAX_TIME = 60;  // 倒计时最大时间 - 秒

	const int CHECK_TIME_DUR = 1000; // 时钟检查时间
	std::vector<std::pair<int, int> > needUpdateV;
	bool visNeedUpdate[10][10];

	int clickNum;
	int prex, prey;
	const int SIZE = 90;

	bool hasPause = true;
	bool gameEnd = false;
	bool stillDrawing;
	int score = 0;

	CProgressCtrl *m_Process;
	int processMax;
	int count;

public:
	afx_msg void OnStnClickedPicturetest2();
	afx_msg void OnBnClickedStart();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedPause();
};
