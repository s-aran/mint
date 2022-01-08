#pragma once

#include "window.h"

namespace Ui
{
  class ChildWindow : public Window
  {
  public:
    ChildWindow(LPCTSTR lpszClassName);
    ChildWindow(LPCTSTR lpszClassName, WindowClassEx& windowClassEx);

    HWND create(HWND hMdiClient, WNDPROC lpfnWndProc);
    HWND create(HINSTANCE hInstance, WNDPROC lpfnWndProc, HWND hMdiClient);
  };
}
