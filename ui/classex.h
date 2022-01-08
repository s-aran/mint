#pragma once

#include "framework.h"

namespace Ui
{
  class WindowClassEx
  {
  public:
    WindowClassEx();
    WindowClassEx(const WindowClassEx& v) noexcept;
    WindowClassEx(WindowClassEx&& v) noexcept;
    ~WindowClassEx();

    WindowClassEx& operator=(const WindowClassEx& rhs);
    WindowClassEx& operator=(WindowClassEx&& rhs);

    LPWNDCLASSEX getWindowClassEx() const;

    void setSize(UINT cbSize);
    UINT getSize() const;

    void setStyle(UINT style);
    UINT getStyle() const;

    void setWindowProcedure(WNDPROC lpfnWndProc);
    WNDPROC getWindowProcedure() const;

    void setClassExtra(int cbClsExtra);
    int getClassExtra() const;

    void setWindowExtra(int cbWndExtra);
    int getWindowExtra() const;

    void setInstance(HINSTANCE hInstance);
    HANDLE getInstance() const;

    void setIcon(HICON hIcon);
    HICON getIcon() const;

    void setCursor(HCURSOR hCursor);
    HCURSOR getCursor() const;

    void setBackground(HBRUSH hbrBackground);
    HBRUSH getBackground() const;

    void setMenuName(LPCTSTR lpszMenuName);
    LPCTSTR getMenuName() const;

    void setClassName(LPCTSTR lpszClassName);
    LPCTSTR getClassName() const;

    void setSmallIcon(HICON hIconSm);
    HICON getSmallIcon() const;

  private:
    UINT m_uiSize;
    LPWNDCLASSEX m_lpwcxWindowClassEx;
    LPCTSTR m_lpszMenuName;
    LPCTSTR m_lpszClassName;
    // CrunError* m_lpError;

    void setWindowClassEx(LPWNDCLASSEX lpwcxWindowClassEx);

    LPWNDCLASSEX createWindowClassEx();
    bool destroyWindowClassEx(LPWNDCLASSEX lpwcxWindowClassEx);
  };
}