// Attacking.cpp: 구현 파일
//

#include "pch.h"
#include "KCF MFC.h"
#include "Attacking.h"
#include "afxdialogex.h"


// Attacking 대화 상자

IMPLEMENT_DYNAMIC(Attacking, CDialogEx)

Attacking::Attacking(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KCFMFC_DIALOG3, pParent)
{

}

Attacking::~Attacking()
{
}

void Attacking::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL Attacking::OnInitDialog()
{
	SetWindowText(L"Please Wait");
	return 0;
}



BEGIN_MESSAGE_MAP(Attacking, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Attacking::OnBnClickedButton1)
END_MESSAGE_MAP()


// Attacking 메시지 처리기


void Attacking::OnBnClickedButton1()
{
}
