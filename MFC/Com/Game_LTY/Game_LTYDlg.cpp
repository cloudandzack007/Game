


#include "stdafx.h"
#include "Game_LTY.h"
#include "Game_LTYDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "linklist.h"

#define PIC_SizeOfBlock_X (1*2*3*4*2)
#define PIC_SizeOfBlock_Y (1*2*3*4*2)
int  PIC_SizeOfPlayer_X=(PIC_SizeOfBlock_X);
int  PIC_SizeOfPlayer_Y=(PIC_SizeOfBlock_Y);
int PIC_MoveSize_L = PIC_SizeOfPlayer_X/2;
int PIC_MoveSize_R = PIC_SizeOfPlayer_X/2;
#define PIC_CNTBlock_X (26)
#define PIC_CNTBlock_Y (17)
#define PIC_W (PIC_SizeOfBlock_X*PIC_CNTBlock_X)
#define PIC_H (PIC_SizeOfBlock_Y*PIC_CNTBlock_Y)
#define Random_X_CNT (1)
#define Speed (1)
#define PIC_Speed (1)

bool DeadOrLive = false;
bool BIG = false;
bool SMALL = false;
bool H =false;
bool W =false;
int Fast_cnt  =  0;
int Fast_cnt_ =  0;
int Slow_cnt  =  0;
int Slow_cnt_ =  0;
int Random_X_CNT_ = Random_X_CNT;
int PIC_Speed_ = PIC_Speed;

CDC * pDC = NULL;
bool g_bExit  =true;
bool g_bPause =true;
LONG pointx;
LONG pointy;
LONG BLOCK_X = 0;
LONG BLOCK_Y = 0;
LONG BLOCK_X_OLD = 0;
LONG BLOCK_Y_OLD = 0;
LONG PIC_POINT = 0;
COLORREF CLR_BLOCK_DEAD = RGB(0,128,64);
COLORREF CLR_BLOCK_LIVE = RGB(255,128,64);
COLORREF CLR_BLOCK_BIG = RGB(255,0,0);
COLORREF CLR_BLOCK_SMALL = RGB(0,0,255);
COLORREF CLR_BLOCK_W = RGB(255,255,0);
COLORREF CLR_BLOCK_H = RGB(255,255,255);
COLORREF CLR_BLOCK_Fast = RGB(192,192,192);
COLORREF CLR_BLOCK_Slow = RGB(128,128,0);
COLORREF CLR_BACK =  RGB(0,0,0);

BYTE * BLOCK_BIT = NULL;
bool first = false;
unsigned int seed  = 0;


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CGame_LTYDlg::CGame_LTYDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGame_LTYDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGame_LTYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGame_LTYDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGame_LTYDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGame_LTYDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGame_LTYDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_Speed, &CGame_LTYDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_Diff_, &CGame_LTYDlg::OnBnClickedDiff2)
END_MESSAGE_MAP()




BOOL CGame_LTYDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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


	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);

	OnBnClickedButton4();
	OnBnClickedDiff2();
	
	return TRUE;  
}

void CGame_LTYDlg::OnSysCommand(UINT nID, LPARAM lParam)
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



void CGame_LTYDlg::OnPaint()
{
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
	}
}


