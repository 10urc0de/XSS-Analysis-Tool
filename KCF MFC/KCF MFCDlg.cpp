// KCF MFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "KCF MFC.h"
#include "KCF MFCDlg.h"
#include "afxdialogex.h"
#include "CPopUp.h"
#include "WinInet.h"
#include "happyhttp.h"
#include "LoginDlg.h"
#pragma comment(lib,"WinInet.lib")

using namespace std;
#include <string>
#include <fstream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4996)
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

wchar_t url[500];
wchar_t Port[10];
bool xssisOpen = false;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CKCFMFCDlg 대화 상자



CKCFMFCDlg::CKCFMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KCFMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKCFMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, LocalDate);
}

BEGIN_MESSAGE_MAP(CKCFMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_URLCHECK_BTN, &CKCFMFCDlg::OnBnClickedUrlcheckBtn)
	ON_BN_CLICKED(IDC_CHECK1, &CKCFMFCDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CKCFMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CKCFMFCDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CKCFMFCDlg 메시지 처리기


BOOL CKCFMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CRect rect;
	GetClientRect(&rect);
	pos.x = GetSystemMetrics(SM_CXSCREEN) / 2.0f - rect.Width() / 2.0f;
	pos.y = GetSystemMetrics(SM_CYSCREEN) / 2.0f - rect.Height() / 2.0f;

	SetWindowPos(NULL, pos.x, pos.y, 0, 0, SWP_NOSIZE);

	LoadingDate();
	
	return TRUE;
}

void CKCFMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CKCFMFCDlg::OnPaint()
{
		if (IsIconic())
		{
			CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

			SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

			// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
			int cxIcon = GetSystemMetrics(SM_CXICON);
			int cyIcon = GetSystemMetrics(SM_CYICON);
			CRect rect;
			GetClientRect(&rect);
			int x = (rect.Width() - cxIcon + 1) / 2;
			int y = (rect.Height() - cyIcon + 1) / 2;

			// 아이콘을 그립니다.
			dc.DrawIcon(x, y, m_hIcon);
		}
		else
		{
			CDialogEx::OnPaint();
		}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CKCFMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

char* CKCFMFCDlg::URLConvert(wchar_t* _url)
{
	//반환할 char* 변수 선언
	char* pStr;

	//입력받은 wchar_t 변수의 길이를 구함
	int strSize = WideCharToMultiByte(CP_ACP, 0, _url, -1, NULL, 0, NULL, NULL);
	//char* 메모리 할당
	pStr = new char[strSize];

	//형 변환 
	WideCharToMultiByte(CP_ACP, 0, _url, -1, pStr, strSize, 0, 0);

	return pStr;
}

wchar_t* CKCFMFCDlg::ConverCtoWC(char* str)
{
	//wchar_t형 변수 선언
	wchar_t* pStr;

	//멀티 바이트 크기 계산 길이 반환
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

	//wchar_t 메모리 할당
	pStr = new WCHAR[strSize];

	//형 변환
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
	return pStr;
}

void  CKCFMFCDlg::LoadingDate()
{
	DWORD dwFlag;
	if (!InternetCheckConnection(L"http://google.com", FLAG_ICC_FORCE_CONNECTION, NULL))
	{
		MessageBox(L"No Internet Connection");
		EndDialog(WM_CLOSE);
	}
	else
	{
		CPopUp* pDialog = NULL; // 팝업 다이얼로그 용도로 생성한 클래스
		pDialog = new CPopUp(this);
		pDialog->Create(IDD_KCFMFC_DIALOG1, NULL);
		pDialog->SetWindowPos(NULL, pos.x, pos.y, 0, 0, SWP_NOSIZE);
		pDialog->ShowWindow(SW_SHOW);
		
		remove("localDate.txt");
		WinExec("localDate.exe", SW_SHOW);

		ifstream CheckStatus;
		char LocalDate[20] = { 0, };
		char TextOutput[40] = "Cheat Sheet Last Updated : ";
		CheckStatus.open("localDate.txt");

		if (CheckStatus.is_open())
			CheckStatus.getline(LocalDate, 100);

		strcat(TextOutput, LocalDate);

		SetDlgItemText(IDC_STATIC1, ConverCtoWC(TextOutput));
		CheckStatus.close();

		pDialog->DestroyWindow();
		delete pDialog;
		pDialog = NULL;

		EnableWindow(TRUE);
	}
}

BOOL CKCFMFCDlg::DestoryWindow()
{
	return CDialogEx::DestroyWindow();
}

void CKCFMFCDlg::OnBnClickedUrlcheckBtn()
{
	CheckedURL = true;
	GetDlgItemText(IDC_INPUT_URL_EDIT, url, 500);
	GetDlgItemText(IDC_INPUT_PORT,Port,10);
	wchar_t httpURL[550] = L"http://";
	wcscat(httpURL, url);

	if (wcslen(Port) > 0)
	{
		wcscat(httpURL, L":");
		wcscat(httpURL, Port);
	}
	if (InternetCheckConnection(httpURL, FLAG_ICC_FORCE_CONNECTION, NULL))
	{
		MessageBox(L"Web Server is Connectable");
		URLisAvailable = true;
	}
	else
	{
		MessageBox(L"Web Server is Not Connectable");
		URLisAvailable = false;
	}

	//remove("response.txt");
	//char* ConvertedURL = URLConvert(url);
	////string Command = "python httpResponse.py http://";
	//string Command = "runResponse.bat http://";

	//Command.append(ConvertedURL);

	//const char* Excute = Command.c_str();

	////system(Excute);

	//ifstream CheckStatus;
	//CheckStatus.open("response.txt");

	//wchar_t* Connection_Complete = "Connect Server";
	//wchar_t* Connection_Complete = "Cannot Connect Server";
	/*if (CheckStatus.is_open())
	{
		MessageBox(L"Web Server is Connectable");
		URLisAvailable = true;
	}
	else
	{
		MessageBox(L"Web Server is Not Connectable");
		URLisAvailable = false;
	}*/
	//CheckStatus.close();
}

void CKCFMFCDlg::OnBnClickedCheck1()
{

}

void CKCFMFCDlg::OnBnClickedButton2()
{
	if (URLisAvailable)
	{
		if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) {
			LoginDlg LoginWindow;
			LoginWindow.DoModal();
		}
		else
			MessageBox(L"Check box is empty");
	}
	else
	{
		MessageBox(L"Please check URL");
	}
}

void CKCFMFCDlg::OnBnClickedButton4()
{
	CCmdTarget::BeginWaitCursor();

	CPopUp* pDialog = NULL; // 팝업 다이얼로그 용도로 생성한 클래스
	pDialog = new CPopUp(this);
	pDialog->Create(IDD_KCFMFC_DIALOG1, NULL);
	pDialog->SetWindowPos(NULL, pos.x, pos.y, 0, 0, SWP_NOSIZE);
	pDialog->ShowWindow(SW_SHOW);
	EnableWindow(FALSE);

	//remove("xssKrolling.txt");
	//WinExec("xssKrolling.exe", SW_HIDE);
	
	ifstream CheckStatus;

	bool LoadingData = true;
	
	while (LoadingData)
	{
		CheckStatus.open("xssKrolling.txt");

		if (CheckStatus.is_open())
		{
			LoadingData = false;
			WinExec("notepad xssKrolling.txt", SW_SHOW);
			CCmdTarget::EndWaitCursor();
			CheckStatus.close();

			pDialog->DestroyWindow();
			delete pDialog;
			pDialog = NULL;

			xssisOpen = true;

			EnableWindow(TRUE);
		}
	}
}
