#pragma once


// CPopUp 대화 상자

class CPopUp : public CDialogEx
{
	DECLARE_DYNAMIC(CPopUp)

public:
	CPopUp(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPopUp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KCFMFC_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
