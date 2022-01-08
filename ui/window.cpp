#include "pch.h"
#include "window.h"


namespace Ui
{
  Window::DialogWindowHandlerVector Window::g_vectorDialogWindows;

  Window::Window(LPCTSTR lpszClassName) :
    m_lpszClassName(lpszClassName),
    m_lpCreateStruct(NULL), m_hWnd(NULL), m_lpszText(NULL),
    m_nX(CW_USEDEFAULT), m_nY(CW_USEDEFAULT), m_nWidth(CW_USEDEFAULT), m_nHeight(CW_USEDEFAULT)
  {
    auto a = this->createWindowClassEx();
    this->windowClassEx_ = a;
  }

  Window::Window(LPCTSTR lpszClassName, WindowClassEx& windowClassEx) :
    m_lpszClassName(lpszClassName),
    m_lpCreateStruct(NULL), m_hWnd(NULL), m_lpszText(NULL),
    m_nX(CW_USEDEFAULT), m_nY(CW_USEDEFAULT), m_nWidth(CW_USEDEFAULT), m_nHeight(CW_USEDEFAULT)
  {
    // g_lpDebug->Info("Called Window constructor!!");
    this->windowClassEx_ = windowClassEx;
    this->windowClassEx_.setClassName(this->m_lpszClassName);
    // this->m_lpError = new CrunError();
  }

  Window::~Window()
  {
    // g_lpDebug->Info("Called Window destructor!!");

    if (!this->m_lpszText)
    {
      // CrunMemory::MemoryFree(this->GetText());
      free(this->m_lpszText);
    }
    this->deleteCreateStruct();
    // delete this->m_lpError;
  }

  HWND Window::create(WNDPROC lpfncWndProc)
  {
    HINSTANCE hInstance = GetModuleHandle(0);
    return this->create(hInstance, lpfncWndProc, NULL);
  }