HCURSOR CGame_LTYDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
bool b_Fast_ = true;
bool b_Slow_ = true;
UINT Fast_(LPVOID pParam)
{
	int PIC_Speed_OLD = PIC_Speed_;
	PIC_Speed_++;
	if(PIC_Speed_>=5)
	{
		PIC_Speed_ = 6;	
	}
	if(PIC_Speed_>=7)
	{
		PIC_Speed_ = 1;
	}
	Fast_cnt=0;
	Sleep(1000);
	PIC_Speed_ = PIC_Speed_OLD;
	b_Fast_ = true;
	return 0;
}
UINT Slow_(LPVOID pParam)
{
	int PIC_Speed_OLD = PIC_Speed_;
	if(PIC_Speed_>=2)
	{
		PIC_Speed_--;
		if(PIC_Speed_==5)
		{
			PIC_Speed_=4;
		}
	}
	Slow_cnt=0;
	Sleep(1000);
	PIC_Speed_ = PIC_Speed_OLD;
	b_Slow_ = true;
	return 0;
}
UINT GAME_PIC(LPVOID pParam)
{
	//COleDateTime temp1;
	//COleDateTime temp2;
	//COleDateTimeSpan temp3;
	//temp1.ParseDateTime("2015-12-16 15:05:05");
	//temp2.ParseDateTime("2015-12-17 16:06:03");
	//temp3 = temp2-temp1;
	//CString temp3_str = temp3.Format("%Y-%m-%D %H:%M:%S");
	//temp3_str = temp3.GetDays();
	//temp3_str = temp3.GetHours();
	//temp3_str = temp3.GetMinutes();
	//temp3_str = temp3.GetSeconds();
	CGame_LTYDlg * home = (CGame_LTYDlg*)pParam;
	CDC MemDC;  
	CBitmap MemBitmap;  
	MemDC.CreateCompatibleDC(NULL); 
	BOOL bRet = MemBitmap.CreateCompatibleBitmap(pDC,PIC_W,PIC_H);  
	BITMAP bm = {0};
	MemBitmap.GetObject(sizeof(BITMAP), &bm);
	
	int cnt = 0;
	int Rcnt = 0;
	Rcnt  = rand()%15;

	int Random_X[PIC_W-PIC_SizeOfBlock_X] = {0};
	for(int i=0;i<Random_X_CNT_;i++)
		Random_X[i] = rand()%(PIC_W-PIC_SizeOfBlock_X);
	linklist ll(PIC_H,PIC_W*4);
	BYTE * PIC_BIT = new BYTE[PIC_H*PIC_W*4];
	YX * cur = ll.head;

	for(int i=0;i<PIC_H;i++)
	{
		for(int j=0;j<PIC_W;j=j++)
		{
			cur->data[j*4+0] = (CLR_BACK&0x00ff0000)>>16;
			cur->data[j*4+1] = (CLR_BACK&0x0000ff00)>>8;
			cur->data[j*4+2] = (CLR_BACK&0x000000ff)>>0;
			cur->data[j*4+3] = 0;
		}
		cur = cur->next;
	}

	srand(seed);

	while(1)
	{
		if (g_bExit)
		{  
			return 0;
		}

		while (g_bPause)
		{
			if (g_bExit)
			{  
				return 0;
			}
		}

		cur = ll.head;
		
		for(int i=0;i<PIC_Speed_;i++)
		{
			for(int j=0;j<PIC_W;j++)
			{
				cur->data[j*4+0] = (CLR_BACK&0x00ff0000)>>16;
				cur->data[j*4+1] = (CLR_BACK&0x0000ff00)>>8;
				cur->data[j*4+2] = (CLR_BACK&0x000000ff)>>0;
				cur->data[j*4+3] = 0;
			}
			cur = cur->next;
		}

		cur = ll.head;
		
		for(int i=0;i<PIC_Speed_;i++)
		{
			for(int xcnt=0;xcnt<Random_X_CNT_;xcnt++)
			{
				if(xcnt == Random_X_CNT_-1)
				{
					COLORREF CLR_BLOCK_Change;
					switch(Rcnt)
					{
						case 1:{CLR_BLOCK_Change =CLR_BLOCK_BIG;break;}
						case 2:{CLR_BLOCK_Change =CLR_BLOCK_SMALL;break;}
						case 3:{CLR_BLOCK_Change =CLR_BLOCK_H;break;}
						case 4:{CLR_BLOCK_Change =CLR_BLOCK_W;break;}
						case 5:{CLR_BLOCK_Change =CLR_BLOCK_Fast;break;}
						case 6:{CLR_BLOCK_Change =CLR_BLOCK_Slow;break;}
						default:{CLR_BLOCK_Change = CLR_BLOCK_DEAD;Rcnt = 7;break;}
					}
					for(int j=0;j<PIC_SizeOfBlock_X;j++)
					{
						cur->data[Random_X[xcnt]*4+j*4+0] = (CLR_BLOCK_Change&0x00ff0000)>>16;
						cur->data[Random_X[xcnt]*4+j*4+1] = (CLR_BLOCK_Change&0x0000ff00)>>8 ;
						cur->data[Random_X[xcnt]*4+j*4+2] = (CLR_BLOCK_Change&0x000000ff)>>0 ;
						cur->data[Random_X[xcnt]*4+j*4+3] = Rcnt;
					}
				}
				else
				{
					for(int j=0;j<PIC_SizeOfBlock_X;j++)
					{
						cur->data[Random_X[xcnt]*4+j*4+0] = (CLR_BLOCK_DEAD&0x00ff0000)>>16;
						cur->data[Random_X[xcnt]*4+j*4+1] = (CLR_BLOCK_DEAD&0x0000ff00)>>8 ;
						cur->data[Random_X[xcnt]*4+j*4+2] = (CLR_BLOCK_DEAD&0x000000ff)>>0 ;
						cur->data[Random_X[xcnt]*4+j*4+3] = Rcnt;
					}
				}
			}
			cur = cur->next;
			cnt++;
			if(cnt == PIC_SizeOfBlock_Y)
			{
				cnt=0;
				Rcnt  = rand()%15;

				for(int rx =0;rx<Random_X_CNT_;rx++)
				{
					Random_X[rx] = rand()%(PIC_W-PIC_SizeOfBlock_X);
				}
				PIC_POINT++;
				CString point_str ;
				point_str.Format("%d",PIC_POINT);
				point_str = "POINT : "+ point_str;
				home->SetDlgItemText(IDC_POINT,point_str);
			}
		}
		
		cur = ll.tail;

		if(BLOCK_X_OLD!=BLOCK_X||BLOCK_Y_OLD!=BLOCK_Y)
		{
			for(int i=0;i<BLOCK_Y_OLD;i++)
			{
				cur = cur->prev;
			}
			BLOCK_Y_OLD = BLOCK_Y;

			for(int i=0;i<PIC_SizeOfPlayer_Y;i++)
			{
				for(int j=0;j<PIC_SizeOfPlayer_X;j++)
				{
					cur->data[BLOCK_X_OLD*4+j*4+0] = (CLR_BACK&0x00ff0000)>>16; 
					cur->data[BLOCK_X_OLD*4+j*4+1] = (CLR_BACK&0x0000ff00)>> 8;
					cur->data[BLOCK_X_OLD*4+j*4+2] = (CLR_BACK&0x000000ff)>> 0;
					cur->data[BLOCK_X_OLD*4+j*4+3] = 0;
				}
				cur = cur->prev;
			}
			BLOCK_X_OLD = BLOCK_X;
		}

		cur = ll.tail;
		
		for(int i=0;i<BLOCK_Y;i++)
		{
			cur = cur->prev;
		}

		for(int i=0;i<PIC_SizeOfPlayer_Y;i++)
		{
			for(int j=0;j<PIC_SizeOfPlayer_X;j++)
			{
				switch(cur->data[BLOCK_X*4+j*4+3])
				{
					case 1:{BIG = true;break;}
					case 2:{SMALL = true;break;}
					case 3:{H = true;break;}
					case 4:{W = true;break;}
					case 5:{Fast_cnt++;break;}
					case 6:{Slow_cnt++;break;}
					case 7:{DeadOrLive = true;break;}
					default:{break;}
				}
				
				cur->data[BLOCK_X*4+j*4+0] = (CLR_BLOCK_LIVE&0x00ff0000)>>16; 
				cur->data[BLOCK_X*4+j*4+1] = (CLR_BLOCK_LIVE&0x0000ff00)>> 8;
				cur->data[BLOCK_X*4+j*4+2] = (CLR_BLOCK_LIVE&0x000000ff)>> 0;
				cur->data[BLOCK_X*4+j*4+3] = 0;
			}
			cur = cur->prev;
		}

		if (BIG == true)
		{
			PIC_SizeOfPlayer_X++;
			PIC_SizeOfPlayer_Y++;
			PIC_MoveSize_L = PIC_SizeOfPlayer_X/2;
			PIC_MoveSize_R = PIC_SizeOfPlayer_X/2;
		}
		if (SMALL == true)
		{
			if(PIC_SizeOfPlayer_X-1>5)
			PIC_SizeOfPlayer_X--;
			if(PIC_SizeOfPlayer_Y-1>5)
			PIC_SizeOfPlayer_Y--;
			PIC_MoveSize_L = PIC_SizeOfPlayer_X/2;
			PIC_MoveSize_R = PIC_SizeOfPlayer_X/2;
		}
		if (H == true)
		{
			if(PIC_SizeOfPlayer_X-1>5)
				PIC_SizeOfPlayer_X--;
			PIC_MoveSize_L = PIC_SizeOfPlayer_X/2;
			PIC_MoveSize_R = PIC_SizeOfPlayer_X/2;
		}
		if(W==true)
		{
			if(PIC_SizeOfPlayer_Y-1>5)
				PIC_SizeOfPlayer_Y--;
			PIC_MoveSize_L = PIC_SizeOfPlayer_X/2;
			PIC_MoveSize_R = PIC_SizeOfPlayer_X/2;
		}

		if (Fast_cnt>=(PIC_SizeOfBlock_X))
		{
			if(b_Fast_==true)
			{	
				b_Fast_ = false;
				AfxBeginThread(Fast_,NULL);
			}
		}
		
		if (Slow_cnt>=(PIC_SizeOfBlock_X))
		{
			if(b_Slow_==true)
			{
				b_Slow_ = false;
				AfxBeginThread(Slow_,NULL);
			}
		}
		
		BIG = false;
		SMALL = false;
		H = false;
		W = false;
		cur = ll.head;

		for(int i=0;i<PIC_H;i++)
		{
			CopyMemory(&PIC_BIT[i*PIC_W*4],cur->data,PIC_W*4);
			cur = cur->next;
		}

		DWORD dwRet = MemBitmap.SetBitmapBits(PIC_H*PIC_W*4,PIC_BIT);
		CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);  
		pDC->StretchBlt(pointx, pointy,PIC_W,PIC_H, &MemDC, 0, 0, PIC_W,PIC_H, SRCCOPY );
		
		if (DeadOrLive == true)
		{
			home->OnBnClickedButton1();
			return 0;
		}

		//for(int i=0;i<PIC_CNTBlock_X;i++)
		//{
		//	if(PIC_BIT[(PIC_H-1)*PIC_W*4+i*PIC_SizeOfBlock_X*4+2] == (CLR_BLOCK&0x000000ff)>>0)
		//	{
		//		if(i*PIC_SizeOfBlock_X == BLOCK_X)
		//		{
		//			while(1);
		//		}
		//	}
		//}	

		cur = ll.tail;

		for(int i=0;i<BLOCK_Y;i++)
		{
			cur = cur->prev;
		}

		for(int i=0;i<PIC_SizeOfPlayer_Y;i++)
		{
			for(int j=0;j<PIC_SizeOfPlayer_X;j++)
			{
				cur->data[BLOCK_X*4+j*4+0] = (CLR_BACK&0x00ff0000)>>16; 
				cur->data[BLOCK_X*4+j*4+1] = (CLR_BACK&0x0000ff00)>> 8;
				cur->data[BLOCK_X*4+j*4+2] = (CLR_BACK&0x000000ff)>> 0;
				cur->data[BLOCK_X*4+j*4+3] = 0;
			}
			cur = cur->prev;
		}

		for(int i=0;i<PIC_Speed_;i++)
		{
			ll.head = ll.head->prev;
			ll.tail = ll.tail->prev;
		}

		Sleep(Speed);
	}
	return 0;
}
void CGame_LTYDlg::OnBnClickedButton1()
{	
	if(g_bExit == true)
	{
		INITPIC();
		pDC=GetDC();
		g_bExit  = false;
		g_bPause = false;
		CRect rect;
		GetDlgItem(IDC_Pic)->GetWindowRect(&rect);
		ScreenToClient(rect);
		pointx=rect.left;
		pointy=rect.top;
		PIC_POINT =0;
		AfxBeginThread(GAME_PIC, this);
		SetDlgItemText(IDC_BUTTON1,"Stop");
	}
	else
	{
		g_bExit = true;
		PIC_POINT =0;
		SetDlgItemText(IDC_BUTTON1,"Start");
	}
}

