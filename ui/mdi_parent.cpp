#include "pch.h"
#include "mdi_parent.h"


namespace Ui
{
  ParentWindow::ParentWindow(LPCTSTR lpszClassName) : Window(lpszClassName), hClientWindow_(NULL)
  {
    this->registerCreateCallback();
  }

  ParentWindow::ParentWindow(LPCTSTR lpszClassName, WindowClassEx& windowClassEx) : Window(lpszClassName, windowClassEx), hClientWindow_(NULL)
  {
    this->registerCreateCallback();
  }

  HWND ParentWindow::create()
  {
    HINSTANCE hInstance = GetModuleHandle(0);
    return this->create(hInstance);
  }

  HWND ParentWindow::create(HINSTANCE hInstance)
  {
    HWND hWnd = this->createWindow(hInstance, nullptr, nullptr);
    if (!hWnd)
    {
      Window::getLogger().warn("[%s] %s: %s\n", "ParentWindow", "CreateWindowEx()", Utils::Convert::lpctstrToString(Utils::Windows::getErrorMessage()).c_str());
      return NULL;
    }
    Window::getLogger().info("[%s] %s: %s\n", "ParentWindow", "CreateWindowEx()", "Succeeded.");

    this->postCreateWindow(hWnd);

    return hWnd;
  }

  HWND ParentWindow::getClientWindowHandle() const
  {
    return this->hClientWindow_;
  }

  void ParentWindow::setClientWindowHandle(HWND hWnd)
  {
    this->hClientWindow_ = hWnd;
  }

  HWND ParentWindow::createClientWindow()
  {
    CLIENTCREATESTRUCT ccsClient{ .hWindowMenu = NULL, .idFirstChild = 1000 };

    RECT rect = this->getClientRect();
    HWND hClient = CreateWindow(TEXT("MDICLIENT"), NULL,
      WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_BORDER | WS_VISIBLE, 
      0, 0, rect.right, rect.bottom, this->getHandle(), (HMENU)1, GetModuleHandle(0), &ccsClient);
    if (!hClient)
    {
      Window::getLogger().warn("[%s] %s: %s\n", "ParentWindow", "CreateWindowEx()", Utils::Convert::lpctstrToString(Utils::Windows::getErrorMessage()).c_str());
      return NULL;
    }
    this->setClientWindowHandle(hClient);
    return hClient;
  }

  void ParentWindow::registerCreateCallback()
  {
    /*
    this->messageCallback_.add(WM_CREATE, [&](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
      this->setClientWindowHandle(this->createClientWindow());
      return 0;
    });
    */
    this->messageCallback_.add(WM_DESTROY, [&](HWND, UINT, WPARAM, LPARAM)
    {
      PostQuitMessage(0);
      return 0;
    });
  }

  HWND ParentWindow::createWindow(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPVOID lpData)
  {
    // using namespace std::placeholders;

    this->windowClassEx_.setInstance(hInstance);
    // auto b = std::bind(&Window::MessageCallback::Procedure, this->messageCallback_, _1, _2, _3, _4);
    // auto b = std::mem_fn(&Window::MessageCallback::Procedure);
    // auto b = boost::bind(&Window::MessageCallback::Procedure, this->messageCallback_, _1, _2, _3, _4);
    this->windowClassEx_.setWindowProcedure(Window::MessageCallback::WindowProcedure);
    this->registerWindowClassEx(this->windowClassEx_);

    //this->m_lpWindowClassEx->GetWindowProcedure()(NULL, 0, NULL, NULL);

    HWND hWnd = CreateWindowEx(
      0,
      this->m_lpszClassName,
      TEXT(""),
      // Caption bar with close button
      // WS_CAPTION | WS_SYSMENU,
      WS_OVERLAPPEDWINDOW,
      this->getX(),
      this->getY(),
      this->getWidth(),
      this->getHeight(),
      NULL,
      NULL,
      hInstance,
      NULL
    );

    return hWnd;
  }

  LRESULT CALLBACK ParentWindow::MessageCallback::Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    const auto itr = this->getMap().find(uMsg);

    if (itr != this->getMap().cend())
    {
      itr->second(hWnd, uMsg, wParam, lParam);
      return 0;
    }

    return DefFrameProc(hWnd, reinterpret_cast<ParentWindow*>(Window::getUserData(hWnd))->getClientWindowHandle(), uMsg, wParam, lParam);
  }
}
