#include "stdafx.h"
#include "resource.h"

#include "BillResultsDlg.h"
#include "VerificationDlg.h"

LRESULT CBillResultsDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	HICON hDlgIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_YTOALL), 
		IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	SendDlgItemMessage(IDC_BILLPIC,STM_SETICON,(WPARAM)hDlgIcon,0);
	DoDataExchange(false);
	list.InsertColumn(0,"时间",LVCFMT_LEFT,108,0);
	list.InsertColumn(1,"运单详情",LVCFMT_LEFT,300,1);
	for(int i=1;i<=BillContainer->GetBillCount();i++) Combo.AddString(BillContainer->GetBillNumber(i));
	Combo.SetCurSel(0);
	for(int i=1;i<=(BillContainer->GetItemCount(1));i++)
	{
		list.InsertItem(i-1,BillContainer->GetBill(1,i,1),NULL);
		list.SetItemText(i-1,1,BillContainer->GetBill(1,i,2));
	}
	return TRUE;
}
LRESULT CBillResultsDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}
LRESULT CBillResultsDlg::OnComboChange(UINT uCode, int nCtrlID, HWND hwndCtrl)
{
	int currentBranch=Combo.GetCurSel()+1;
	list.DeleteAllItems();
	for(int i=1;i<=(BillContainer->GetItemCount(currentBranch));i++)
	{
		list.InsertItem(i-1,BillContainer->GetBill(currentBranch,i,1),NULL);
		list.SetItemText(i-1,1,BillContainer->GetBill(currentBranch,i,2));
	}
	return 0;
}
LRESULT CBillResultsDlg::OnCopy(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int currentBranch=Combo.GetCurSel()+1;
	CString FileContent;
	FileContent=FileContent+"圆通运单号:"+BillContainer->GetBillNumber(currentBranch)+"\r\n\r\n";
	for(int i=1;i<=BillContainer->GetItemCount(currentBranch);i++)
	{
		FileContent=FileContent+BillContainer->GetBill(currentBranch,i,1)+"\t"+BillContainer->GetBill(currentBranch,i,2)+"\r\n";
	}
	if(OpenClipboard())//写入前，如非延时写入，都要先调用
	{
		char *pBuf;
		EmptyClipboard();
		HANDLE hClip=GlobalAlloc(GMEM_MOVEABLE,FileContent.GetLength()+1);//分配内存空间
		pBuf=(char*)GlobalLock(hClip);
		strcpy(pBuf,FileContent);
		GlobalUnlock(hClip);
		SetClipboardData(CF_TEXT,hClip);
		CloseClipboard();
	}
	return 0;
}
LRESULT CBillResultsDlg::OnSaveText(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CFileDialog m_wndSaveAll(false,NULL,"运单查询结果.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"文本文档(*.txt)\0*.txt\0All Files(*.*)\0*.*");
	if( IDOK==m_wndSaveAll.DoModal())
	{
			HANDLE hFile=::CreateFile(m_wndSaveAll.m_ofn.lpstrFile,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			DWORD dwWrites;
			CString FileContent;
			for(int i=1;i<=BillContainer->GetBillCount();i++)
			{
				FileContent=FileContent+"\r\n圆通运单号:"+BillContainer->GetBillNumber(i)+"\r\n\r\n";
				for(int j=1;j<=BillContainer->GetItemCount(i);j++)
				{
					FileContent=FileContent+BillContainer->GetBill(i,j,1)+"\t"+BillContainer->GetBill(i,j,2)+"\r\n";
				}
				FileContent=FileContent+"\r\n";
			}
			::WriteFile(hFile,FileContent,FileContent.GetLength(),&dwWrites,NULL);
			CloseHandle(hFile);
	}
	return 0;
}
LRESULT CBillResultsDlg::OnSavePic(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SetWindowPos(HWND_TOP,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE|SWP_SHOWWINDOW);
	CRect rect;
	GetClientRect(&rect);
	HBITMAP hMap =  CopyScreenToBitmap(rect);

	CFileDialog m_wndSavePic(false,NULL,"查询结果.bmp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"位图文件(*.bmp)\0*.bmp\0\0");
	if( IDOK==m_wndSavePic.DoModal()) SaveBitmapToFile(hMap,m_wndSavePic.m_ofn.lpstrFile);
	return 0;
}
HBITMAP CBillResultsDlg::CopyScreenToBitmap(LPRECT lpRect) //lpRect 代表选定区域
{
	/* HDC hScrDC, hMemDC;
	// 屏幕和内存设备描述表
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表*/
	CClientDC hScrDC(m_hWnd);
	HDC hMemDC;
	HBITMAP hBitmap,hOldBitmap;
	// 位图句柄
	int nX,nY,nX2,nY2;
	// 选定区域坐标
	int nWidth, nHeight;
	// 位图宽度和高度
	int xScrn,yScrn;
	// 屏幕分辨率
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
	return NULL;
	//为屏幕创建设备描述表

	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// 获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的
	if (nX < 0)
	nX = 0;
	if (nY < 0)
	nY = 0;
	if (nX2 > xScrn)
	nX2 = xScrn;
	if (nY2 > yScrn)
	nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth-128,nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC,0,0, nWidth-128,nHeight,hScrDC, nX, nY, SRCCOPY);
	//得到屏幕位图的句柄
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// 返回位图句柄
	return hBitmap;
}
int CBillResultsDlg::SaveBitmapToFile(HBITMAP hBitmap, LPSTR lpFileName) //hBitmap 为刚才的屏幕位图句柄
{      //lpFileName 为位图文件名
 HDC     hDC;         
    //设备描述表
 int     iBits;      
 //当前显示分辨率下每个像素所占字节数
 WORD    wBitCount;   
    //位图中每个像素所占字节数
 //定义调色板大小， 位图中像素字节大小 ，  位图文件大小 ， 写入文件字节数
 DWORD           dwPaletteSize=0,dwBmBitsSize,dwDIBSize, dwWritten;
 BITMAP          Bitmap;        
 //位图属性结构
 BITMAPFILEHEADER   bmfHdr;        
 //位图文件头结构
 BITMAPINFOHEADER   bi;            
 //位图信息头结构 
 LPBITMAPINFOHEADER lpbi;          
 //指向位图信息头结构
    HANDLE          fh, hDib, hPal;
 HPALETTE     hOldPal=NULL;
 //定义文件，分配内存句柄，调色板句柄
 
 //计算位图文件每个像素所占字节数
 hDC = CreateDC("DISPLAY",NULL,NULL,NULL);
 iBits = GetDeviceCaps(hDC, BITSPIXEL) * 
  GetDeviceCaps(hDC, PLANES);
 DeleteDC(hDC);
 if (iBits <= 1)
  wBitCount = 1;
 else if (iBits <= 4)
  wBitCount = 4;
 else if (iBits <= 8)
  wBitCount = 8;
 else if (iBits <= 24)
  wBitCount = 24;
else
  wBitCount = 32;
 //计算调色板大小
 if (wBitCount <= 8)
  dwPaletteSize=(1<<wBitCount)*sizeof(RGBQUAD);
 
 //设置位图信息头结构
 GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
 bi.biSize            = sizeof(BITMAPINFOHEADER);
 bi.biWidth           = Bitmap.bmWidth;
 bi.biHeight          = Bitmap.bmHeight;
 bi.biPlanes          = 1;
 bi.biBitCount         = wBitCount;
 bi.biCompression      = BI_RGB;
 bi.biSizeImage        = 0;
 bi.biXPelsPerMeter     = 0;
 bi.biYPelsPerMeter     = 0;
 bi.biClrUsed         = 0;
 bi.biClrImportant      = 0;
 
 dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight;
 //为位图内容分配内存

/*xxxxxxxx计算位图大小分解一下(解释一下上面的语句)xxxxxxxxxxxxxxxxxxxx 
//每个扫描行所占的字节数应该为4的整数倍，具体算法为:
 int biWidth = (Bitmap.bmWidth*wBitCount) / 32;
 if((Bitmap.bmWidth*wBitCount) % 32)
  biWidth++; //不是整数倍的加1
 biWidth *= 4;//到这里，计算得到的为每个扫描行的字节数。
 dwBmBitsSize = biWidth * Bitmap.bmHeight;//得到大小
xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/


 hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
 lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
 *lpbi = bi;
 // 处理调色板   
 hPal = GetStockObject(DEFAULT_PALETTE);
 if (hPal)
 {
  hDC = ::GetDC(NULL);
  hOldPal=SelectPalette(hDC,(HPALETTE)hPal,FALSE);
  RealizePalette(hDC);
 }
 // 获取该调色板下新的像素值
 GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
 //恢复调色板   
 if (hOldPal)
 {
  SelectPalette(hDC, hOldPal, TRUE);
  RealizePalette(hDC);
  ::ReleaseDC(NULL, hDC);
 }
 //创建位图文件    
 fh=CreateFile(lpFileName, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
 if (fh==INVALID_HANDLE_VALUE)
  return FALSE;
 // 设置位图文件头
 bmfHdr.bfType = 0x4D42;  // "BM"
 dwDIBSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize;  
 bmfHdr.bfSize = dwDIBSize;
 bmfHdr.bfReserved1 = 0;
 bmfHdr.bfReserved2 = 0;
 bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
 // 写入位图文件头
 WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
 // 写入位图文件其余内容
  WriteFile(fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)+dwPaletteSize+dwBmBitsSize , &dwWritten, NULL); 
 //清除   
 GlobalUnlock(hDib);
 GlobalFree(hDib);
 CloseHandle(fh);
 return TRUE;
}