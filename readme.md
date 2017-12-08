## GDIPlus_Demo

该演示程序演示了球形进度条效果

## 效果截图
![image](http://www.cnso.org/wp-content/uploads/2017/12/GDIPlus_Demo-1.png)
![image](http://www.cnso.org/wp-content/uploads/2017/12/GDIPlus_Demo1-1.png)

## 支持以下效果设置
- 设置球体背景填充色色、填充色透明度
- 设置球体前景填充色、前景色透明度
- 设置球体边框颜色、边框颜色透明度
- 设置球体边框进度颜色、进度颜色透明度
- 设置球体字体颜色、字体颜色透明度
- 设置球体整体透明度
- 设置球体宽度、高度，可设置成椭圆或者圆形
- 可选择是否显示边框

## 进度信息查看效果
两种调节方式查看进度效果：
- 手动调节进度查看效果
- 通过获取内存占用显示自动更新进度信息

## 关于背景填充
- 可以设置图片背景
- 可以设置纯色背景

## 关于球体形状
可以通过设置长度、宽度改变球体形状，可以是圆形，也可以是椭圆形，并可在左侧预览区域实时查看效果

## 核心代码

```
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
```
