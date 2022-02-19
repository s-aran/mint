#pragma once

#include "window.h"

namespace Ui
{
  class ParentWindow : public Window
  {
  public:
    struct MessageCallback : public CallbackBase<Window::Callback>
    {
      virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };

  public:
    ParentWindow(LPCTSTR lpszClassName);
    ParentWindow(LPCTSTR lpszClassName, WindowClassEx& windowClassEx);

    HWND create();
    HWND create(HINSTANCE hInstance);

    HWND createClientWindow();
    HWND getClientWindowHandle() const;

  private:
    HWND hClientWindow_;

    void setClientWindowHandle(HWND hWnd);
    void registerCreateCallback();

    virtual HWND createWindow(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPVOID lpData);
  };
}