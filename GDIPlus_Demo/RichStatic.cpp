// RichStatic.cpp : 实现文件
//


#include "stdafx.h"
#include "RichStatic.h"




// CRichStatic


IMPLEMENT_DYNAMIC(CRichStatic, CStatic)


CRichStatic::CRichStatic():
m_clrText(0), m_clrBackground(CLR_NONE), m_selfCreated(FALSE)
{
	m_hFont.CreateFont(14,0,0,0,FW_NORMAL,0,0,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,DEFAULT_PITCH | FF_DONTCARE,_T("Arial"));
   SetTextAlign();
}


CRichStatic::~CRichStatic()
{
	m_hFont.DeleteObject();
}




BEGIN_MESSAGE_MAP(CRichStatic, CStatic)
	ON_MESSAGE(WM_SETTEXT,OnSetText)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()






// CRichStatic 消息处理程序

void CRichStatic::PaintBG(CDC *pDC)
{
	CRect rect,windowrect;
	GetClientRect(rect);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_BGMemDC, 0, 0, SRCCOPY);
}

void CRichStatic::SetBkGnd(CDC* pDC,BOOL bRedraw/* = TRUE*/)
{
	CBitmap btm,*pOldBtm;
	CRect rect,rectS;

	GetClientRect(&rect);
	GetWindowRect(&rectS);
	GetParent()->ScreenToClient(&rectS);

	if (NULL != m_BGMemDC.m_hDC)
	{
		m_BGMemDC.DeleteDC();
	}

	m_BGMemDC.CreateCompatibleDC(pDC);
	btm.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	pOldBtm = m_BGMemDC.SelectObject(&btm);
	m_BGMemDC.BitBlt(0,0,rect.Width(),rect.Height(),pDC,rectS.left,rectS.top,SRCCOPY);

	btm.DeleteObject();
	if (bRedraw)
	{
		Invalidate();
	}
}

HBRUSH CRichStatic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// 	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);
	// 
	// 	// TODO:  在此更改 DC 的任何属性
	// 
	// 	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	// 	return hbr;
	if (m_BGMemDC.m_hDC == NULL)
	{
		CBitmap bmp;

		CRect rect1,rect;

		GetClientRect(&rect);
		CClientDC clDC(GetParent());
		GetWindowRect(rect1);
		GetParent()->ScreenToClient(rect1);
		m_BGMemDC.CreateCompatibleDC(&clDC);
		//m_BGMemDC.SetBkMode(TRANSPARENT);
		bmp.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_BGMemDC.SelectObject(&bmp);
		m_BGMemDC.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);

	}
	return NULL;
}

void CRichStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct -> hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	memDC.SelectObject(bmp);

	PaintBG(&memDC);
	if (m_clrBackground != CLR_NONE)    // 若背景色不为CLR_NONE（CLR_NONE表示无背景色），则绘制背景
	{
		CRect rect;
		CBrush brush(m_clrBackground);
		GetClientRect(rect);
		memDC.FillRect(rect,&brush);

		//RECT rect;
		//GetWindowRect(&rect);
		//CBrush brush;
		//brush.CreateSolidBrush(m_clrBackground);
		//::SelectObject(memDC.GetSafeHdc(), brush.m_hObject);    // 设置画刷颜色
		//::SelectObject(memDC.GetSafeHdc(), GetStockObject(NULL_PEN));    // 设置笔为空笔（不绘制边界）
		//Rectangle(memDC.GetSafeHdc(), 0, 0,rect.right - rect.left, rect.bottom - rect.top);
	}


	CString strCaption;    // 标题文字
	GetWindowText(strCaption);
	if (m_hFont.m_hObject != NULL)
	{
		::SelectObject(memDC.GetSafeHdc(), m_hFont.m_hObject);
	}