void CGame_LTYDlg::OnBnClickedButton2()
{
	if (g_bPause == false)
	{
		g_bPause = true;
		SetDlgItemText(IDC_BUTTON2,"Continue");
	}
	else
	{
		g_bPause = false;
		SetDlgItemText(IDC_BUTTON2,"Pause");
	}
}

BOOL CGame_LTYDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:return TRUE;
		case VK_ESCAPE:return TRUE;
		case 37:
			{
				if(g_bPause==false&&g_bExit==false){L();};return TRUE;
			}
		case 38:
			{
				if(g_bPause==false&&g_bExit==false){Up();};return TRUE;
			}
		case 39:
			{
				if(g_bPause==false&&g_bExit==false){R();};return TRUE;
			}
		case 40:
			{
				if(g_bPause==false&&g_bExit==false){Do();};return TRUE;
			}
		default:return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CGame_LTYDlg::L(void)
{
// 	CDC * pcdc = GetDC();
// 	CRect rect;
// 	GetDlgItem(IDC_Pic)->GetWindowRect(&rect);
// 	ScreenToClient(rect);
// 	LONG bx=rect.left;
// 	LONG by=rect.top;
// 
// 	CDC MemDC;  
// 	CBitmap MemBitmap;  
// 	MemDC.CreateCompatibleDC(NULL); 
// 	BOOL bRet = MemBitmap.CreateCompatibleBitmap(pcdc,PIC_SizeOfBlock_X,PIC_SizeOfBlock_Y);  
// 	BITMAP bm = {0};
// 	MemBitmap.GetObject(sizeof(BITMAP), &bm);
// 
// 	for(int i=0;i<PIC_SizeOfBlock_Y;i++)
// 	{
// 		for(int j=0;j<PIC_SizeOfBlock_X;j++)
// 		{
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+0] = (CLR_BACK&0x00ff0000)>>16;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+1] = (CLR_BACK&0x0000ff00)>>8;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+2] = (CLR_BACK&0x000000ff)>>0;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+3] = 0;
// 		}
// 	}
// 
// 	DWORD dwRet = MemBitmap.SetBitmapBits(PIC_SizeOfBlock_X*PIC_SizeOfBlock_Y*4,BLOCK_BIT);
// 	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);  
// 	pcdc->StretchBlt(bx+BLOCK_X,by+PIC_H,PIC_SizeOfBlock_X,PIC_SizeOfBlock_Y, &MemDC, 0, 0, PIC_SizeOfBlock_X,PIC_SizeOfBlock_Y, SRCCOPY );	
// 
// 	for(int i=0;i<PIC_SizeOfBlock_Y;i++)
// 	{
// 		for(int j=0;j<PIC_SizeOfBlock_X;j++)
// 		{
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+0] = (CLR_BLOCK&0x00ff0000)>>16;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+1] = (CLR_BLOCK&0x0000ff00)>>8;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+2] = (CLR_BLOCK&0x000000ff)>>0;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+3] = 0;
// 		}
// 	}

	if (BLOCK_X-(PIC_MoveSize_L)>=0)
	{
		//BLOCK_X_OLD = BLOCK_X;
		BLOCK_X = BLOCK_X-(PIC_MoveSize_L);
	}

