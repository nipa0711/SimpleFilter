// About.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SimpleFilter.h"
#include "About.h"
#include "afxdialogex.h"


// CAbout 대화 상자입니다.

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


// CAbout 메시지 처리기입니다.
