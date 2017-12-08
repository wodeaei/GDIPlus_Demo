#pragma once


// CRichStatic

class CRichStatic : public CStatic
{
	DECLARE_DYNAMIC(CRichStatic)

public:
	CRichStatic();
	virtual ~CRichStatic();

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnSetText(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	void PaintBG(CDC *pDC);

private:
	COLORREF m_clrText;          // 文字前景色
	COLORREF m_clrBackground;    // 文字背景色
	CBitmap m_Bmp;               // 保存背景用的位图对象
	BOOL m_selfCreated;
	 CFont m_hFont;
	UINT  m_xAlignment;
	CDC             m_BGMemDC;
public:
	void SetBkGnd(CDC* pDC,BOOL bRedraw = TRUE);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// 设置背景色（若clr为CLR_NONE，则背景透明）
	void SetBackgroundColor(COLORREF clr){m_clrBackground = clr;}
	// 设置文字前景色
	void SetTextColor(COLORREF clr){m_clrText = clr;}
	// 设置文字字体
	BOOL SetFont(TCHAR* lpFaceName = _T("Arial"), int nSize = 14, int nWeight = FW_NORMAL, BOOL bItalic = FALSE);
	BOOL SetFont(const LPLOGFONT lpFont);
	void SetTextAlign(UINT ulTextAlign = DT_CENTER|DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS){m_xAlignment = ulTextAlign;}
	void SetText(LPCTSTR lpszText,BOOL bRedraw = TRUE);

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};

