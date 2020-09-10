
// KCF MFCDlg.h: 헤더 파일
//

#pragma once

// CKCFMFCDlg 대화 상자
extern wchar_t url[500];
extern wchar_t Port[10];
extern bool xssisOpen;
class CKCFMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CKCFMFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	bool CheckedURL = false;
	bool URLisAvailable = false;
	CPoint pos;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KCFMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUrlcheckBtn();
	char* URLConvert(wchar_t* _url);
	wchar_t* ConverCtoWC(char* str);
	void LoadingDate();
	BOOL DestoryWindow();

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	CStatic LocalDate;
};
