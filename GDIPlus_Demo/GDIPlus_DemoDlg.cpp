// GDIPlus_DemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GDIPlus_Demo.h"
#include "GDIPlus_DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDIPlus_DemoDlg 对话框




CGDIPlus_DemoDlg::CGDIPlus_DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGDIPlus_DemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bgColor = GetSysColor(COLOR_3DFACE);
	m_bRedrawBkDC = TRUE;
	m_nPos = 45;
	m_startAngle = 45.0;
	//m_FillColor.nAlpha = 77;
	m_BorderHiColor.nAlpha = 255;
	m_BorderHiColor.color = RGB(0,0,255);
	m_BorderColor.nAlpha = 255;
	m_BorderColor.color = RGB(0,255,0);
	m_BackColor.nAlpha = 255;
	m_BackColor.color = RGB(255,128,0);
	m_TextColor.color = RGB(0,0,0);
	m_nEllipseAlpha = 255;
	m_nLeftMargin = 20;
	m_nTopMargin = 20;
	m_nEllipseWidth = 200;
	m_nEllipseHeight = 300;
	m_nRightPaddingClient = 290;
}

void CGDIPlus_DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_BORDER, m_btnCheckBorder);
	DDX_Control(pDX, IDC_CHECK_UPDATEMEMORY, m_btnCheckMemory);
	DDX_Control(pDX, IDC_STATIC_TIPS, m_staticTips);
	DDX_Control(pDX, IDC_SLIDER1, m_wndFillAlpha);
	DDX_Control(pDX, IDC_SLIDER3, m_wndBorder);
	DDX_Control(pDX, IDC_SLIDER2, m_wndBorderHight);
	DDX_Control(pDX, IDC_SLIDER4, m_wndTransAlpha);
	DDX_Control(pDX, IDC_SLIDER5, m_wndPos);
	DDX_Control(pDX, IDC_SLIDER6, m_wndTextTrans);
	DDX_Control(pDX, IDC_SLIDER7, m_wndSliderBack);
	DDX_Control(pDX, IDC_SPIN1, m_wndSpinLeft);
	DDX_Control(pDX, IDC_SPIN2, m_wndSpinTop);
	DDX_Control(pDX, IDC_SPIN3, m_wndSpinWidth);
	DDX_Control(pDX, IDC_SPIN4, m_wndSpinHeight);
}

BEGIN_MESSAGE_MAP(CGDIPlus_DemoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_CHECK_BORDER, &CGDIPlus_DemoDlg::OnBnClickedCheckBorder)
	ON_BN_CLICKED(IDC_BUTTON_CHANGEBGIMG, &CGDIPlus_DemoDlg::OnBnClickedButtonChangebgimg)
	ON_BN_CLICKED(IDC_BUTTON3, &CGDIPlus_DemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK_UPDATEMEMORY, &CGDIPlus_DemoDlg::OnBnClickedCheck1)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()

	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER1, &CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CGDIPlus_DemoDlg::OnNMCustomdrawSlider3)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER3, &CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider3)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER2, &CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider2)
	ON_BN_CLICKED(IDC_BUTTON_BODY, &CGDIPlus_DemoDlg::OnBnClickedButtonBody)
	ON_BN_CLICKED(IDC_BUTTON7, &CGDIPlus_DemoDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CGDIPlus_DemoDlg::OnBnClickedButton6)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER4, &CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider4)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER5, &CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider5)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER6, &CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider6)
	ON_BN_CLICKED(IDC_BUTTON8, &CGDIPlus_DemoDlg::OnBnClickedButton8)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER7, &CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider7)
	ON_BN_CLICKED(IDC_BUTTON_BODY2, &CGDIPlus_DemoDlg::OnBnClickedButtonBody2)
	ON_EN_CHANGE(IDC_EDIT_LEFT, &CGDIPlus_DemoDlg::OnEnChangeEditLeft)
	ON_EN_CHANGE(IDC_EDIT_TOP, &CGDIPlus_DemoDlg::OnEnChangeEditTop)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, &CGDIPlus_DemoDlg::OnEnChangeEditWidth)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, &CGDIPlus_DemoDlg::OnEnChangeEditHeight)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CGDIPlus_DemoDlg::OnNMClickSyslink1)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK2, &CGDIPlus_DemoDlg::OnNMClickSyslink2)
