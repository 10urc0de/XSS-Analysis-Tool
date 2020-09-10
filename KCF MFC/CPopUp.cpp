// CPopUp.cpp: 구현 파일
//

#include "pch.h"
#include "KCF MFC.h"
#include "CPopUp.h"
#include "afxdialogex.h"


// CPopUp 대화 상자

IMPLEMENT_DYNAMIC(CPopUp, CDialogEx)

CPopUp::CPopUp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KCFMFC_DIALOG1, pParent)
{
}

CPopUp::~CPopUp()
{
}

void CPopUp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CPopUp::OnInitDialog()
{
	SetWindowText(L"Please Wait");
	return 0;
}


BEGIN_MESSAGE_MAP(CPopUp, CDialogEx)
END_MESSAGE_MAP()


// CPopUp 메시지 처리기
