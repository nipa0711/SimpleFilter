#pragma once


// CAbout 대화 상자입니다.

class CAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAbout();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
