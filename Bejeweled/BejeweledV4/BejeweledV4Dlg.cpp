// BejeweledV4Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "BejeweledV4.h"
#include "BejeweledV4Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CBejeweledV4Dlg 对话框

CBejeweledV4Dlg::CBejeweledV4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BEJEWELEDV4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBejeweledV4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBejeweledV4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN() // 添加鼠标左键消息映射
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBejeweledV4Dlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PAUSE, &CBejeweledV4Dlg::OnBnClickedPause)
END_MESSAGE_MAP()

// CBejeweledV4Dlg 消息处理程序

BOOL CBejeweledV4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Process = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	processMax = MAX_TIME * 1000 / CHECK_TIME_DUR;
	m_Process->SetRange(0, MAX_TIME * 1000 / CHECK_TIME_DUR);
	m_Process->SetStep(-1);
	m_Process->SetPos(processMax);
	count = MAX_TIME;

	CFont m_editFont;
	m_editFont.CreatePointFont(200, _T("宋体"));
	GetDlgItem(IDC_PAUSE)->SetFont(&m_editFont);
	InitNewMap();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBejeweledV4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBejeweledV4Dlg::OnPaint()
{
	static int psss = 1;
	psss++;
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();

		// 用户添加
		CImage image;//创建图片类
		CWnd *pWnd = GetDlgItem(IDC_Picture);//获得picture控件窗口句柄
		CDC *pDC = pWnd->GetDC();//获得picture控件的DC

		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				image.Destroy();
				if (matchMap[i][j] == 0) image.Load(_T("res/1.bmp"));//加载图片文件
				else if (matchMap[i][j] == 1) image.Load(_T("res/2.bmp"));//加载图片文件
				else if (matchMap[i][j] == 2) image.Load(_T("res/3.bmp"));//加载图片文件
				else if (matchMap[i][j] == 3) image.Load(_T("res/4.bmp"));//加载图片文件
				int cx = image.GetWidth();//获取图片宽度
				int cy = image.GetHeight();//获取图片高度
				image.Draw(pDC->m_hDC, i*(SIZE), j*(SIZE), SIZE, SIZE);//将图片画到picture控件表示的矩形区域内
			}
		}

		ReleaseDC(pDC);//释放picture控件的DC
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBejeweledV4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBejeweledV4Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(100);
	if (MessageBox(_T("重新开始？"), _T("提示"), MB_YESNO | MB_ICONWARNING) == IDNO) {
		return;
	}
	//Restart
	RestartGame();

	return;
}

void CBejeweledV4Dlg::InitNewMap()
{
	memset(visNeedUpdate, 0, sizeof(visNeedUpdate));
	memset(visMap, 0, sizeof(visMap));
	needUpdateV.clear();
	// 冲洗地图直到没有连续
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			matchMap[i][j] = rand() % 4;
		}
	}
	while (CheckAllMap()) {
		for (auto box : needUpdateV) {
			matchMap[box.first][box.second] = rand() % 4;
		}
		needUpdateV.clear();
	}

	clickNum = 0;
	score = 0;
	needUpdateV.clear();
	GetDlgItem(IDC_Score)->SetWindowText(_T("0"));

	CString t;
	t.Format(_T("%d"), count);
	GetDlgItem(IDC_RelTime)->SetWindowText(t);
}

void CBejeweledV4Dlg::RestartGame()
{
	count = MAX_TIME;
	InitNewMap();
	gameEnd = false;
	hasPause = true;
	GetDlgItem(IDC_PAUSE)->SetWindowTextW(_T("开始"));
	m_Process->SetPos(processMax);
	RedrawWindow();
}

