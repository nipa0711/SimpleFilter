
// SimpleFilterDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "SimpleFilter.h"
#include "SimpleFilterDlg.h"
#include "afxdialogex.h"
#include "About.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSimpleFilterDlg ��ȭ ����



CSimpleFilterDlg::CSimpleFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSimpleFilterDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ShowImg, ShowImgFrame);
	DDX_Control(pDX, IDC_Histogram, ShowHistogram);
	DDX_Control(pDX, IDC_LIST, FilterList);
}

BEGIN_MESSAGE_MAP(CSimpleFilterDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FileOpen, &CSimpleFilterDlg::OnOpen)
	ON_COMMAND(ID_Exit, &CSimpleFilterDlg::OnExit)
	ON_LBN_SELCHANGE(IDC_LIST, &CSimpleFilterDlg::OnLbnSelchangeList)
	ON_COMMAND(ID_FileSave, &CSimpleFilterDlg::OnFilesave)
	ON_COMMAND(ID_MADE, &CSimpleFilterDlg::OnMade)
	ON_UPDATE_COMMAND_UI(ID_FileSave, &CSimpleFilterDlg::OnUpdateFilesave)
END_MESSAGE_MAP()


// CSimpleFilterDlg �޽��� ó����

BOOL CSimpleFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CStatic *staticSize = (CStatic *)GetDlgItem(IDC_ShowImg);
	CStatic *staticSize2 = (CStatic *)GetDlgItem(IDC_Histogram);
	staticSize->GetClientRect(rect);
	staticSize2->GetClientRect(rect2);
	picWidth = rect.Width();
	picHeight = rect.Height();
	histWidth = rect2.Width();
	histHeight = rect2.Height();
	drawFilter();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CSimpleFilterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CSimpleFilterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		rect = CRect(0, 0, picWidth, picHeight);
		pDC1 = ShowImgFrame.GetDC();
		hDC1 = pDC1->GetSafeHdc();	

		rect2 = CRect(0, 0, histWidth, histHeight);
		pDC2 = ShowHistogram.GetDC();
		hDC2 = pDC2->GetSafeHdc();

		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CSimpleFilterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSimpleFilterDlg::OnOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Image(*.BMP,*.JPG,*.PNG)|*.BMP;*.JPG;*.PNG|All Files(*.*)|*.*||"));
	if (IDOK == dlg.DoModal()) 
	{
		CString strPathName = dlg.GetPathName();
		OriginalMat = imread(CStrToStr(strPathName));	

		IplImage1 = OriginalMat;
		IplFilterShow = OriginalMat;
		m_CVvImageObj1.CopyOf(&IplImage1);
		m_CVvImageObj1.DrawToHDC(hDC1, &rect);
		drawHistogram(OriginalMat);
		FilterList.EnableWindow(TRUE);
		CMenu *menu = (CMenu*)GetMenu();
			// This will disable
		menu->EnableMenuItem(ID_FileSave /*your menu ID*/, MF_ENABLED);
	}	
	
	//Invalidate(TRUE);
	//CDialogEx::OnPaint();
}


string CSimpleFilterDlg::CStrToStr(CString str)
{
	string outputStr = string(CT2CA(str.operator LPCWSTR()));
	return outputStr;
}

void CSimpleFilterDlg::OnExit()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CSimpleFilterDlg::OnCancel();
}

void CSimpleFilterDlg::drawHistogram(Mat input)
{
	currentMat = input;
	int histSize = 255;
	long int dim;
	Mat histImage, grayImg;

	if (input.channels()==3)
	{
		cvtColor(input, grayImg, CV_BGR2GRAY);
	}
	else
	{
		grayImg = input;
	}	

	calcHist(&grayImg, 1, 0, Mat(), histImage, 1, &histSize, 0);

	dim = grayImg.rows * grayImg.cols;
	hist = Mat::ones(255, 255, CV_8U) * 255;

	normalize(histImage, histImage, 0, hist.rows, CV_MINMAX, CV_32F);
	
	hist = Scalar::all(255);
	int binW = cvRound((double)hist.cols / histSize);

	for (int i = 0; i < histSize;i++)
	{
		rectangle(hist, Point(i*binW, hist.rows), Point((i + 1)*binW, hist.rows - cvRound(histImage.at<float>(i))), Scalar::all(0), -1, 8, 0);
	}

	IplHistogram = hist;
	m_CVvHistogram.CopyOf(&IplHistogram);
	m_CVvHistogram.DrawToHDC(hDC2, &rect2);	
}