// 	CRect rect;
// 	GetClientRect(rect);
	// 设置dc字串颜色
	int iOldMode = pDC->GetBkMode();
	memDC.SetBkMode( TRANSPARENT);
	// 设置dc字串颜色
	::SetTextColor(memDC.GetSafeHdc(), m_clrText);
	DrawText(memDC.GetSafeHdc(), strCaption, strCaption.GetLength(),&rect,m_xAlignment);
	memDC.SetBkMode( iOldMode);
	
	::BitBlt(lpDrawItemStruct -> hDC,0,0,
		rect.Width(),rect.Height(),
		memDC,0,0,SRCCOPY);
}


void CRichStatic::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();
	ModifyStyle(0, SS_OWNERDRAW);
}


BOOL CRichStatic::SetFont(TCHAR* lpFaceName /* = "Arial" */, int nSize /* = 14 */, int nWeight /* = FW_NORMAL */, BOOL bItalic /* = FALSE */)
{
	if (m_hFont.m_hObject)
	{
		m_hFont.DeleteObject();
	}
	

	BOOL ret = m_hFont.CreateFont(nSize,0,0,0,nWeight,(BYTE)bItalic,0,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,DEFAULT_PITCH | FF_DONTCARE,lpFaceName);

	if (ret)
	{
		if (::IsWindow(m_hWnd))
		{
			CWnd::SetFont(&m_hFont);
		}
	}
	return ret;
}

BOOL CRichStatic::SetFont( LPLOGFONT lpFont )
{
	if (m_hFont.m_hObject)
	{
		m_hFont.DeleteObject();
	}
	BOOL ret = m_hFont.CreateFontIndirect(lpFont);

	if (ret)
	{
		if (::IsWindow(m_hWnd))
		{
			CWnd::SetFont(&m_hFont);
		}
	}

	return ret;
}

BOOL CRichStatic::OnEraseBkgnd(CDC* pDC)
{
	// 当背景色为透明时，需要保存与拷贝显示主框的显示区域
// 	if (m_clrBackground == CLR_NONE)
// 	{
// 		if (m_Bmp.GetSafeHandle() == NULL)
// 		{
// 			CRect Rect;
// 			GetWindowRect(&Rect);
// 			CWnd *pParent = GetParent();
// 			ASSERT(pParent);
// 			pParent->ScreenToClient(&Rect);  // 将坐标转换为与主对话框相对应
// 
// 			// 拷贝对应区域主框显示的内容
// 			CDC *pDC = pParent->GetDC();
// 			CDC MemDC;
// 			MemDC.CreateCompatibleDC(pDC);
// 			m_Bmp.CreateCompatibleBitmap(pDC,Rect.Width(),Rect.Height());
// 			CBitmap *pOldBmp = MemDC.SelectObject(&m_Bmp);
// 			MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),pDC,Rect.left,Rect.top,SRCCOPY);
// 			MemDC.SelectObject(pOldBmp);
// 			MemDC.DeleteDC();    // 删除内存DC，否则内存泄漏
// 			pParent->ReleaseDC(pDC);
// 		}
// 		else // 将主框显示的内容拷贝回去
// 		{
// 			CRect Rect;
// 			GetClientRect(Rect);
// 			CDC MemDC;
// 			MemDC.CreateCompatibleDC(pDC);
// 			CBitmap *pOldBmp = MemDC.SelectObject(&m_Bmp);
// 			pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
// 			MemDC.SelectObject(pOldBmp);
// 			MemDC.DeleteDC();    // 删除内存DC，否则内存泄漏
// 		}
// 	}


	return TRUE;
}


LRESULT CRichStatic::OnSetText(WPARAM wParam,LPARAM lParam)
{
	LRESULT Result = Default();
	Invalidate();
	UpdateWindow();
	return Result;
}

void CRichStatic::SetText(LPCTSTR lpszText,BOOL bRedraw /*= TRUE*/)
{
	if (lpszText == NULL 
		|| _tcslen(lpszText) == 0)
	{
		return ;
	}
	SetWindowText(lpszText);
	if (bRedraw)
	{
		Invalidate();
	}
}