void CBejeweledV4Dlg::OnLButtonDown(UINT nFlags, CPoint point) //鼠标按下
{
	// 判断动画是否再进行
	if (hasPause || gameEnd) return;

	ClientToScreen(&point);//将鼠标坐标转换成屏幕坐标
	CRect rect;//定义一个矩形框，包含左上角和右下角可访问成员
	GetDlgItem(IDC_Picture)->GetClientRect(rect);//获取Picture控件的位置信息，存入rect中
	GetDlgItem(IDC_Picture)->ClientToScreen(rect);//转换成屏幕坐标

	// 横向X， 纵向Y
	int posx = point.x - rect.left;
	int posy = point.y - rect.top;

	if (0 < posx && posx < 730 && 0 < posy && posy < 730)//判断point是否在rect内部
	{
		int blockx = posx / 90;
		int blocky = posy / 90;
		printf("%d %d\n", posx, posy);
		clickNum++;


		//while (CheckAllMap()) {
		//	DrawAndUpdate(); // 画vector中的block 动画
		//}
		ChooseAndDraw(blockx, blocky);
		if (clickNum >= 2) {
			Swap2Block(prex, prey, blockx, blocky);

			if (abs(prex - blockx) + abs(prey - blocky) == 1) { // 检查和这两个相关点的连线,加入Vector
				bool flag = CheckMap(prex, prey);
				bool flag2 = CheckMap(blockx, blocky);
				if (flag || flag2) {
					ChooseAndDraw(prex, prey);
					ChooseAndDraw(blockx, blocky);

					// 画图开始，暂停时间
					KillTimer(100);
					DrawAndUpdate();

					// 更新全局的
					while (CheckAllMap()) {
						DrawAndUpdate(); // 画vector中的block (动画?
					}
					// 画图结束，开始时间
					SetTimer(100, CHECK_TIME_DUR, NULL);

					if (score > GOALSCORE) {
						gameEnd = true;
						KillTimer(100);
						if (MessageBox(_T("你赢啦！重新开始？"), _T("提示"), MB_YESNO | MB_ICONWARNING) == IDNO) {
							exit(0);
						}
						RestartGame();
					}
					clickNum = 0;
					prex = 0, prey = 0;
					return;
				}
			}
			{ // 选取失败 或 不可选取 或 选取后无解
				ChooseAndDraw(prex, prey);
				ChooseAndDraw(blockx, blocky);
				ChooseAndDraw(prex, prey);
				ChooseAndDraw(blockx, blocky);
				Sleep(200);

				Swap2Block(prex, prey, blockx, blocky); // 检查失败，交换回来
				ChooseAndDraw(prex, prey);
				ChooseAndDraw(blockx, blocky);
			}
			clickNum = 0;
			prex = 0, prey = 0;
		}
		else { // 第一次点击
			prex = blockx;
			prey = blocky;
		}
	}
}

bool CBejeweledV4Dlg::Swap2Block(int a, int b, int curx, int cury)
{
	int temp = matchMap[a][b];
	matchMap[a][b] = matchMap[curx][cury];
	matchMap[curx][cury] = temp;
	return true;
}

void CBejeweledV4Dlg::ChooseAndDraw(int x, int y)
{
	if (x < 0 || x > 8 || y < 0 || y > 8) return;

	CImage image;//创建图片类
	CWnd *pWnd = GetDlgItem(IDC_Picture);//获得picture控件窗口句柄
	CDC *pDC = pWnd->GetDC();//获得picture控件的DC

	if (visMap[x][y]) { // 已经访问过，需要取消
		visMap[x][y] = false;
		if (matchMap[x][y] == 0) image.Load(_T("res/1.bmp"));//加载图片文件
		else if (matchMap[x][y] == 1) image.Load(_T("res/2.bmp"));//加载图片文件
		else if (matchMap[x][y] == 2) image.Load(_T("res/3.bmp"));//加载图片文件
		else if (matchMap[x][y] == 3) image.Load(_T("res/4.bmp"));//加载图片文件
		int cx = image.GetWidth();//获取图片宽度
		int cy = image.GetHeight();//获取图片高度
		image.Draw(pDC->m_hDC, x*(SIZE), y*(SIZE), SIZE, SIZE);//将图片画到picture控件表示的矩形区域内
	}
	else {
		visMap[x][y] = true;
		int drawX = x * 90 + 2, drawY = y * 90 + 2; // 画到内部
		CClientDC dc(this);//选定当前画图环境
		CPen pen(PS_SOLID, 4, RGB(255, 255, 255));//做一支红色粗细为1的笔
		dc.SelectObject(&pen);//将pen放到dc
		dc.SelectStockObject(NULL_BRUSH);
		dc.Rectangle(drawX, drawY, drawX + 86, drawY + 86);
		ReleaseDC(&dc);
	}

	ReleaseDC(pDC);
}