void CSimpleFilterDlg::drawFilter()
{
	FilterList.AddString(L"����");
	FilterList.AddString(L"���� ���� �յ�ȭ");
	FilterList.AddString(L"��⿡ ���� �յ�ȭ");
	FilterList.AddString(L"��鿵��");
	FilterList.AddString(L"Luv");
	FilterList.AddString(L"Lab");
	FilterList.AddString(L"YCrCb");
	FilterList.AddString(L"XYZ");
	FilterList.AddString(L"HLS");
	FilterList.AddString(L"����ȭ");
	FilterList.AddString(L"Canny");
	FilterList.AddString(L"Erode");
	FilterList.AddString(L"Dilate");
	FilterList.AddString(L"���� ���� A -��");
	FilterList.AddString(L"���� ���� A -��");
	FilterList.AddString(L"���� ���� A -��");
	FilterList.AddString(L"���� ���� B -��");
	FilterList.AddString(L"���� ���� B -��");
	FilterList.AddString(L"���� ���� B -��");
	FilterList.AddString(L"���� ����");
	FilterList.AddString(L"Sobel");
	FilterList.AddString(L"Laplace");
	FilterList.AddString(L"MedianBlur");
	FilterList.AddString(L"Gaussian");
	FilterList.AddString(L"�����ϰ�");
	FilterList.AddString(L"�¿��Ī");
	FilterList.AddString(L"���ϴ�Ī");
	FilterList.AddString(L"�̴Ͼ��� ȿ��");
	FilterList.AddString(L"���Ǿ�");
	FilterList.AddString(L"������ ����");
	FilterList.AddString(L"Stylization");
	FilterList.AddString(L"���� ����");
	FilterList.AddString(L"�ʷ� ����");
	FilterList.AddString(L"�Ķ� ����");
	FilterList.AddString(L"�����");
}

CBitmap* CSimpleFilterDlg::IplImageToCBitmap(IplImage* img)
{
	CDC dc;
	CDC memDC;

	if (!dc.CreateDC(L"DISPLAY", NULL, NULL, NULL))
		return NULL;

	if (!memDC.CreateCompatibleDC(&dc))
		return NULL;

	CBitmap* bmp = new CBitmap();
	CBitmap* pOldBitmap;

	bmp->CreateCompatibleBitmap(&dc, img->width, img->height);
	pOldBitmap = memDC.SelectObject(bmp);

	CvvImage cvImage; // you will need OpenCV_2.2.0- to use CvvImage 
	cvImage.CopyOf(img);
	cvImage.Show(memDC.m_hDC, 0, 0, img->width, img->height, 0, 0);
	cvImage.Destroy();

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	dc.DeleteDC();

	return bmp;
}

void CSimpleFilterDlg::OnLbnSelchangeList()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nList = 0;
	nList = FilterList.GetCurSel();

	switch (nList)
	{
	case 0:
		adaptFilterImg(OriginalMat);
		break;
	case 1:
		adaptFilterImg(BGRHistogramEqual(OriginalMat));
		break;
	case 2:
		adaptFilterImg(YCrCbHistogramEqual(OriginalMat));
		break;
	case 3:
		adaptFilterImg(toGray(OriginalMat));
		break;
	case 4:
		adaptFilterImg(toLuv(OriginalMat));
		break;
	case 5:
		adaptFilterImg(toLab(OriginalMat));
		break;
	case 6:
		adaptFilterImg(toYCrCb(OriginalMat));
		break;
	case 7:
		adaptFilterImg(toXYZ(OriginalMat));
		break;
	case 8:
		adaptFilterImg(toHLS(OriginalMat));
		break;
	case 9:
		adaptFilterImg(toThreshold(OriginalMat));
		break;
	case 10:
		adaptFilterImg(toCanny(OriginalMat));
		break;
	case 11:
		adaptFilterImg(toErode(OriginalMat));
		break;
	case 12:
		adaptFilterImg(toDilate(OriginalMat));
		break;
	case 13:
		adaptFilterImg(NipaFilterA1(OriginalMat));
		break;
	case 14:
		adaptFilterImg(NipaFilterA2(OriginalMat));
		break;
	case 15:
		adaptFilterImg(NipaFilterA3(OriginalMat));
		break;
	case 16:
		adaptFilterImg(NipaFilterB1(OriginalMat));
		break;
	case 17:
		adaptFilterImg(NipaFilterB2(OriginalMat));
		break;
	case 18:
		adaptFilterImg(NipaFilterB3(OriginalMat));
		break;
	case 19:
		adaptFilterImg(toInvert(OriginalMat));
		break;
	case 20:
		adaptFilterImg(toSobel(OriginalMat));
		break;
	case 21:
		adaptFilterImg(toLaplace(OriginalMat));
		break;
	case 22:
		adaptFilterImg(toMedianBlur(OriginalMat));
		break;
	case 23:
		adaptFilterImg(toGaussian(OriginalMat));
		break;
	case 24:
		adaptFilterImg(toUnSharp(OriginalMat));
		break;
	case 25:
		adaptFilterImg(toFlip(OriginalMat,1));
		break;
	case 26:
		adaptFilterImg(toFlip(OriginalMat, 0));
		break;
	case 27:
		adaptFilterImg(toMiniature(OriginalMat));
		break;
	case 28:
		adaptFilterImg(toSepia(OriginalMat));
		break;
	case 29:
		adaptFilterImg(toDetailEnhance(OriginalMat));
		break;
	case 30:
		adaptFilterImg(toStylization(OriginalMat));
		break;
	case 31:
		adaptFilterImg(toColorOnly(OriginalMat,1));
		break;
	case 32:
		adaptFilterImg(toColorOnly(OriginalMat, 2));
		break;
	case 33:
		adaptFilterImg(toColorOnly(OriginalMat, 3));
		break;
	case 34:
		adaptFilterImg(toVignetting(OriginalMat));
		break;
	default:
		break;
	}
}

