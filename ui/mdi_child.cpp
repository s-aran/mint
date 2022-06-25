#include "pch.h"
#include "mdi_child.h"


namespace Ui
{
  ChildWindow::ChildWindow(LPCTSTR lpszClassName) : Window(lpszClassName)
  {
  }

  ChildWindow::ChildWindow(LPCTSTR lpszClassName, WindowClassEx& windowClassEx) : Window(lpszClassName, windowClassEx)
  {
    // NOP
  }

  HWND ChildWindow::create(HWND hMdiClient)
  {
    return this->create(hMdiClient, this->messageCallback_.WindowProcedure);
  }

  HWND ChildWindow::create(HWND hMdiClient, WNDPROC lpfnWndProc)
  {
    HINSTANCE hInstance = GetModuleHandle(0);
    return this->create(hInstance, lpfnWndProc, hMdiClient);
  }

  HWND ChildWindow::create(HINSTANCE hInstance, WNDPROC lpfnWndProc, HWND hMdiClient)
  {
    this->hMdiClient = hMdiClient;
      
    HWND hWnd = this->createWindow(hInstance, lpfnWndProc, nullptr);

    this->postCreateWindow(hWnd);

    return hWnd;
  }
  
  HWND ChildWindow::createWindow(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPVOID lpData)
  {
    this->windowClassEx_.setInstance(hInstance);
    this->windowClassEx_.setWindowProcedure(lpfnWndProc);
    this->registerWindowClassEx(this->windowClassEx_);

    HWND hWnd = CreateMDIWindow(
      this->m_lpszClassName,
      TEXT("Piyo"),
      0,
      this->getX(),
      this->getY(),
      this->getWidth(),
      this->getHeight(),
      hMdiClient,
      hInstance,
      0
    );

    if (!hWnd)
    {
      Window::getLogger().warn("[%s] %s: %s\n", "ChildWindow", "CreateMDIWindow()", Utils::Convert::lpctstrToString(Utils::Windows::getErrorMessage()).c_str());
    }

    return hWnd;
  }

  LRESULT CALLBACK ChildWindow::MessageCallback::Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    const auto itr = this->getMap().find(uMsg);

    if (itr != this->getMap().cend())
    {
      itr->second(hWnd, uMsg, wParam, lParam);
      return 0;
    }

    return DefMDIChildProc(hWnd, uMsg, wParam, lParam);
  }
}
