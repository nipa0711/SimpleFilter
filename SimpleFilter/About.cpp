// About.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "SimpleFilter.h"
#include "About.h"
#include "afxdialogex.h"


// CAbout ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAbout, CDialogEx)

CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAbout::IDD, pParent)
{

}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAbout, CDialogEx)
END_MESSAGE_MAP()


// CAbout �޽��� ó�����Դϴ�.
