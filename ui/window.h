#pragma once

#include "framework.h"

class Window
{
public:
  Window(LPCTSTR lpszClassName);
  Window(LPCTSTR lpszClassName, WindowClassEx& windowClassEx);
  virtual ~Window();

  HWND create(WNDPROC lpfncWndProc);
  HWND create(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPVOID lpData);

  WPARAM MainLoop();

  HWND getHandle() const;

  BOOL setWidth(int nWidth);
  BOOL setHeight(int nHeight);
  BOOL setSize(int nWidth, int nHeight);

  int getHeight() const;
  int getWidth() const;

  BOOL setX(int nX);
  BOOL setY(int nY);
  BOOL setPosition(int nX, int nY);

  int getX() const;
  int getY() const;

  BOOL setText(LPCTSTR lpszText);
  LPCTSTR getText() const;

  void setStyle(DWORD dwStyle);
  DWORD getStyle() const;

  void setExStyle(DWORD dwExStyle);
  DWORD getExStyle() const;

  void show();
  void close();

  static HINSTANCE getInstance(HWND hWnd);

protected:
  typedef std::vector<HWND> DialogWindowHandlerVector;

  static DialogWindowHandlerVector g_vectorDialogWindows;

  WindowClassEx createWindowClassEx();
  void registerWindowClassEx(WindowClassEx& classEx);
  // void setHandle(HWND hWnd);
  LPCREATESTRUCT createCreateStruct(LPVOID lpCreateParam);
  void deleteCreateStruct();

  BOOL setClientSize(int nClientWidth, int nClientHeight);

  // CrunError* GetError();

  LPCTSTR m_lpszClassName;

  WindowClassEx windowClassEx_;
  // CrunError* m_lpError;

  LPCREATESTRUCT m_lpCreateStruct;

  HWND m_hWnd;

  LPTSTR m_lpszText;
  DWORD m_dwStyle;
  DWORD m_dwExStyle;
  int m_nX;
  int m_nY;
  int m_nWidth;
  int m_nHeight;


private:
};