// 	dwRet = MemBitmap.SetBitmapBits(PIC_SizeOfBlock_X*PIC_SizeOfBlock_Y*4,BLOCK_BIT);
// 	pOldBit = MemDC.SelectObject(&MemBitmap);  
// 	pcdc->StretchBlt(bx+BLOCK_X,by+PIC_H,PIC_SizeOfBlock_X,PIC_SizeOfBlock_Y, &MemDC, 0, 0, PIC_SizeOfBlock_X,PIC_SizeOfBlock_Y, SRCCOPY );	

	return;
}

void CGame_LTYDlg::R(void)
{
// 	CDC * pcdc = GetDC();
// 	CRect rect;
// 	GetDlgItem(IDC_Pic)->GetWindowRect(&rect);
// 	ScreenToClient(rect);
// 	LONG bx=rect.left;
// 	LONG by=rect.top;
// 
// 	CDC MemDC;  
// 	CBitmap MemBitmap;  
// 	MemDC.CreateCompatibleDC(NULL); 
// 	BOOL bRet = MemBitmap.CreateCompatibleBitmap(pcdc,PIC_SizeOfBlock_X,PIC_SizeOfBlock_Y);  
// 	BITMAP bm = {0};
// 	MemBitmap.GetObject(sizeof(BITMAP), &bm);
// 
// 	for(int i=0;i<PIC_SizeOfBlock_Y;i++)
// 	{
// 		for(int j=0;j<PIC_SizeOfBlock_X;j++)
// 		{
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+0] = (CLR_BACK&0x00ff0000)>>16;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+1] = (CLR_BACK&0x0000ff00)>>8;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+2] = (CLR_BACK&0x000000ff)>>0;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+3] = 0;
// 		}
// 	}
// 
// 	DWORD dwRet = MemBitmap.SetBitmapBits(PIC_SizeOfBlock_X*PIC_SizeOfBlock_Y*4,BLOCK_BIT);
// 	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);  
// 	pcdc->StretchBlt(bx+BLOCK_X,by+PIC_H,PIC_SizeOfBlock_X,PIC_SizeOfBlock_Y, &MemDC, 0, 0, PIC_SizeOfBlock_X,PIC_SizeOfBlock_Y, SRCCOPY );
// 
// 	for(int i=0;i<PIC_SizeOfBlock_Y;i++)
// 	{
// 		for(int j=0;j<PIC_SizeOfBlock_X;j++)
// 		{
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+0] = (CLR_BLOCK&0x00ff0000)>>16;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+1] = (CLR_BLOCK&0x0000ff00)>>8;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+2] = (CLR_BLOCK&0x000000ff)>>0;
// 			BLOCK_BIT[i*PIC_SizeOfBlock_X*4+j*4+3] = 0;
// 		}
// 	}

	if (BLOCK_X+(PIC_MoveSize_R)<=PIC_W-PIC_SizeOfPlayer_X)
	{
		//BLOCK_X_OLD = BLOCK_X;
		BLOCK_X = BLOCK_X+(PIC_MoveSize_R);
	}
	