END_MESSAGE_MAP()


// CGDIPlus_DemoDlg 消息处理程序

BOOL CGDIPlus_DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CRect rectClient;
	GetClientRect(rectClient);
	m_wndSpinLeft.SetRange(2,800);
	m_wndSpinLeft.SetPos(20);
	m_wndSpinTop.SetRange(2,800);
	m_wndSpinTop.SetPos(20);
	m_wndSpinWidth.SetRange(0,rectClient.Width() - 300);
	m_wndSpinWidth.SetPos(200);
	m_wndSpinHeight.SetRange(0,rectClient.Height() - 4);
	m_wndSpinHeight.SetPos(200);

	m_btnCheckBorder.SetCheck(TRUE);
	m_wndFillAlpha.SetRange(0,255);
	m_wndFillAlpha.SetPos(m_FillColor.nAlpha);
	m_wndBorder.SetRange(0,255);
	m_wndBorderHight.SetRange(0,255);
	m_wndBorderHight.SetPos(m_BorderHiColor.nAlpha);
	m_wndBorder.SetPos(m_BorderColor.nAlpha);
	m_wndTransAlpha.SetRange(0,255);
	m_wndTransAlpha.SetPos(m_nEllipseAlpha);
	m_wndPos.SetRange(0,180);
	m_wndPos.SetPos(m_nPos);
	m_wndTextTrans.SetRange(0,255);
	m_wndTextTrans.SetPos(m_TextColor.nAlpha);
	m_wndSliderBack.SetRange(0,255);
	m_wndSliderBack.SetPos(m_BackColor.nAlpha);
	
	m_staticTips.SetFont(_T("Tahoma"));
	m_staticTips.SetTextColor(RGB(0,0,0));
	m_staticTips.SetTextAlign(DT_CENTER|DT_EDITCONTROL|DT_WORDBREAK);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGDIPlus_DemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialog::OnPaint();
		CPaintDC dc(this); // 用于绘制的设备上下文
		PAINTSTRUCT ps = {0};
		BeginPaint(&ps);
		ReDraw(&dc);
		EndPaint(&ps);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGDIPlus_DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//--------------------------------------------------------------------
//Enum value
enum ImageDrawMode
{    
	//Fit to the play window size. How wide (height) the window is, how 
	//is the move. Keep aspect ratio.
	IMG_FIT,

	//Not support.Stretch to the play window size. Don't keep the aspect ratio.
	IMG_STRETCH,


	//When the size of video is smaller than the play window, it displayes
	//as the video size. If it's bigger , it just like the DISP_FIT mode.
	IMG_NATIVE
};