void CSimpleFilterDlg::adaptFilterImg(Mat input)
{
	IplImage img = input;
	m_CVvImageObj1.CopyOf(&img);
	m_CVvImageObj1.DrawToHDC(hDC1, &rect);
	drawHistogram(input);
	
}

Mat CSimpleFilterDlg::toGray(Mat input)
{
	Mat GrayImg;
	cvtColor(input, GrayImg, CV_BGR2GRAY);
	return GrayImg;
}

Mat CSimpleFilterDlg::YCrCbHistogramEqual(Mat input)
{
	Mat afterImg;
	vector<Mat>channels;
	cvtColor(input, afterImg, CV_BGR2YCrCb);
	split(afterImg, channels);
	equalizeHist(channels[0], channels[0]);
	merge(channels, afterImg);
	cvtColor(afterImg, afterImg, CV_YCrCb2BGR);

	return afterImg;
}

Mat CSimpleFilterDlg::BGRHistogramEqual(Mat input)
{
	Mat afterImg;
	input.copyTo(afterImg);
	vector<Mat>channels;
	split(afterImg, channels);
	equalizeHist(channels[0], channels[0]);
	equalizeHist(channels[1], channels[1]);
	equalizeHist(channels[2], channels[2]);
	merge(channels, afterImg);

	return afterImg;
}

Mat CSimpleFilterDlg::toLuv(Mat input)
{
	Mat luv;
	cvtColor(input, luv, CV_BGR2Luv);
	return luv;
}

Mat CSimpleFilterDlg::toLab(Mat input)
{
	Mat lab;
	cvtColor(input, lab, CV_BGR2Lab);
	return lab;
}

Mat CSimpleFilterDlg::toYCrCb(Mat input)
{
	Mat YCrCb;
	cvtColor(input, YCrCb, CV_BGR2YCrCb);
	return YCrCb;
}

Mat CSimpleFilterDlg::toXYZ(Mat input)
{
	Mat XYZ;
	cvtColor(input, XYZ, CV_BGR2XYZ);
	return XYZ;
}

void CSimpleFilterDlg::OnFilesave()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog dlg(FALSE, _T("*.jpg"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("JPG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp|PNG(*.png)|*.png|All Files(*.*)|*.*||"));

	if (IDOK == dlg.DoModal())
	{
		CString strFolderPath = dlg.GetFolderPath();
		CString strFileName = dlg.GetFileName();
		CString strFileExtension = dlg.GetFileExt();
		imwrite(CStrToStr(strFolderPath) + "\\" + CStrToStr(strFileName), currentMat);	
	}
}

Mat CSimpleFilterDlg::toHLS(Mat input)
{
	Mat HLS;
	cvtColor(input, HLS, CV_BGR2HLS);
	return HLS;
}