// 	dwRet = MemBitmap.SetBitmapBits(PIC_SizeOfBlock_X*PIC_SizeOfBlock_Y*4,BLOCK_BIT);
// 	pOldBit = MemDC.SelectObject(&MemBitmap);  
// 	pcdc->StretchBlt(bx+BLOCK_X,by+PIC_H,PIC_SizeOfBlock_X,PIC_SizeOfBlock_Y, &MemDC, 0, 0, PIC_SizeOfBlock_X, PIC_SizeOfBlock_Y,SRCCOPY );

	return;
}


void CGame_LTYDlg::INITPIC(void)
{
	BLOCK_BIT = new BYTE [PIC_SizeOfBlock_X*PIC_SizeOfBlock_Y*4];
	ZeroMemory(BLOCK_BIT,PIC_SizeOfBlock_X*PIC_SizeOfBlock_Y*4);
	
	BLOCK_X = 0;
	BLOCK_X_OLD = 0;
	BLOCK_Y = 0;
	BLOCK_Y_OLD = 0;
	DeadOrLive = false;
	seed = GetTickCount();
	Fast_cnt = 0;
	Slow_cnt = 0;
	b_Fast_ = true;
	b_Slow_ = true;
	PIC_SizeOfPlayer_X=(PIC_SizeOfBlock_X);
	PIC_SizeOfPlayer_Y=(PIC_SizeOfBlock_Y);
	PIC_MoveSize_L = PIC_SizeOfPlayer_X/2;
	PIC_MoveSize_R = PIC_SizeOfPlayer_X/2;

	//while(BLOCK_X!=PIC_W-PIC_SizeOfBlock_X)
	//{
	//	R();
	//}
	//while(BLOCK_X!=0)
	//{
	//	L();
	//}
}


