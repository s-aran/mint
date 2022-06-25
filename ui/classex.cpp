#include "pch.h"
#include "classex.h"


namespace Ui
{
  WindowClassEx::WindowClassEx()
  {
    this->setSize(sizeof(WNDCLASSEX));

    // this->m_lpError = new CrunError();
    this->m_lpwcxWindowClassEx = this->createWindowClassEx();

    // default values
    this->setStyle(CS_HREDRAW | CS_VREDRAW);
    this->setWindowProcedure(NULL);
    this->setClassExtra(0);
    this->setWindowExtra(0);
    this->setInstance(NULL);
    this->setIcon(LoadIcon(NULL, IDI_APPLICATION));
    this->setCursor(LoadCursor(NULL, IDC_ARROW));
    this->setBackground((HBRUSH)GetStockObject(WHITE_BRUSH));
    this->setMenuName(NULL);
    this->setClassName(NULL);
    this->setSmallIcon(LoadIcon(NULL, IDI_APPLICATION));
  }

  WindowClassEx::WindowClassEx(const WindowClassEx& v) noexcept
  {
    this->m_lpwcxWindowClassEx = (LPWNDCLASSEX)malloc(sizeof(*v.getWindowClassEx()));
    memcpy(this->m_lpwcxWindowClassEx, v.getWindowClassEx(), sizeof(*v.getWindowClassEx()));
  }

  WindowClassEx::WindowClassEx(WindowClassEx&& v) noexcept
  {
    this->m_lpwcxWindowClassEx = (LPWNDCLASSEX)malloc(sizeof(*v.getWindowClassEx()));
    memcpy(this->m_lpwcxWindowClassEx, v.getWindowClassEx(), sizeof(*v.getWindowClassEx()));
    v.m_lpwcxWindowClassEx = NULL;
  }

  WindowClassEx::~WindowClassEx()
  {
    // delete this->m_lpError;
    this->destroyWindowClassEx(this->m_lpwcxWindowClassEx);
  }


  WindowClassEx& WindowClassEx::operator=(const WindowClassEx& rhs)
  {
    this->destroyWindowClassEx(this->m_lpwcxWindowClassEx);
    this->m_lpwcxWindowClassEx = (LPWNDCLASSEX)malloc(sizeof(*rhs.getWindowClassEx()));
    memcpy(this->m_lpwcxWindowClassEx, rhs.getWindowClassEx(), sizeof(*rhs.getWindowClassEx()));
    return *this;
  }

  WindowClassEx& WindowClassEx::operator=(WindowClassEx&& rhs) noexcept
  {
    this->destroyWindowClassEx(this->m_lpwcxWindowClassEx);
    this->m_lpwcxWindowClassEx = (LPWNDCLASSEX)malloc(sizeof(*rhs.getWindowClassEx()));
    memcpy(this->m_lpwcxWindowClassEx, rhs.getWindowClassEx(), sizeof(*rhs.getWindowClassEx()));
    rhs.m_lpwcxWindowClassEx = NULL;
    return *this;
  }

  void WindowClassEx::setWindowClassEx(LPWNDCLASSEX lpwcxWindowClassEx)
  {
    this->m_lpwcxWindowClassEx = lpwcxWindowClassEx;
  }

  LPWNDCLASSEX WindowClassEx::getWindowClassEx() const
  {
    return this->m_lpwcxWindowClassEx;
  }

  void WindowClassEx::setSize(UINT cbSize)
  {
    this->m_uiSize = cbSize;
  }

  UINT WindowClassEx::getSize() const
  {
    return this->m_uiSize;
  }

  void WindowClassEx::setStyle(UINT style)
  {
    this->m_lpwcxWindowClassEx->style = style;
  }

  UINT WindowClassEx::getStyle() const
  {
    return this->m_lpwcxWindowClassEx->style;
  }

  void WindowClassEx::setWindowProcedure(WNDPROC lpfnWndProc)
  {
    this->m_lpwcxWindowClassEx->lpfnWndProc = lpfnWndProc;
  }

