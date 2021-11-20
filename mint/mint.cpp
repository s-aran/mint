// mint.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <locale.h>
#include <iostream>

#include "header.h"


HINSTANCE hInstance;

LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  HDC hDC;
  PAINTSTRUCT ps;
  CLIENTCREATESTRUCT ccsClient;

  static HWND hClientWindow;

  switch (uMsg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  case WM_CREATE:
    ccsClient.hWindowMenu = NULL;
    ccsClient.idFirstChild = 1000;
    hClientWindow = CreateWindow(TEXT("Hoge"), NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)1, hInstance, &ccsClient);
    return 0;
  }
  return DefFrameProc(hWnd, hClientWindow, uMsg, wParam, lParam);
}

LPCWSTR GetWindowsErrorMessage()
{
  return getErrorMessage();
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
  return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

int main()
{
  setlocale(LC_CTYPE, "");
  std::cout << "Hello World!\n";

  fnui();
  Window* w = new Window(TEXT("AAAA"));
  w->create(MainWndProc);
  w->show();
  w->MainLoop();
  delete w;

  MSG uMsg;
  WNDCLASSEX wndClass;

  HINSTANCE hInstance = GetModuleHandle(0);

  wndClass.cbSize = sizeof(wndClass);
  wndClass.style = CS_HREDRAW | CS_VREDRAW;
  wndClass.lpfnWndProc = FrameWndProc;
  wndClass.cbClsExtra = wndClass.cbWndExtra = 0;
  wndClass.hInstance = hInstance;
  wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
  wndClass.lpszMenuName = NULL;
  wndClass.lpszClassName = TEXT("MINTMINT");
  wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if (!RegisterClassEx(&wndClass))
  {
    printf("RegisterClassEx failed\n");
    wprintf(L"%ls", GetWindowsErrorMessage());
    return 1;
  }

  HWND hWnd = CreateWindowEx(
    0,
    TEXT("MINTMINT"),
    TEXT("mint"),
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

  if (!hWnd)
  {
    printf("CreateWindowEx failed\n");
    wprintf(L"%ls", GetWindowsErrorMessage());
    return 1;
  }

  while (GetMessage(&uMsg, NULL, 0, 0))
  {
    TranslateMessage(&uMsg);
    DispatchMessage(&uMsg);
  }

  return uMsg.wParam;
}


// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