void CGame_LTYDlg::Up(void)
{
	if (BLOCK_Y+PIC_SizeOfPlayer_Y<PIC_H)
	{
		BLOCK_Y = BLOCK_Y+PIC_SizeOfPlayer_Y;
	}
}


void CGame_LTYDlg::Do(void)
{
	if (BLOCK_Y-PIC_SizeOfPlayer_Y>=0)
	{
		BLOCK_Y = BLOCK_Y-PIC_SizeOfPlayer_Y;
	}
}


void CGame_LTYDlg::OnBnClickedButton3()
{
	CColorDialog cdlg(true);
	if(cdlg.DoModal()==IDOK)
	{
		CLR_BACK = cdlg.GetColor();	
		if(cdlg.DoModal()==IDOK)
		{
			CLR_BLOCK_DEAD = cdlg.GetColor();
			if(cdlg.DoModal()==IDOK)
			{
				CLR_BLOCK_LIVE = cdlg.GetColor();
			}
		}
	}
}

int Speed_cnt = 0;
void CGame_LTYDlg::OnBnClickedButton4()
{
	Speed_cnt++;
	switch(Speed_cnt)
	{
	case 1:
		{
			PIC_Speed_=1;
			SetDlgItemText(IDC_Speed,"VSlow");break;
		}
	case 2:
		{
			PIC_Speed_=2;
			SetDlgItemText(IDC_Speed,"Slow");break;
		}
	case 3:
		{
			PIC_Speed_=3;
			SetDlgItemText(IDC_Speed,"Normal");break;
		}
	case 4:
		{
			PIC_Speed_=4;
			SetDlgItemText(IDC_Speed,"Fast");break;
		}
	case 5:
		{
			PIC_Speed_=6;
			SetDlgItemText(IDC_Speed,"VFast");break;
		}
	case 6:
		{
			Speed_cnt = 1;
			PIC_Speed_=1;
			SetDlgItemText(IDC_Speed,"VSlow");break;
		}
	}
}
int Diff_cnt = 0;
void CGame_LTYDlg::OnBnClickedDiff2()
{
	Diff_cnt++;
	if(Diff_cnt>PIC_CNTBlock_X)
		Diff_cnt = 1;
	Random_X_CNT_ = Diff_cnt;
	CString str_diff;
	str_diff.Format("%d",Random_X_CNT_);
	SetDlgItemText(IDC_Diff_,str_diff);
}