//-----------------------------------------------------------------------------------------------
//Description:
//    Caculate the draw area
//
//Parameters:
//    mode : [in] The image display mode.
//    pDstRect : [in] A pointer to a RECT value defining the portion of the display area within the graphics context that receives the output from this method. 
//    psrcRect : [in] An optional pointer to a RECT that specifies, in 0.01mm units, the portion of the image to be drawn in dstRect. 
//                To display the entire image, set this value to NULL. 
//    pDrawRect : [out] The calculated draw area.
//
//-----------------------------------------------------------------------------------------------
void CalculateDrawArea(const RECT *pDstRect, const RECT *pSrcRect,CSize imgSize, RECT *pDrawRect,ImageDrawMode mode = IMG_FIT)
{
	RECT rcDraw = {0};

	if(mode == IMG_FIT || mode == IMG_NATIVE)
	{
		LONG lDstWidth = (pDstRect->right > pDstRect->left) ? (pDstRect->right - pDstRect->left) : (pDstRect->left - pDstRect->right);
		LONG lDstHeight = (pDstRect->bottom > pDstRect->top) ? (pDstRect->bottom - pDstRect->top) : (pDstRect->top > pDstRect->bottom);
		LONG lSrcWidth = (pSrcRect == NULL) ? imgSize.cx : (pSrcRect->right - pSrcRect->left);
		LONG lSrcHeight = (pSrcRect == NULL) ? imgSize.cy : (pSrcRect->bottom - pSrcRect->top);

		LONG lDispLeft,lDispTop,lDispWidth,lDispHeight;

		if(mode == IMG_NATIVE && lDstWidth >= lSrcWidth && lDstHeight >= lSrcHeight)
		{
			lDispLeft = (lDstWidth - lSrcWidth) / 2 + pDstRect->left;
			lDispTop = (lDstHeight - lSrcHeight) / 2 + pDstRect->top;
			lDispWidth = lSrcWidth ;
			lDispHeight = lSrcHeight ;
		}
		else
		{
			if(lSrcWidth * lDstHeight > lDstWidth * lSrcHeight)
			{
				lDispWidth = lDstWidth;                
				lDispHeight = (LONG)((float)lDispWidth / (float)lSrcWidth * lSrcHeight);
				lDispLeft = pDstRect->left;
				lDispTop = (lDstHeight - lDispHeight) / 2 + pDstRect->top;        
			}
			else if(lSrcWidth * lDstHeight < lDstWidth * lSrcHeight)
			{
				lDispHeight = lDstHeight;
				lDispWidth = (LONG)((float)lDispHeight / (float)lSrcHeight * lSrcWidth);
				lDispLeft = (lDstWidth - lDispWidth) / 2 + pDstRect->left;
				lDispTop = pDstRect->top;
			}
			else
			{
				lDispWidth = lDstWidth;                
				lDispHeight = lDstHeight;
				lDispLeft = pDstRect->left;
				lDispTop = pDstRect->top;
			}
		}

		rcDraw.left = lDispLeft;
		rcDraw.top = lDispTop;
		rcDraw.right = lDispLeft + lDispWidth;
		rcDraw.bottom = lDispTop + lDispHeight;

	}
	else if(mode == IMG_STRETCH)
	{        
		rcDraw = *pDstRect;
	}

	*pDrawRect = rcDraw;

}

void CGDIPlus_DemoDlg::PaintBG(CDC *pDC)
{
	BOOL bAutoReleaseDC = FALSE;
	CBitmap bmp;
	CRect rect;
	GetClientRect(&rect);
	int nWidth = rect.Width(),nHeight = rect.Height();

	if (NULL == pDC)
	{
		pDC = GetDC();
		bAutoReleaseDC = TRUE;
	} 
	if (m_bRedrawBkDC || m_BGMemDC.m_hDC == NULL)
	{
		m_bRedrawBkDC = FALSE;
		if (NULL != m_BGMemDC.m_hDC)
		{
			m_BGMemDC.DeleteDC();
		}

		m_BGMemDC.CreateCompatibleDC(pDC);

		bmp.CreateCompatibleBitmap(pDC,nWidth,nHeight);
		m_BGMemDC.SelectObject(bmp);
		
			CBrush BackBrush(m_bgColor);
			m_BGMemDC.FillRect(rect,&BackBrush);
		
 		if (!m_imgBG.IsNull())
 		{
			CRect rectDest,rectSrc;
			rectDest = rect;
			rectDest.DeflateRect(0,0,m_nRightPaddingClient-2,0);
			rectSrc.SetRect(0,0,m_imgBG.GetWidth(),
				m_imgBG.GetHeight());

			m_imgBG.AlphaBlend(m_BGMemDC.GetSafeHdc(),rectDest,rectSrc,255);
 		}
		
		CPen pen(PS_SOLID,1,RGB(255,0,0));
		CPen *pOldPen = m_BGMemDC.SelectObject(&pen);

		m_BGMemDC.MoveTo(1,1);
		m_BGMemDC.LineTo(nWidth - m_nRightPaddingClient,1);
		m_BGMemDC.LineTo(nWidth - m_nRightPaddingClient,nHeight - 2);
		m_BGMemDC.LineTo(1,nHeight - 2);
		m_BGMemDC.LineTo(1,1);
		m_BGMemDC.SelectObject(pOldPen);
		m_BGMemDC.FillSolidRect(nWidth - m_nRightPaddingClient + 2,0,nWidth - m_nRightPaddingClient - 2,
			nHeight,GetSysColor(COLOR_3DFACE));
		m_staticTips.SetBkGnd(&m_BGMemDC);
	}

	::BitBlt(pDC->GetSafeHdc(),0,0,
		nWidth,
		nHeight,
		m_BGMemDC,0,0,SRCCOPY);

	if (bAutoReleaseDC)
	{
		::ReleaseDC(m_hWnd,pDC->GetSafeHdc());
	}
}

