// Loading.cpp: 구현 파일
//

#include "pch.h"
#include "KCF MFC.h"
#include "Loading.h"
#include "afxdialogex.h"


// Loading 대화 상자

IMPLEMENT_DYNAMIC(Loading, CDialogEx)

bool LoadingCancel;
Loading::Loading(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KCFMFC_DIALOG3, pParent)
{
	LoadingCancel = false;
}

Loading::~Loading()
{
}

void Loading::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Loading, CDialogEx)
END_MESSAGE_MAP()


// Loading 메시지 처리기