bool CBejeweledV4Dlg::CheckMap(int x, int y)
{
	/// 检查单点
	if (x < 0 || x > 8 || y < 0 || y > 8)
		return false;
	int len = 0;
	int curx = x, cury = y, curx2 = x + 1, cury2 = y + 1;
	int tempVal = matchMap[x][y];
	while (curx >= 0 && matchMap[curx][y] == tempVal) curx--;
	while (curx2 < 8 && matchMap[curx2][y] == tempVal) curx2++;
	while (cury >= 0 && matchMap[x][cury] == tempVal) cury--;
	while (cury2 < 8 && matchMap[x][cury2] == tempVal) cury2++;
	for (int i = curx + 1; curx2 - curx - 1 >= 3 && i < curx2; ++i) {
		if (visNeedUpdate[i][y]) continue;
		needUpdateV.push_back({ i, y });
		visNeedUpdate[i][y] = true;
	}
	for (int i = cury + 1; cury2 - cury - 1 >= 3 && i < cury2; ++i) {
		if (visNeedUpdate[y][i]) continue;
		needUpdateV.push_back({ x, i });
		visNeedUpdate[x][i] = true;
	}

	return needUpdateV.size() > 0;
}

bool CBejeweledV4Dlg::CheckAllMap()
{
	/// 横向、纵向
	for (int dir = 0; dir < 2; ++dir) {
		for (int i = 0; i < 8; ++i) {
			int pre = 0;
			int curVal = (dir == 0 ? matchMap[i][pre] : matchMap[pre][i]);
			int len = 0;

			for (int j = 0; j < 8; ++j) {
				int temp = (dir == 0 ? matchMap[i][j] : matchMap[j][i]);
				if (temp == curVal) {
					len++;
					if (len >= 3 && j == 7) {
						for (int k = pre; k <= j; ++k) {
							// 加入所有值到更新列表中
							needUpdateV.push_back((dir == 0 ? std::make_pair(i, k) : std::make_pair(k, i)));
						}

						// 更新当前对比点
						pre = j, len = 1;
						curVal = temp;
					}
				}
				else if (len >= 3) { //相同的已经到这里
					for (int k = pre; k < j; ++k) {
						// 加入所有值到更新列表中
						needUpdateV.push_back((dir == 0 ? std::make_pair(i, k) : std::make_pair(k, i)));
					}

					// 更新当前对比点
					pre = j, len = 1;
					curVal = temp;
				}
				else { // 值不同了，并且长度不够
					pre = j, len = 1;
					curVal = temp;
				}
			}
		}
	}

	return needUpdateV.size() > 0;
}

void CBejeweledV4Dlg::DrawAndUpdate()
{
	CClientDC dc(this);//选定当前画图环境
	CPen pen(PS_SOLID, 8, RGB(247, 248, 249));//做一支红色粗细为1的笔
	dc.SelectObject(&pen);//将pen放到dc
	dc.SelectStockObject(NULL_BRUSH);

	// 动画，画出可以消掉的模块
	Sleep(300);
	for (int time = 1; time < 11; ++time) {
		Sleep(100 / 10);
		for (auto npoint : needUpdateV) {
			int drawX = npoint.first * 90 + 8 * time - 4, drawY = npoint.second * 90 + 8 * time - 4;
			dc.Rectangle(drawX, drawY, drawX + 90 - time * 8, drawY + 90 - time * 8);
			visNeedUpdate[npoint.first][npoint.second] = false;
			matchMap[npoint.first][npoint.second] = -1;
		}
		if (time == 3) {
			continue;
		}
	}
	score += needUpdateV.size();
	CString t;
	t.Format(_T("%d"), score);
	GetDlgItem(IDC_Score)->SetWindowText(t);
	needUpdateV.clear(); // 更新已经划掉的模块

	//Sleep(200);
	// 上面的滑块向下移动
	for (int i = 0; i < 8; ++i) {
		int st = 0;
		while (st < 8) {
			while (st < 8 && matchMap[i][st] != -1) st++;
			int ed = st;
			while (ed < 8 && matchMap[i][ed] == -1) ed++;

			if (st == 8) break; // 这一列没有
			// 移动动画
			AnimationDrawBlock(i, st - 1, i, ed - 1);
			st = ed;
		}
	}

	ReleaseDC(&dc);
}

