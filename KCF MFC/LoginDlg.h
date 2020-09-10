#pragma once


// LoginDlg 대화 상자

class LoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LoginDlg)

public:
	LoginDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LoginDlg();

	CPoint pos;

	wchar_t httpURL[500] = L"http://";

	wchar_t ID[500];
	wchar_t Password[500];
	wchar_t LoginAction[500];
	wchar_t LoginActionInput[500];
	wchar_t bbsWrite[500];
	wchar_t bbsWriteInput[500];
	wchar_t bbsDelete[500];
	wchar_t bbsDeleteInput[500];

	char tmp[3000] = { "", };
	char* AttackCode[3000];

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KCFMFC_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	char* URLConvert(wchar_t* _url);
	wchar_t* ConverCtoWC(char* str);
	void Assignment();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLoginbutton();

};
