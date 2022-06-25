#pragma once

#include "window.h"

namespace Ui
{
  class ChildWindow : public Window
  {
  public:
    using Callback = std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>;
    struct MessageCallback : public CallbackBase<Callback>
    {
      virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };
  public:
    ChildWindow(LPCTSTR lpszClassName);
    ChildWindow(LPCTSTR lpszClassName, WindowClassEx& windowClassEx);

    HWND create(HWND hMdiClient);
    HWND create(HWND hMdiClient, WNDPROC lpfnWndProc);
    HWND create(HINSTANCE hInstance, WNDPROC lpfnWndProc, HWND hMdiClient);

  private:
    HWND hMdiClient;

    HWND createWindow(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPVOID lpData);
  };
}
