#pragma once


// Attacking 대화 상자

class Attacking : public CDialogEx
{
	DECLARE_DYNAMIC(Attacking)

public:
	Attacking(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Attacking();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KCFMFC_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};
