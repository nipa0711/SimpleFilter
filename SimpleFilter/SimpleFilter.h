
// SimpleFilter.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include <opencv2\opencv.hpp>
#include "CvvImage.h"
#include <opencv2/ml/ml.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/world.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;


// CSimpleFilterApp:
// �� Ŭ������ ������ ���ؼ��� SimpleFilter.cpp�� �����Ͻʽÿ�.
//

class CSimpleFilterApp : public CWinApp
{
public:
	CSimpleFilterApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSimpleFilterApp theApp;