Mat  CSimpleFilterDlg::toThreshold(Mat input)
{
	Mat thresholdMat;
	cvtColor(input, thresholdMat, CV_BGR2GRAY);
	threshold(thresholdMat, thresholdMat, 125, 255, THRESH_BINARY);

	return thresholdMat;
}

void CSimpleFilterDlg::OnMade()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CAbout dlg;
	dlg.DoModal();
}


void CSimpleFilterDlg::OnUpdateFilesave(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->Enable(TRUE);
}

Mat CSimpleFilterDlg::toCanny(Mat input)
{
	Mat src, src_gray;
	Mat dst, detected_edges;

	int edgeThresh = 1;
	int lowThreshold=50;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;

	src = input;
	dst.create(src.size(), src.type());
	cvtColor(src, src_gray, CV_BGR2GRAY);

	blur(src_gray, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);

	return dst;
}

Mat CSimpleFilterDlg::toErode(Mat input)
{
	Mat temp;
	int erosion_size = 6;
	Mat element = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	erode(input, temp, element);

	return temp;
}

Mat CSimpleFilterDlg::toDilate(Mat input)
{
	Mat temp;
	int erosion_size = 6;
	Mat element = getStructuringElement(cv::MORPH_ELLIPSE,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));

	dilate(input, temp, element);

	return temp;
}

Mat CSimpleFilterDlg::NipaFilterA1(Mat input)
{
	Mat temp, dst;

	input.copyTo(temp);
	dst = BGRHistogramEqual(input);

	addWeighted(input, 0.25, dst, 0.75, 0.0, temp);

	return temp;
}

Mat CSimpleFilterDlg::NipaFilterA2(Mat input)
{
	Mat temp, dst;

	input.copyTo(temp);
	dst = BGRHistogramEqual(input);

	addWeighted(input, 0.5, dst, 0.5, 0.0, temp);

	return temp;
}

Mat CSimpleFilterDlg::NipaFilterA3(Mat input)
{
	Mat temp, dst;

	input.copyTo(temp);
	dst = BGRHistogramEqual(input);

	addWeighted(input, 0.75, dst, 0.25, 0.0, temp);

	return temp;
}

Mat CSimpleFilterDlg::NipaFilterB1(Mat input)
{
	Mat temp, dst;

	input.copyTo(temp);
	dst = YCrCbHistogramEqual(input);

	addWeighted(input, 0.25, dst, 0.75, 0.0, temp);

	return temp;
}

Mat CSimpleFilterDlg::NipaFilterB2(Mat input)
{
	Mat temp, dst;

	input.copyTo(temp);
	dst = YCrCbHistogramEqual(input);

	addWeighted(input, 0.5, dst, 0.5, 0.0, temp);
	
	return temp;
}

Mat CSimpleFilterDlg::NipaFilterB3(Mat input)
{
	Mat temp, dst;

	input.copyTo(temp);
	dst = YCrCbHistogramEqual(input);

	addWeighted(input, 0.75, dst, 0.25, 0.0, temp);

	return temp;
}

Mat CSimpleFilterDlg::toInvert(Mat input)
{
	Mat temp;
	bitwise_not(input, temp);

	return temp;
}

Mat CSimpleFilterDlg::toSobel(Mat input)
{
	Mat src, src_gray;
	Mat grad;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	input.copyTo(src);
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	/// Convert it to gray
	cvtColor(src, src_gray, CV_RGB2GRAY);

	/// Generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	
	return grad;
}

Mat CSimpleFilterDlg::toLaplace(Mat input)
{
	Mat src, src_gray, dst;
	int kernel_size = 5;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	input.copyTo(src);

	/// Remove noise by blurring with a Gaussian filter
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// Convert the image to grayscale
	cvtColor(src, src_gray, CV_RGB2GRAY);

	/// Apply Laplace function
	Mat abs_dst;

	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	return abs_dst;
}

Mat CSimpleFilterDlg::toMedianBlur(Mat input)
{
	Mat src, dst;
	input.copyTo(src);

	medianBlur(src, dst, 15);

	return dst;
}

Mat CSimpleFilterDlg::toGaussian(Mat input)
{
	Mat src;
	input.copyTo(src);
	GaussianBlur(src, src, Size(9, 9), 0, 0, BORDER_DEFAULT);
	return src;
}

Mat CSimpleFilterDlg::toUnSharp(Mat input)
{
	Mat src;
	input.copyTo(src);
	GaussianBlur(src, src, Size(7, 7),5);
	addWeighted(input, 1.5, src, -0.5, 0, src);
	return src;
}