void CGDIPlus_DemoDlg::ReDraw(CDC *pDC)
{
	BOOL bAutoReleaseDC = FALSE;
	if (NULL == pDC)
	{
		pDC = GetDC();
		bAutoReleaseDC = TRUE;
	} 
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	CRect rect;

	GetClientRect(&rect);
	int nWidth = rect.Width(),nHeight = rect.Height();
	bmp.CreateCompatibleBitmap(pDC,nWidth,nHeight);
	memDC.SelectObject(bmp);

	PaintBG(&memDC);

	CRect rectEill(m_nLeftMargin,m_nTopMargin,m_nLeftMargin + m_nEllipseWidth,m_nTopMargin + m_nEllipseHeight);
    RedrawEllipse(&memDC,rectEill);

	::BitBlt(pDC->GetSafeHdc(),0,0,
		nWidth,
		nHeight,
		memDC,0,0,SRCCOPY);
	if (bAutoReleaseDC)
	{
		::ReleaseDC(m_hWnd,pDC->GetSafeHdc());
	}
}

void CGDIPlus_DemoDlg::RedrawEllipse(CDC *pDC,CRect rectDraw)
{
	BOOL bAutoReleaseDC = FALSE;
	if (NULL == pDC)
	{
		pDC = GetDC();
		bAutoReleaseDC = TRUE;
	} 

	CDC memDC;
	CBitmap bmp;
	BLENDFUNCTION bm;
	BYTE byteAlpha = 255;
	CRect rect = rectDraw;

	bm.BlendOp=AC_SRC_OVER;
	bm.BlendFlags=0;
	bm.SourceConstantAlpha= m_nEllipseAlpha;
	bm.AlphaFormat=0; 
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(GetFont());
	memDC.SetMapMode(MM_TEXT);

	CSize Extent;

	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	memDC.SelectObject(bmp);
 	memDC.BitBlt(0,0,rect.Width(),rect.Height(),pDC,rect.left,rect.top,SRCCOPY);
 	
	CRect rectElli = rect;
	rectElli.MoveToXY(0,0);
	
 	Gdiplus::Graphics graph(memDC);
 	Gdiplus::Color colBorder(m_BorderColor.nAlpha,GetRValue(m_BorderColor.color),GetGValue(m_BorderColor.color),GetBValue(m_BorderColor.color)/*243,106,9*/),colFill(/*80,163,240*/m_FillColor.nAlpha,GetRValue(m_FillColor.color),GetGValue(m_FillColor.color),GetBValue(m_FillColor.color)),
		colBorderHi(m_BorderHiColor.nAlpha,GetRValue(m_BorderHiColor.color),GetGValue(m_BorderHiColor.color),GetBValue(m_BorderHiColor.color)/*243,106,9*/),
		colBackFill(m_BackColor.nAlpha,GetRValue(m_BackColor.color),GetGValue(m_BackColor.color),GetBValue(m_BackColor.color));
 	int nLineWidth = 2;
	
	Gdiplus::Pen penBorder(colBorderHi,nLineWidth);
 	int nOffset = nLineWidth/2;
 	graph.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);//抗锯齿
 
 	//绘制选中部分颜色
 	Gdiplus::SolidBrush brushFill(colFill); 
	Gdiplus::SolidBrush brushBackFill(colBackFill); 
 	Gdiplus::GraphicsPath arcPath,arcBorder;
	int nPadding = 5;
	Gdiplus::RectF rectBackPath(rectElli.left+nOffset ,rectElli.top+nOffset,rectElli.Width()- 2*nOffset - 1,rectElli.Height() - 2*nOffset - 1);
	Gdiplus::RectF rectPath(rectElli.left+nOffset + nPadding,rectElli.top+nOffset + nPadding,rectElli.Width()- 2*nOffset - 1 - 2*nPadding,rectElli.Height() - 2*nOffset - 1 - 2*nPadding);
	Gdiplus::RectF rectBorderPath(rectElli.left+nOffset,rectElli.top+nOffset,rectElli.Width()- 2*nOffset - 1,rectElli.Height() - 2*nOffset - 1);
 	Gdiplus::REAL startAngle , sweepAngle ;

	arcBorder.AddArc(rectBackPath,0.0,360.0);
	graph.FillPath(&brushBackFill,&arcBorder);
	arcBorder.Reset();

 	startAngle = m_startAngle;
	sweepAngle = (90-startAngle)*2;
 	arcPath.AddArc(rectPath,startAngle,sweepAngle);
 	graph.FillPath(&brushFill,&arcPath);

	
	if (m_btnCheckBorder.GetCheck())
	{
		//绘制边框
		Gdiplus::Pen penBorder1(colBorder,nLineWidth);
		arcBorder.AddArc(rectBorderPath,0.0,360.0);
		graph.DrawPath(&penBorder1,&arcBorder);
		arcBorder.Reset();

		startAngle = -90.0 ;
		sweepAngle =  m_nPos *2;
		arcBorder.AddArc(rectBorderPath,startAngle,sweepAngle);
	    graph.DrawPath(&penBorder,&arcBorder);
	}

	Gdiplus::SolidBrush brushText(Gdiplus::Color(m_TextColor.nAlpha,GetRValue(m_TextColor.color),GetGValue(m_TextColor.color),GetBValue(m_TextColor.color)));  
	Gdiplus::Font font(_T("Tahoma"),10.0,Gdiplus::FontStyleBold);
	Gdiplus::StringFormat sf ;
	sf.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	sf.SetAlignment(Gdiplus::StringAlignmentNear);
	sf.SetFormatFlags(Gdiplus::StringFormatFlagsDirectionRightToLeft|Gdiplus::StringFormatFlagsNoWrap);//纵向输出禁止换行
	sf.SetTrimming(Gdiplus::StringTrimmingEllipsisWord);//结尾截断字符
	
	CString strText;
	strText.Format(_T("%d"),(int)(((double)m_nPos/180.0)*100));
	int nLen = strText.GetLength();
	graph.DrawString(strText,nLen,&font,Gdiplus::RectF(rectElli.left +5 ,rectElli.top ,rectElli.Width()/2 ,rectElli.Height() + 1),&sf,&brushText);

	strText = _T("\%");
	nLen = strText.GetLength();
	Gdiplus::Font font1(_T("Tahoma"),6.0);
	sf.SetAlignment(Gdiplus::StringAlignmentFar);
	graph.DrawString(strText,nLen,&font1,Gdiplus::RectF(rectElli.left + rectElli.Width()/2 + 3,rectElli.top + 2 ,rectElli.Width()/2 ,rectElli.Height() + 1),&sf,&brushText);

	AlphaBlend(pDC->m_hDC,rect.left,rect.top,rect.Width(),rect.Height(),memDC.m_hDC,0,0,rectElli.Width(),rectElli.Height(),bm); 
 
	if (bAutoReleaseDC)
	{
		::ReleaseDC(m_hWnd,pDC->GetSafeHdc());
	}
}

