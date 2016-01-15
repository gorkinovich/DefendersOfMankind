// ===========================================================================
// The interface of the CSplash class
// ===========================================================================

#ifndef __APPLICATION_SPLASH_H__
#define __APPLICATION_SPLASH_H__

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

/**
 * Use it for displaying splash screen for applications
 * Works only on Win2000 , WinXP and later versions of Windows
 */
class CSplash {
public:
	/**
	 * Default constructor
	 */
	CSplash();
    
	/**
	 * Constructor
	 * @param lpszFileName Path of the Bitmap that will be show on the splash screen
	 * @param colTrans The color on the bitmap that will be made transparent
	 */
	CSplash(LPCTSTR lpszFileName, COLORREF colTrans);

	/**
	 * Desctructor
	 */
	virtual ~CSplash();

	/**
	 * Launches the non-modal splash screen
	 */
	void ShowSplash();

	/**
	 * Launched the splash screen as a modal window. Not completely implemented.
	 */
	int DoLoop();

	/**
	 * Closes the splash screen started with ShowSplash
	 */
	int CloseSplash();

	/**
	 * Call this with the path of the bitmap. Not required to be used
	 * when the construcutor with the image path has been used.
	 * @param lpszFileName The file path to a bitmap
	 * @return 1 if succesfull
	 */
	DWORD SetBitmap(LPCTSTR lpszFileName);
	
	/**
	 * Call this with the path of the bitmap. Not required to be used
	 * when the construcutor with the image path has been used.
	 * @param hBitmap The handle to an already loaded bitmap
	 * @return 1 if succesfull
	 */
	DWORD SetBitmap(HBITMAP hBitmap);

	/**
	 * This is used to make one of the color transparent
	 * @param col The colors RGB value. Not required if the color is specified 
	 *            using the constructor
	 * @return 1 if succesfull
	 */
	bool SetTransparentColor(COLORREF col);

	/**
	 * The window event handler
	 */
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	/**
	 * The window handle
	 */
	HWND m_hwnd;

private:
	void Init();
	void OnPaint(HWND hwnd);
	bool MakeTransparent();
	void FreeResources();

	HWND RegAndCreateWindow();
	COLORREF m_colTrans;
	DWORD m_dwWidth;
	DWORD m_dwHeight;
	HBITMAP m_hBitmap;
	LPCTSTR m_lpszClassName;
};

#endif