Mat CSimpleFilterDlg::toFlip(Mat input, int order)
{
	Mat dst;
	flip(input, dst, order);
	return dst;
}

Mat CSimpleFilterDlg::toMiniature(Mat input)
{
	Mat dst;
	//input.copyTo(dst);
	dst = input.clone();
	int dstWidth, dstHeight;
	dstHeight = dst.rows; // ��ü ����
	dstWidth = dst.cols; // ��ü ��

	int pointHeight = dstHeight / 9;

		Rect region_of_interest = Rect(0, 0, dstWidth, pointHeight);
		Mat roi = dst(region_of_interest);
		
		//GaussianBlur(roi, roi, Size(25, 25), 0, 0, BORDER_DEFAULT);
		blur(roi, roi, Size(23, 23), Point(-1, -1));
		
		region_of_interest = Rect(0, pointHeight, dstWidth, pointHeight);
		roi = dst(region_of_interest);
		//GaussianBlur(roi, roi, Size(17, 17), 0, 0, BORDER_DEFAULT);
		blur(roi, roi, Size(17, 17), Point(-1, -1));

		region_of_interest = Rect(0, pointHeight * 2, dstWidth, pointHeight);
		roi = dst(region_of_interest);
		//GaussianBlur(roi, roi, Size(11, 11), 0, 0, BORDER_DEFAULT);
		blur(roi, roi, Size(11, 11), Point(-1, -1));

		region_of_interest = Rect(0, pointHeight * 6, dstWidth, pointHeight);

		roi = dst(region_of_interest);
		//GaussianBlur(roi, roi, Size(9, 9), 0, 0, BORDER_DEFAULT);
		blur(roi, roi, Size(11, 11), Point(-1, -1));

		region_of_interest = Rect(0, pointHeight * 7, dstWidth, pointHeight);
		roi = dst(region_of_interest);
		//GaussianBlur(roi, roi, Size(17, 17), 0, 0, BORDER_DEFAULT);
		blur(roi, roi, Size(17, 17), Point(-1, -1));

		region_of_interest = Rect(0, pointHeight * 8, dstWidth, dstHeight - (pointHeight * 8));
		roi = dst(region_of_interest);
		//GaussianBlur(roi, roi, Size(25, 25), 0, 0, BORDER_DEFAULT);
		blur(roi, roi, Size(23, 23), Point(-1, -1));
		
	return dst;
}

Mat CSimpleFilterDlg::toSepia(Mat input)
{
	Mat temp;
	Mat kern = (cv::Mat_<float>(3, 3) << 
		0.131, 0.534, 0.272,  // B
		0.168, 0.686, 0.349,  // G
		0.189, 0.769, 0.393 // R
		);
	transform(input, temp, kern);

	return temp;
}

Mat CSimpleFilterDlg::toDetailEnhance(Mat input)
{
	Mat temp;
	detailEnhance(input, temp, 10.0f, 0.15f);
	return temp;
}

Mat CSimpleFilterDlg::toStylization(Mat input)
{
	Mat temp;
	stylization(input, temp, 60, 0.45f);
	return temp;
}

