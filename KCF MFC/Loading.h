#pragma once


// Loading 대화 상자

extern bool LoadingCancel;
class Loading : public CDialogEx
{
	DECLARE_DYNAMIC(Loading)

public:
	Loading(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Loading();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KCFMFC_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