  WNDPROC WindowClassEx::getWindowProcedure() const
  {
    return this->m_lpwcxWindowClassEx->lpfnWndProc;
  }

  void WindowClassEx::setClassExtra(int cbClsExtra)
  {
    this->m_lpwcxWindowClassEx->cbClsExtra = cbClsExtra;
  }

  int WindowClassEx::getClassExtra() const
  {
    return this->m_lpwcxWindowClassEx->cbClsExtra;
  }

  void WindowClassEx::setWindowExtra(int cbWndExtra)
  {
    this->m_lpwcxWindowClassEx->cbWndExtra = cbWndExtra;
  }

  int WindowClassEx::getWindowExtra() const
  {
    return this->m_lpwcxWindowClassEx->cbWndExtra;
  }

  void WindowClassEx::setInstance(HINSTANCE hInstance)
  {
    HINSTANCE hInst = hInstance;
    if (hInstance == NULL)
    {
      // g_lpDebug->Warn("hInstance is NULL. Setting hInstance automatic.");
      hInst = GetModuleHandle(0);
      // this->m_lpError->SetWindowsError();
      // if (GetLastError() != ERROR_SUCCESS)
      {
        // g_lpDebug->Error(this->m_lpError->GetWindowsErrorMessage());
      }
    }
    this->m_lpwcxWindowClassEx->hInstance = hInst;
  }

  HANDLE WindowClassEx::getInstance() const
  {
    return this->m_lpwcxWindowClassEx->hInstance;
  }

  void WindowClassEx::setIcon(HICON hIcon)
  {
    this->m_lpwcxWindowClassEx->hIcon = hIcon;
  }

  HICON WindowClassEx::getIcon() const
  {
    return this->m_lpwcxWindowClassEx->hIcon;
  }

  void WindowClassEx::setCursor(HCURSOR hCursor)
  {
    this->m_lpwcxWindowClassEx->hCursor = hCursor;
  }

  HCURSOR WindowClassEx::getCursor() const
  {
    return this->m_lpwcxWindowClassEx->hCursor;
  }

  void WindowClassEx::setBackground(HBRUSH hbrBackground)
  {
    this->m_lpwcxWindowClassEx->hbrBackground = hbrBackground;
  }

  HBRUSH WindowClassEx::getBackground() const
  {
    return this->m_lpwcxWindowClassEx->hbrBackground;
  }

  void WindowClassEx::setMenuName(LPCTSTR lpszMenuName)
  {
    this->m_lpwcxWindowClassEx->lpszMenuName = lpszMenuName;
  }

  LPCTSTR WindowClassEx::getMenuName() const
  {
    return this->m_lpwcxWindowClassEx->lpszMenuName;
  }

  void WindowClassEx::setClassName(LPCTSTR lpszClassName)
  {
    this->m_lpwcxWindowClassEx->lpszClassName = lpszClassName;
  }

  LPCTSTR WindowClassEx::getClassName() const
  {
    return this->m_lpwcxWindowClassEx->lpszClassName;
  }

  void WindowClassEx::setSmallIcon(HICON hIconSm)
  {
    this->m_lpwcxWindowClassEx->hIconSm = hIconSm;
  }

  HICON WindowClassEx::getSmallIcon() const
  {
    return this->m_lpwcxWindowClassEx->hIconSm;
  }

  LPWNDCLASSEX WindowClassEx::createWindowClassEx()
  {
    LPWNDCLASSEX lpWndClassEx = NULL;

    lpWndClassEx = (LPWNDCLASSEX)malloc(this->getSize());
    lpWndClassEx->cbSize = this->getSize();

    return lpWndClassEx;
  }

  bool WindowClassEx::destroyWindowClassEx(LPWNDCLASSEX lpwcxWindowClassEx)
  {
    if (lpwcxWindowClassEx)
    {
      free(lpwcxWindowClassEx);
    }

    return true;
  }
}