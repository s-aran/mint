#pragma once

#include "framework.h"

namespace Ui
{
  class Window
  {
  public:
    using Callback = std::function<LRESULT(HWND, UINT, WPARAM, LPARAM)>;
    struct MessageCallback : public CallbackBase<Callback>
    {
      virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

      static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };

    static constexpr DWORD WM_CREATED = WM_APP + 1;

  public:
    Window(LPCTSTR lpszClassName);
    Window(LPCTSTR lpszClassName, WindowClassEx& windowClassEx);
    virtual ~Window();

    HWND create(WNDPROC lpfncWndProc);
    HWND create(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPVOID lpData);

    WPARAM MainLoop();

    HWND getHandle() const;

    BOOL setWidth(int nWidth);
    BOOL setHeight(int nHeight);
    BOOL setSize(int nWidth, int nHeight);

    int getHeight() const;
    int getWidth() const;

    BOOL setX(int nX);
    BOOL setY(int nY);
    BOOL setPosition(int nX, int nY);

    int getX() const;
    int getY() const;

    BOOL setText(LPCTSTR lpszText);
    LPCTSTR getText() const;

    void setStyle(DWORD dwStyle);
    DWORD getStyle() const;

    void setExStyle(DWORD dwExStyle);
    DWORD getExStyle() const;

    void show();
    void close();

    void setData(void* lpData);
    void* getData() const;

    // MessageCallback getMessageCallback();

    static HINSTANCE getInstance(HWND hWnd);

    void addCallback(UINT uMsg, Callback cb);
    void removeCallback(UINT uMsg);
    bool hasCallback(UINT uMsg) const;

    RECT getClientRect() const;

  protected:
    typedef std::vector<HWND> DialogWindowHandlerVector;

    static DialogWindowHandlerVector g_vectorDialogWindows;

    static Utils::Logger& getLogger();

    WindowClassEx createWindowClassEx();
    void registerWindowClassEx(WindowClassEx& classEx);
    // void setHandle(HWND hWnd);
    LPCREATESTRUCT createCreateStruct(LPVOID lpCreateParam);
    void deleteCreateStruct();

    void postCreateWindow(HWND hWnd);

    BOOL setClientSize(int nClientWidth, int nClientHeight);

    void setUserData();
    static Window* getUserData(HWND hWnd);

    // CrunError* GetError();

    LPCTSTR m_lpszClassName;

    WindowClassEx windowClassEx_;
    MessageCallback messageCallback_;

    // CrunError* m_lpError;

    LPCREATESTRUCT m_lpCreateStruct;

    HWND m_hWnd;

    LPTSTR m_lpszText;
    DWORD m_dwStyle;
    DWORD m_dwExStyle;
    int m_nX;
    int m_nY;
    int m_nWidth;
    int m_nHeight;
    void* m_lpData;

  private:
    HWND createWindow(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPVOID lpData);
  };

}