void CBejeweledV4Dlg::AnimationDrawBlock(int nx, int ny, int tx, int ty) // x应该是相同的，由上向下移动
{
	//CImage image;//创建图片类
	CWnd *pWnd = GetDlgItem(IDC_Picture);//获得picture控件窗口句柄
	CDC *pDC = pWnd->GetDC();//获得picture控件的DC

	CImage images[10];
	int imagesPos[10];
	int imagesSz = ny;
	std::vector<int> addBlockList;

	for (int i = 0; i <= ny; ++i) { // 装载标记点以上的所有滑块
		int type = matchMap[nx][ny - i];
		if (type == 0) images[i].Load(_T("res/1.bmp"));//加载图片文件
		else if (type == 1) images[i].Load(_T("res/2.bmp"));
		else if (type == 2) images[i].Load(_T("res/3.bmp"));
		else if (type == 3) images[i].Load(_T("res/4.bmp"));
		imagesPos[i] = ny - i;
		addBlockList.push_back(type);
	}

	// 动画，block下移
	bool canAddNewBlock = false;
	for (float j = 0; j <= ty - ny; j += 0.5) { // 分帧
		Sleep(20);

		if (canAddNewBlock) {
			imagesSz++;
			int type = rand() % 4;
			if (type == 0) images[imagesSz].Load(_T("res/1.bmp"));//加载图片文件
			else if (type == 1) images[imagesSz].Load(_T("res/2.bmp"));
			else if (type == 2) images[imagesSz].Load(_T("res/3.bmp"));
			else if (type == 3) images[imagesSz].Load(_T("res/4.bmp"));
			if (imagesSz == 0)
				imagesPos[0] = -1;
			else
				imagesPos[imagesSz] = imagesPos[imagesSz - 1] - 1;
			addBlockList.push_back(type);
			canAddNewBlock = false;
		}
		else canAddNewBlock = true;

		//画出此帧 图片
		for (int i = 0; i <= imagesSz; ++i) {
			images[i].Draw(pDC->m_hDC, nx*(SIZE), (j + imagesPos[i])*(SIZE), SIZE, SIZE);//将图片画到picture控件表示的矩形区域内
		}
	}

	// 更新map
	int prePos = ty;
	for (auto pos : addBlockList) {
		if (prePos == -1) break;
		matchMap[nx][prePos] = pos;
		prePos--;
	}

	ReleaseDC(pDC);
}

void CBejeweledV4Dlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	InitNewMap();
	RedrawWindow();
	/*CProgressCtrl *pProgCtrl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	int nPos = (pProgCtrl->GetPos() - 0) * 100 / (200 - 0);
	int b = 1;*/
}

void CBejeweledV4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	default:
		break;
	case 100:
		//PostMessage(WM_CLOSE);
		count--;
		CString t;
		t.Format(_T("%d"), count);
		GetDlgItem(IDC_RelTime)->SetWindowText(t);

		m_Process->StepIt();
		int pos = m_Process->GetPos();
		if (pos <= 0)
		{
			KillTimer(100);
			MessageBox(_T("时间到！"));
			hasPause = true;
			gameEnd = true;
			//PostMessage(WM_CLOSE);
		}

		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CBejeweledV4Dlg::OnBnClickedPause()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd *pWnd = GetDlgItem(IDC_PAUSE);
	CString i;
	GetDlgItemText(IDC_PAUSE, i); //取按钮标题
	if (gameEnd) return;

	if (i == _T("继续")) {
		hasPause = false;
		RedrawWindow();
		SetTimer(100, CHECK_TIME_DUR, NULL);
		pWnd->SetWindowText(_T("暂停"));
	}
	else if (i == _T("开始")) {
		hasPause = false;
		count = MAX_TIME;
		SetTimer(100, CHECK_TIME_DUR, NULL);
		pWnd->SetWindowText(_T("暂停"));
	}
	else {
		hasPause = true;
		KillTimer(100);
		pWnd->SetWindowText(_T("继续"));
	}
}