#include "pch.h"
#include "mdi_child.h"


ChildWindow::ChildWindow(LPCTSTR lpszClassName): Window(lpszClassName)
{
  // NOP
}

ChildWindow::ChildWindow(LPCTSTR lpszClassName, WindowClassEx& windowClassEx): Window(lpszClassName, windowClassEx)
{
  // NOP
}

HWND ChildWindow::create(HWND hMdiClient, WNDPROC lpfnWndProc)
{
  HINSTANCE hInstance = GetModuleHandle(0);
  return this->create(hInstance, lpfnWndProc, hMdiClient);
}

HWND ChildWindow::create(HINSTANCE hInstance, WNDPROC lpfnWndProc, HWND hMdiClient)
{
  this->windowClassEx_.setInstance(hInstance);
  this->windowClassEx_.setWindowProcedure(lpfnWndProc);
  this->registerWindowClassEx(this->windowClassEx_);

  HWND hWnd = CreateMDIWindow(
    this->m_lpszClassName,
    TEXT(""),
    0,
    this->getX(),
    this->getY(),
    this->getWidth(),
    this->getHeight(),
    hMdiClient,
    hInstance,
    0
  );
  this->m_hWnd = hWnd;

  if (!hWnd)
  {
    std::wcout << std::wstring(getErrorMessage()) << std::endl;
  }
  
  return hWnd;
}