  HWND Window::create(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPVOID lpData)
  {
    this->windowClassEx_.setInstance(hInstance);
    this->windowClassEx_.setWindowProcedure(lpfnWndProc);
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
      (lpData) ? (LPVOID)this->createCreateStruct(lpData) : NULL
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

  WPARAM Window::MainLoop()
  {
    MSG iMsg = { 0 };

    while (GetMessage(&iMsg, NULL, 0, 0))
    {
      TranslateMessage(&iMsg);
      DispatchMessage(&iMsg);
    }

    return iMsg.wParam;
  }

  WindowClassEx Window::createWindowClassEx()
  {
    WindowClassEx lpWindowClassEx;
    lpWindowClassEx.setClassName(this->m_lpszClassName);

    // g_lpDebug->WriteHex(lpWindowClassEx->GetWindowClassEx(), lpWindowClassEx->GetSize());

    return (lpWindowClassEx);
  }

  void Window::registerWindowClassEx(WindowClassEx& classEx)
  {
    if (!RegisterClassEx(classEx.getWindowClassEx()))
    {
      std::wcout << std::wstring(getErrorMessage()) << std::endl;
    }

    // this->m_lpError->SetSelfError(RegisterClassEx(lpClassEx->GetWindowClassEx()));
    // this->m_lpError->SetWindowsError();

    /*
    if (this->m_lpError->GetSelfError() != 0)
    {
      g_lpDebug->Error("Can not register class.");

      g_lpDebug->Info("Size\t\t0x%08X", lpClassEx->GetSize());
      g_lpDebug->Info("Syle\t\t0x%08X", lpClassEx->GetStyle());
      g_lpDebug->Info("Procedure\t0x%p", lpClassEx->GetWindowProcedure());
      g_lpDebug->Info("ClassExtra\t0x%08X", lpClassEx->GetClassExtra());
      g_lpDebug->Info("WindowExtra\t0x%08X", lpClassEx->GetWindowExtra());
      g_lpDebug->Info("Instance\t\t0x%08X", lpClassEx->GetInstance());
      g_lpDebug->Info("Icon\t\t0x%08X", lpClassEx->GetIcon());
      g_lpDebug->Info("Curosor\t\t0x%08X", lpClassEx->GetCursor());
      g_lpDebug->Info("Background\t0x%08X", lpClassEx->GetBackground());
      g_lpDebug->Info("MenuName\t\t0x%p (%s)", lpClassEx->GetMenuName(), lpClassEx->GetMenuName());
      g_lpDebug->Info("ClassName\t0x%p (%s)", lpClassEx->GetClassName(), lpClassEx->GetClassName());
      g_lpDebug->Info("SmallIcon\t0x%08X", lpClassEx->GetSmallIcon());

      g_lpDebug->Error(this->m_lpError->GetWindowsErrorMessage());
    }
    */
  }

  /*
  void Window::setHandle(HWND hWnd)
  {
    this->m_hWnd = hWnd;
  }
  */

  HWND Window::getHandle() const
  {
    return this->m_hWnd;
  }

  int Window::getX() const
  {
    return this->m_nX;
  }

  int Window::getY() const
  {
    return this->m_nY;
  }

  int Window::getWidth() const
  {
    return this->m_nWidth;
  }

  int Window::getHeight() const
  {
    return this->m_nHeight;
  }

  BOOL Window::setX(int nX)
  {
    BOOL bResult = FALSE;
    this->m_nX = nX;

    if (this->m_hWnd)
    {
      bResult = SetWindowPos(this->m_hWnd, 0, this->getX(), this->getY(), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    return bResult;
  }

  BOOL Window::setY(int nY)
  {
    BOOL bResult = FALSE;
    this->m_nY = nY;

    if (this->m_hWnd)
    {
      bResult = SetWindowPos(this->m_hWnd, 0, this->getX(), this->getY(), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    return bResult;
  }

  BOOL Window::setPosition(int nX, int nY)
  {
    BOOL bResult = FALSE;
    this->m_nX = nX;
    this->m_nY = nY;

    if (this->m_hWnd)
    {
      bResult = SetWindowPos(this->m_hWnd, 0, this->getX(), this->getY(), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }

    return bResult;
  }

  BOOL Window::setWidth(int nWidth)
  {
    BOOL bResult = FALSE;
    this->m_nWidth = nWidth;

    if (this->m_hWnd)
    {
      bResult = SetWindowPos(this->m_hWnd, 0, 0, 0, this->getWidth(), this->getHeight(), SWP_NOMOVE | SWP_NOZORDER);
    }

    return bResult;
  }

  BOOL Window::setHeight(int nHeight)
  {
    BOOL bResult = FALSE;
    this->m_nHeight = nHeight;

    if (this->m_hWnd)
    {
      bResult = SetWindowPos(this->m_hWnd, 0, 0, 0, this->getWidth(), this->getHeight(), SWP_NOMOVE | SWP_NOZORDER);
    }

    return bResult;
  }

  BOOL Window::setSize(int nWidth, int nHeight)
  {
    BOOL bResult = FALSE;

    this->m_nWidth = nWidth;
    this->m_nHeight = nHeight;

    if (this->m_hWnd)
    {
      bResult = SetWindowPos(this->m_hWnd, 0, 0, 0, this->getWidth(), this->getHeight(), SWP_NOMOVE | SWP_NOZORDER);
    }

    return bResult;
  }

  BOOL Window::setText(LPCTSTR lpszText)
  {
    BOOL bResult = FALSE;

    // g_lpDebug->Info("lpszText = %s (0x%p)", lpszText, lpszText);
    this->m_lpszText = (LPTSTR)malloc(lstrlen(lpszText) + 2);
    lstrcpy(this->m_lpszText, lpszText);
    // g_lpDebug->Info("m_lpszText = %s (0x%p)", this->GetText(), this->GetText());

    if (!this->m_hWnd)
    {
      return FALSE;
    }

    bResult = SetWindowText(this->m_hWnd, this->m_lpszText);

    if (bResult == FALSE)
    {
      // g_lpDebug->Error(m_lpError->GetWindowsErrorMessage());

      // g_lpDebug->Error("SetWindowText() Failure!");
      // g_lpDebug->Info("Handle = %08X", this->GetHandle());
      // g_lpDebug->Info("Text = %s", this->GetText());
    }

    return bResult;
  }

  LPCTSTR Window::getText() const
  {
    return this->m_lpszText;
  }

  LPCREATESTRUCT Window::createCreateStruct(LPVOID lpCreateParam)
  {
    this->m_lpCreateStruct = new CREATESTRUCT;

    this->m_lpCreateStruct->lpCreateParams = lpCreateParam;

    return this->m_lpCreateStruct;
  }

  void Window::deleteCreateStruct()
  {
    if (!this->m_lpCreateStruct)
    {
      return;
    }

    delete this->m_lpCreateStruct;
    this->m_lpCreateStruct = NULL;
  }

  void Window::show()
  {
    HWND hWnd = this->m_hWnd;

    if (IsWindow(this->m_hWnd))
    {
      PostMessage(hWnd, WM_SHOWWINDOW, NULL, NULL);
      ShowWindow(hWnd, SW_SHOW);
      UpdateWindow(hWnd);
    }
  }

  void Window::close()
  {
    LRESULT lResult = SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
  }

  BOOL Window::setClientSize(int nClientWidth, int nClientHeight)
  {
    RECT rcClient = { NULL };
    RECT rcWindow = { NULL };

    GetClientRect(this->m_hWnd, &rcClient);
    GetWindowRect(this->m_hWnd, &rcWindow);

    int nWindowWidth = ((rcWindow.right - rcWindow.left) << 1) >> 1;
    int nWindowHeight = ((rcWindow.bottom - rcWindow.top) << 1) >> 1;
    int nWidthDiff = ((nClientWidth - rcClient.right) << 1) >> 1;
    int nHeightDiff = ((nClientHeight - rcClient.bottom) << 1) >> 1;

    return this->setSize(nWindowWidth + nWidthDiff, nWindowHeight + nHeightDiff);
  }

  HINSTANCE Window::getInstance(HWND hWnd)
  {
    HINSTANCE hInstance = NULL;

#ifdef _WIN64
    hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
#else
    hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
#endif /* _WIN64 */

    return hInstance;
  }

  void Window::setData(void* lpData)
  {
    this->m_lpData = lpData;
  }

  void* Window::getData() const
  {
    return this->m_lpData;
  }

  /*
  CrunError* Window::GetError()
  {
    return this->m_lpError;
  }
  */

  void Window::setUserData()
  {
    HWND hWnd = this->getHandle();

#ifdef _WIN64
    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
#elif _WIN32
    SetWindowLong(hWnd, GWL_USERDATA, (LONG)this);
#endif/* _WINxx */
  }

  Window* Window::getUserData(HWND hWnd)
  {
    Window* lpWindow = NULL;
#ifdef _WIN64
    lpWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
#else
    lpWindow = reinterpret_cast<Window*>(GetWindowLong(hWnd, GWL_USERDATA));
#endif /* _WINxx */

    return lpWindow;
  }

  LRESULT CALLBACK Window::MessageCallback::Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    const auto itr = this->getMap().find(uMsg);

    if (itr != this->getMap().cend())
    {
      itr->second(hWnd, uMsg, wParam, lParam);
      return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }
  LRESULT CALLBACK Window::MessageCallback::WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    Window* window = Window::getUserData(hWnd);
    if (window && window->messageCallback_.has(uMsg))
    {
      return window->messageCallback_.get(uMsg)(hWnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }
}