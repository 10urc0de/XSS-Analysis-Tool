// LoginDlg.cpp: 구현 파일
//
#include "pch.h"
#include "KCF MFC.h"
#include "KCF MFCDlg.h"
#include "LoginDlg.h"
#include "Attacking.h"
#include "afxdialogex.h"
#include "wchar.h"
#include "fstream""
#include "ostream"
#include "Loading.h"

#pragma warning(disable : 4996)
//// LoginDlg 대화 상자

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)
using namespace std;

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KCFMFC_DIALOG2, pParent)
{
	if (wcslen(Port) > 0)
	{
		wcscat(url, L":");
		wcscat(url, Port);
	}
	wcscat(url, L"/");
	wcscat(httpURL, url);

	LoadingCancel = false;
	//CRect rect;
	//GetClientRect(&rect);
	//pos.x = GetSystemMetrics(SM_CXSCREEN) / 2.0f - rect.Width() / 2.0f;
	//pos.y = GetSystemMetrics(SM_CYSCREEN) / 2.0f - rect.Height() / 2.0f;
}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_LoginButton, &LoginDlg::OnBnClickedLoginbutton)
END_MESSAGE_MAP()


char* LoginDlg::URLConvert(wchar_t* _url)
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

void LoginDlg::Assignment()
{
	ifstream Attacks;
	
	int len = 0;
	int i = 0;

	if (xssisOpen) {
		Attacks.open("xssKrolling.txt",ios_base::in);

		while (!Attacks.eof())
		{
			Attacks.getline(tmp, 3000);
			len = strlen(tmp) + 1;
			AttackCode[i] = (char*)malloc(sizeof(char) * len);
			strcpy(AttackCode[i], tmp);
			i++;
		}
		Attacks.close();
	}
	else {

		remove("xssKrolling.txt");
		WinExec("xssKrolling.exe", SW_HIDE);

		ifstream CheckStatus;

		bool LoadingData = true;

		while (LoadingData)
		{
			CheckStatus.open("xssKrolling.txt");

			if (CheckStatus.is_open())
			{
				LoadingData = false;
				CheckStatus.close();

				xssisOpen = true;

			}
		}
		Attacks.open("xssKrolling.txt", ios_base::in);

		while (!Attacks.eof())
		{
			Attacks.getline(tmp, 3000);
			len = strlen(tmp) + 1;
			AttackCode[i] = (char*)malloc(sizeof(char) * len);
			strcpy(AttackCode[i], tmp);
			i++;
		}
		Attacks.close();
	}
}

wchar_t* LoginDlg::ConverCtoWC(char* str)
{
	wchar_t* pStr;
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	pStr = new WCHAR[strSize];
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);

	return pStr;
}

BOOL LoginDlg::OnInitDialog()
{
	//AfxGetApp()->m_pMainWnd->DestroyWindow();
	return TRUE;
}

void LoginDlg::OnBnClickedLoginbutton()
{
	Loading* LoadingWindow = new Loading;
	LoadingWindow->Create(IDD_KCFMFC_DIALOG3);
	LoadingWindow->ShowWindow(SW_SHOW);

	Assignment();

	GetDlgItemText(IDC_INPUT_ID, ID, 500);
	GetDlgItemText(IDC_INPUT_PASSWORD, Password, 500);
	GetDlgItemText(IDC_INPUT_PATH, LoginActionInput, 500);
	GetDlgItemText(IDC_INPUT_PATH2, bbsWriteInput, 500);

	wcscpy(LoginAction, httpURL);
	wcscpy(bbsWrite, httpURL);

	wcscat(LoginAction,LoginActionInput);
	wcscat(bbsWrite, bbsWriteInput);

	wchar_t view[1000] = { NULL, };

	if (wcslen(ID) == 0 || wcslen(Password) == 0 || wcslen(LoginActionInput) == 0
		|| wcslen(bbsWriteInput) == 0)
	{
		MessageBox(L"Check input value");
	}
	else
	{
		wcscat(ID,L" ");
		wcscat(Password, L" ");
		wcscat(LoginAction, L" ");
		wcscat(bbsWrite, L" ");

		int i = 0;
		char number[10] = { NULL, };
		wchar_t ExcuteCode[4000];

		ifstream CheckStatus;
		ofstream AttackSuccess;

		bool LoadingData = true;

		system("del AttackSuccess.txt");
		AttackSuccess.open("AttackSuccess.txt", ios::app);

		while(AttackCode[i] != nullptr)
		{
			if (LoadingCancel)
				return;

			system("del Content.txt");
			wcscpy(view, L"");

			wcscpy(ExcuteCode, L"python writeContent.py ");
			wcscat(ExcuteCode, ID);
			wcscat(ExcuteCode, Password);
			wcscat(ExcuteCode, L" \"");
			wcscat(ExcuteCode, ConverCtoWC(AttackCode[i]));
			wcscat(ExcuteCode, L"\" ");
			wcscat(ExcuteCode, LoginAction);
			wcscat(ExcuteCode, bbsWrite);
			
			sprintf(number,"%d",i + 1);
			wcscat(ExcuteCode, ConverCtoWC(number));

			wcscat(view, L" ");
			wcscat(view, httpURL);
			wcscat(view, L"/view/view.jsp?bbsID=");
			wcscat(view, ConverCtoWC(number));
			wcscat(ExcuteCode, view);

			WinExec(URLConvert(ExcuteCode), SW_HIDE);
			Sleep(2500);

			LoadingData = true;
			while (LoadingData)
			{
				CheckStatus.open("Content.txt",ios::in);
				if (CheckStatus.is_open())
				{
					LoadingData = false;
					while (!CheckStatus.eof())
					{
						strcpy(tmp, "");
						CheckStatus.getline(tmp, 3000); 
						if (strstr(tmp, AttackCode[i]) != NULL)
						{
							AttackSuccess << "bbsID:";
							AttackSuccess << i + 1;
							AttackSuccess << " AttackCode:";
							AttackSuccess << AttackCode[i];
							AttackSuccess << " link:";
							AttackSuccess << URLConvert(view) << endl;
						}
 					}
					CheckStatus.close();
				}
			}
			Sleep(2500);
			i++;
		}
		//system(URLConvert(ExcuteCode));
		AttackSuccess.close();
		MessageBox(L"Complete");
		EnableWindow(TRUE);
	}
}
