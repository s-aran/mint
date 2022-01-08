// mint.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <locale.h>
#include <iostream>

#include "header.h"

// Ui::Window* mainWindow = NULL;
Ui::ParentWindow* mainWindow = NULL;
Ui::ChildWindow* cw = NULL;

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
    // fnui();

    ccsClient.hWindowMenu = NULL;
    ccsClient.idFirstChild = 1000;
    hClientWindow = CreateWindow(TEXT("MDICLIENT"), NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, 0, 0, 0, 0, hWnd, (HMENU)1, GetModuleHandle(0), &ccsClient);

    // CreateMDIWindow(TEXT("MDICHILD"), TEXT("Piyo"), 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hClientWindow, hInstance, 0);
    HWND hChild = cw->create(hClientWindow, DefMDIChildProc);
    cw->setSize(320, 240);
    return 0;
  }

  return DefFrameProc(hWnd, hClientWindow, uMsg, wParam, lParam);
}

int main()
{
  using namespace Ui;

  setlocale(LC_CTYPE, "");
  std::cout << "Hello World!\n";

  WindowClassEx windowClass;
  windowClass.setBackground((HBRUSH)(COLOR_APPWORKSPACE + 1));

  /*
  mainWindow = new Window(TEXT("AAAA"), windowClass);
  */
  mainWindow = new ParentWindow(TEXT("AAAA"), windowClass);
  

  WindowClassEx childClass = windowClass;
  childClass.setBackground((HBRUSH)GetStockObject(WHITE_BRUSH));
  cw = new ChildWindow(TEXT("MDICHILD"), childClass);


  mainWindow->create();
  mainWindow->show();

  mainWindow->MainLoop();

  delete cw;
  delete mainWindow;

  return 0;
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