void CGDIPlus_DemoDlg::OnBnClickedCheckBorder()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateEllipseThemes();
}

void MakeTranPngImage( CImage & image )
{
	if(!image.IsNull() && image.GetBPP() == 32)       
	{                     
		int maxY=image.GetHeight();           
		int maxX=image.GetWidth();           
		//		byte r,g,b;
		//int avg;    
		//		WORD dwHue, dwLum, dwSat;
		for(int x=0;x<maxX;x++)           
		{                
			for(int y=0;y<maxY;y++)                
			{                     

				UCHAR *cr = (UCHAR*) image.GetPixelAddress(x,y);
				cr[0] = cr[0]*cr[3] / 255;
				cr[1] = cr[1]*cr[3] / 255;
				cr[2] = cr[2]*cr[3] / 255;     
			}  
		}    
	}
}

void CGDIPlus_DemoDlg::OnBnClickedButtonChangebgimg()
{
	// TODO: 在此添加控件通知处理程序代码

	CString strTemp;
	CString strNewFilePath;
	CString strTitle,strContent,strFilter;  
	strFilter.Format(_T("%s(*.jpg *.png *.gif *.jpeg)|*.jpg;*.png;*.gif;*.jpeg||"),_T("背景图片"),_T("Image files"));

	CFileDialog Open(TRUE,_T("*.png|*.jpg|*.gif|*.jpeg"),NULL,OFN_ENABLESIZING| OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST/*|OFN_ALLOWMULTISELECT*/,strFilter,NULL,0,FALSE); 
	if (Open.DoModal()==IDOK)
	{
		POSITION posFile=Open.GetStartPosition();
		while(posFile!=NULL)
		{
			strTemp.Format(_T("%s"),Open.GetNextPathName(posFile));
			if(PathFileExists(strTemp))
			{
				if(!m_imgBG.IsNull())
				{
					m_imgBG.Destroy();
				}
				m_bRedrawBkDC = TRUE;
				m_imgBG.Load(strTemp);
				MakeTranPngImage(m_imgBG);
				Invalidate();
			}

		} 
	}
}