Mat CSimpleFilterDlg::toColorOnly(Mat input, int select) // 1 - Red, 2 - Green, 3 - Blue
{
	Mat show;
	Mat hsv;
	
	cvtColor(input, hsv, CV_BGR2HSV);
	input.copyTo(show);

	uchar r, g, b;
	uchar h, s, v;

	switch (select)
	{
	case 1:
		for (int y = 0; y < show.rows; ++y)
		{
			Vec3b* pixel = show.ptr<Vec3b>(y);
			Vec3b* pixelHSV = hsv.ptr<Vec3b>(y);

			for (int x = 0; x < show.cols; ++x)
			{
				r = pixel[x][2];
				g = pixel[x][1];
				b = pixel[x][0];

				h = pixelHSV[x][0];
				s = pixelHSV[x][1];
				v = pixelHSV[x][2];

				int sum = (r + g + b) / 3;

				//if (r>100 && b<25 && g <25)
				if (((h >= 0 && h <= 10) || (h >= 170 && h <= 179)) && (s >= 100 && s <= 255) && (v >=100 && v <= 255))
				{
					/*r = r;
					g = g;
					b = b;*/
				}
				else
				{
					pixel[x][2] = (uchar)sum;
					pixel[x][1] = (uchar)sum;
					pixel[x][0] = (uchar)sum;
				}
			}
		}
		break;
	case 2:
		for (int y = 0; y < show.rows; ++y)
		{
			Vec3b* pixel = show.ptr<Vec3b>(y);
			Vec3b* pixelHSV = hsv.ptr<Vec3b>(y);

			for (int x = 0; x < show.cols; ++x)
			{
				r = pixel[x][2];
				g = pixel[x][1];
				b = pixel[x][0];


				h = pixelHSV[x][0];
				s = pixelHSV[x][1];
				v = pixelHSV[x][2];

				int sum = (r + g + b) / 3;

				if ((h >= 40 && h <= 75) && (s >= 60 && s <= 255) && (v >= 60 && v <= 255))
				{
					/*r = r;
					g = g;
					b = b;*/
				}
				else
				{
					pixel[x][2] = (uchar)sum;
					pixel[x][1] = (uchar)sum;
					pixel[x][0] = (uchar)sum;
				}
			}
		}
		break;
	case 3:
		for (int y = 0; y < show.rows; ++y)
		{
			Vec3b* pixel = show.ptr<Vec3b>(y);
			Vec3b* pixelHSV = hsv.ptr<Vec3b>(y);

			for (int x = 0; x < show.cols; ++x)
			{
				r = pixel[x][2];
				g = pixel[x][1];
				b = pixel[x][0];


				h = pixelHSV[x][0];
				s = pixelHSV[x][1];
				v = pixelHSV[x][2];

				int sum = (r + g + b) / 3;

				//if (r>100 && b<25 && g <25)
				if ((h>=105 && h<=130) && (s >= 80 && s <= 255) && (v >= 80 && v <= 255))
				{
					/*r = r;
					g = g;
					b = b;*/
				}
				else
				{
					pixel[x][2] = (uchar)sum;
					pixel[x][1] = (uchar)sum;
					pixel[x][0] = (uchar)sum;
				}
			}
		}
		break;
	default:
		break;
	}	

	return show;
}

// Helper function to calculate the distance between 2 points.
double dist(CvPoint a, CvPoint b)
{
	return sqrt(pow((double)(a.x - b.x), 2) + pow((double)(a.y - b.y), 2));
}

// Helper function that computes the longest distance from the edge to the center point.
double getMaxDisFromCorners(const cv::Size& imgSize, const cv::Point& center)
{
	// given a rect and a line
	// get which corner of rect is farthest from the line

	std::vector<cv::Point> corners(4);
	corners[0] = cv::Point(0, 0);
	corners[1] = cv::Point(imgSize.width, 0);
	corners[2] = cv::Point(0, imgSize.height);
	corners[3] = cv::Point(imgSize.width, imgSize.height);

	double maxDis = 0;
	for (int i = 0; i < 4; ++i)
	{
		double dis = dist(corners[i], center);
		if (maxDis < dis)
			maxDis = dis;
	}

	return maxDis;
}

// Helper function that creates a gradient image.   
// firstPt, radius and power, are variables that control the artistic effect of the filter.
void generateGradient(cv::Mat& mask)
{
	cv::Point firstPt = cv::Point(mask.size().width / 2, mask.size().height / 2);
	double radius = 1.0;
	double power = 0.8;

	double maxImageRad = radius * getMaxDisFromCorners(mask.size(), firstPt);

	mask.setTo(cv::Scalar(1));
	for (int i = 0; i < mask.rows; i++)
	{
		for (int j = 0; j < mask.cols; j++)
		{
			double temp = dist(firstPt, cv::Point(j, i)) / maxImageRad;
			temp = temp * power;
			double temp_s = pow(cos(temp), 4);
			mask.at<double>(i, j) = temp_s;
		}
	}
}

Mat CSimpleFilterDlg::toVignetting(Mat input)
{
	Mat maskImg(input.size(), CV_64F);
	generateGradient(maskImg);

	Mat labImg(input.size(), CV_8UC3);
	cvtColor(input, labImg, CV_BGR2Lab);

	for (int row = 0; row < labImg.size().height; row++)
	{
		for (int col = 0; col < labImg.size().width; col++)
		{
			Vec3b value = labImg.at<Vec3b>(row, col);
			value.val[0] *= maskImg.at<double>(row, col);
			labImg.at<Vec3b>(row, col) = value;
		}
	}

	Mat output;
	cvtColor(labImg, output, CV_Lab2BGR);

	return output;
}