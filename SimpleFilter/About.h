#pragma once


// CAbout ��ȭ �����Դϴ�.

class CAbout : public CDialogEx
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAbout();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
