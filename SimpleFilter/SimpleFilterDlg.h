
// SimpleFilterDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSimpleFilterDlg 대화 상자
class CSimpleFilterDlg : public CDialogEx
{
	// 생성입니다.
public:
	CSimpleFilterDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_SIMPLEFILTER_DIALOG };

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
	afx_msg void OnOpen();
	string CStrToStr(CString str);
	afx_msg void OnExit();
	Mat OriginalMat, hist, currentMat;// GrayImg;
	CStatic ShowImgFrame;
	CDC *pDC1, *pDC2;
	HDC hDC1, hDC2;
	CvvImage m_CVvImageObj1, m_CVvHistogram;
	IplImage IplImage1, IplHistogram, IplFilterShow;
	CRect rect, rect2;
	int picWidth;
	int picHeight;
	void drawHistogram(Mat input);
	CStatic ShowHistogram;
	int histWidth;
	int histHeight;
	CListBox FilterList;
	void drawFilter();
	CBitmap* IplImageToCBitmap(IplImage* img);
	afx_msg void OnLbnSelchangeList();
	void adaptFilterImg(Mat input);
	Mat toGray(Mat input);
	Mat YCrCbHistogramEqual(Mat input);
	Mat BGRHistogramEqual(Mat input);
	Mat toLuv(Mat input);
	Mat toLab(Mat input);
	Mat toYCrCb(Mat input);
	Mat toXYZ(Mat input);
	afx_msg void OnFilesave();
	Mat toHLS(Mat input);
	Mat toThreshold(Mat input);
	afx_msg void OnMade();
	afx_msg void OnUpdateFilesave(CCmdUI *pCmdUI);
	Mat toCanny(Mat input);
	Mat toErode(Mat input);
	Mat toDilate(Mat input);
	Mat NipaFilterA1(Mat input);
	Mat NipaFilterA2(Mat input);
	Mat NipaFilterA3(Mat input);
	Mat NipaFilterB1(Mat input);
	Mat NipaFilterB2(Mat input);
	Mat NipaFilterB3(Mat input);
	Mat toInvert(Mat input);
	Mat toSobel(Mat input);
	Mat toLaplace(Mat input);
	Mat toMedianBlur(Mat input);
	Mat toGaussian(Mat input);
	Mat toUnSharp(Mat input);
	Mat toFlip(Mat input, int order);
	Mat toMiniature(Mat input);
	Mat toSepia(Mat input);
	Mat toDetailEnhance(Mat input);
	Mat toStylization(Mat input);
	Mat toColorOnly(Mat input, int select);
	Mat toVignetting(Mat input);
	Mat toDotPattern(Mat input);
	Mat toFisheye(Mat input);
	Mat toCartoonEffect(Mat input);
	Mat toAdaptiveLightnessHistogramEqualization(Mat input);
	Mat toAdaptiveRGBHistogramEqualization(Mat input);
	Mat toAdaptiveYCrCbHistogramEqualization(Mat input);
	Mat toAdaptiveSaturationHistogramEqualization(Mat input);
};
