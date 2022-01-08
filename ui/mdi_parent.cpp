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

    if (!hWnd)
    {
      std::wcout << std::wstring(getErrorMessage()) << std::endl;
      // this->m_lpError->SetWindowsError();

      // g_lpDebug->Error("CreateWindowEx() is Failure. return = 0x%08X, ErrorCode=0x%08X", hWnd, GetLastError());
      // g_lpDebug->Error(this->m_lpError->GetWindowsErrorMessage());

      std::wcout << std::wstring(getErrorMessage()) << std::endl;

      return NULL;
    }

    this->m_hWnd = hWnd;
    // this->setClientSize(480, 320);

    this->setUserData();

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
    return CreateWindow(TEXT("MDICLIENT"), NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, 0, 0, Window::getUserData(this->getHandle())->getHandle(), (HMENU)1, GetModuleHandle(0), &ccsClient);
  }

  void ParentWindow::registerCreateCallback()
  {
    this->messageCallback_.add(WM_CREATE, [&](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
      this->setClientWindowHandle(this->createClientWindow());
      return 0;
    });
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