void CGDIPlus_DemoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colDlg(m_bgColor);
	if (colDlg.DoModal() == IDOK)
	{
       m_bgColor = colDlg.GetColor();
	   m_bRedrawBkDC = TRUE;
	   if (!m_imgBG.IsNull())
	   {
		   m_imgBG.Destroy();
	   }
	   Invalidate();
	}
}

void CGDIPlus_DemoDlg::UpdateMemory()
{
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof (statex);

	GlobalMemoryStatusEx (&statex);
	m_nPos = (int)((double)statex.dwMemoryLoad/100.0*180.0);
	m_wndPos.SetPos(m_nPos);
	UpdateEllipse(m_nPos);
}

void CGDIPlus_DemoDlg::UpdateEllipse(int nPos)
{
	
	CString strText;
	m_startAngle = (90 - nPos)*1.0;
	strText.Format(_T("pos:%d startAngle:%.2f"),m_nPos,m_startAngle);
	m_staticTips.SetText(strText);
	UpdateEllipseThemes();
}
void CGDIPlus_DemoDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_btnCheckMemory.GetCheck())
	{
       KillTimer(TIMER_UPDATE_MEMORY);
	   SetTimer(TIMER_UPDATE_MEMORY,1000,NULL);
	}else
	{
		KillTimer(TIMER_UPDATE_MEMORY);
	}
}

void CGDIPlus_DemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    if (nIDEvent == TIMER_UPDATE_MEMORY)
    {
		UpdateMemory();
    }
	CDialog::OnTimer(nIDEvent);
}

BOOL CGDIPlus_DemoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

void CGDIPlus_DemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_bRedrawBkDC = TRUE;
	Invalidate();
}

void CGDIPlus_DemoDlg::SetPosToEllipse(int nOffset)
{
	int nTemp = m_nPos;
	nTemp += nOffset;
	if (nTemp < 0)
	{
		nTemp = 0;
	}else if (nTemp > 180)
	{
		nTemp = 180;
	}
	if (m_nPos != nTemp)
	{
		//有变化时才刷新
		m_nPos = nTemp;
	    UpdateEllipse(m_nPos);
	}
}


BOOL CGDIPlus_DemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{ 
		switch(pMsg->wParam)
		{
// 		case VK_UP:
// 		case VK_RIGHT:
// 			SetPosToEllipse(1);
// 			break;
// 		case VK_LEFT:
// 		case VK_DOWN:
// 			SetPosToEllipse(-1);
// 			break;
		case VK_HOME:
			m_nPos = 0;
			UpdateEllipse(m_nPos);
			break;
		case VK_END:
			m_nPos = 180;
			UpdateEllipse(m_nPos);
			break;
		case VK_PRIOR:
			SetPosToEllipse(10);
			break;
		case VK_NEXT:
			SetPosToEllipse(-10);
			break;
		}
	}
   
	return CDialog::PreTranslateMessage(pMsg);
}

void CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	m_FillColor.nAlpha = m_wndFillAlpha.GetPos();
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnNMCustomdrawSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider3(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	m_BorderColor.nAlpha = m_wndBorder.GetPos();
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	m_BorderHiColor.nAlpha = m_wndBorderHight.GetPos();
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnBnClickedButtonBody()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colDlg(m_bgColor);
	if (colDlg.DoModal() == IDOK)
	{
		m_FillColor.color = colDlg.GetColor();	
		UpdateEllipseThemes();
	}
}

void CGDIPlus_DemoDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colDlg(m_bgColor);
	if (colDlg.DoModal() == IDOK)
	{
		m_BorderColor.color = colDlg.GetColor();
		UpdateEllipseThemes();
	}
}

void CGDIPlus_DemoDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colDlg(m_bgColor);
	if (colDlg.DoModal() == IDOK)
	{
		m_BorderHiColor.color = colDlg.GetColor();	
		UpdateEllipseThemes();
	}
}

void CGDIPlus_DemoDlg::UpdateEllipseThemes()
{
	CRect rectClient;
	GetClientRect(rectClient);
	rectClient.right -= 300;
	//CRect rect(m_nLeftMargin,m_nTopMargin,m_nEllipseWidth,m_nEllipseHeight);
	InvalidateRect(rectClient);
}
void CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider4(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
    m_nEllipseAlpha = m_wndTransAlpha.GetPos();
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider5(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	m_nPos = m_wndPos.GetPos();
	UpdateEllipse(m_nPos);
}

void CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider6(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	m_TextColor.nAlpha = m_wndTextTrans.GetPos();
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colDlg(m_bgColor);
	if (colDlg.DoModal() == IDOK)
	{
		m_TextColor.color = colDlg.GetColor();	
		UpdateEllipseThemes();
	}
}

HBRUSH CGDIPlus_DemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if(nCtlColor==CTLCOLOR_STATIC)  //注意此处的（pWnd->），否则没效果
	{
		//pDC->SetTextColor(RGB(255,0,0));
		//pDC->SetBkColor(RGB(0,0,0));    //设置文本背景色
		pDC->SetBkMode(TRANSPARENT);      //设置背景透明
	}
	return hbr;
}

void CGDIPlus_DemoDlg::OnTRBNThumbPosChangingSlider7(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	m_BackColor.nAlpha = m_wndSliderBack.GetPos();
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnBnClickedButtonBody2()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog colDlg(m_bgColor);
	if (colDlg.DoModal() == IDOK)
	{
		m_BackColor.color = colDlg.GetColor();	
		UpdateEllipseThemes();
	}
}

void CGDIPlus_DemoDlg::OnEnChangeEditLeft()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	m_nLeftMargin = GetDlgItemInt(IDC_EDIT_LEFT);
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnEnChangeEditTop()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	m_nTopMargin = GetDlgItemInt(IDC_EDIT_TOP);
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnEnChangeEditWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	m_nEllipseWidth = GetDlgItemInt(IDC_EDIT_WIDTH);
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnEnChangeEditHeight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	m_nEllipseHeight = GetDlgItemInt(IDC_EDIT_HEIGHT);
	UpdateEllipseThemes();
}

void CGDIPlus_DemoDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	ShellExecute(NULL, _T("open"), _T("http://www.cnso.org?from=GDIPlus_Demo&v=1.0.0.1"), NULL, NULL,SW_SHOWNORMAL);
}

void CGDIPlus_DemoDlg::OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	ShellExecute(NULL, _T("open"), _T("http://www.cnso.org/aboutme?from=GDIPlus_Demo&v=1.0.0.1"), NULL, NULL,SW_SHOWNORMAL);
}
