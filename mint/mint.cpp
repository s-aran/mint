// mint.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <locale.h>
#include <iostream>

#include "header.h"

// Ui::Window* mainWindow = NULL;
Ui::ParentWindow* mainWindow = NULL;
Ui::ChildWindow* cw = NULL;


int main()
{
  using namespace Ui;

  setlocale(LC_CTYPE, "");
  std::cout << "Hello World!\n";

  Utils::Logger logger = Utils::Logger::getLogger(0);

  WindowClassEx windowClass;
  windowClass.setBackground((HBRUSH)(COLOR_APPWORKSPACE + 1));

  /*
  mainWindow = new Window(TEXT("AAAA"), windowClass);
  */
  mainWindow = new ParentWindow(TEXT("FRAMEWINDOW"), windowClass);
  

  WindowClassEx childClass = windowClass;
  childClass.setBackground((HBRUSH)GetStockObject(WHITE_BRUSH));
  cw = new ChildWindow(TEXT("MDICHILD"), childClass);

  cw->addCallback(WM_MOUSEMOVE, [&](HWND hWnd, UINT, WPARAM wParam, LPARAM lParam)
  {
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    logger.info("(%d, %d)\n", x, y);

    return 0;
  });

  mainWindow->addCallback(Window::WM_CREATED, [&](HWND hWnd, UINT, WPARAM, LPARAM)
  {
    mainWindow->createClientWindow();

    HMENU hMenu = CreateMenu();
    HMENU hSub1 = CreatePopupMenu();
    HMENU hSub2 = CreatePopupMenu();

    MENUITEMINFO menuInfo;

    ZeroMemory(&menuInfo, sizeof(menuInfo));
    menuInfo.cbSize = sizeof(menuInfo);
    menuInfo.fMask = MIIM_TYPE | MIIM_SUBMENU;
    menuInfo.fType = MFT_STRING;
    menuInfo.fState = MFS_ENABLED;

    menuInfo.wID = 0;
    menuInfo.hSubMenu = hSub1;
    menuInfo.dwTypeData = (LPWSTR)TEXT("A");
    InsertMenuItem(hMenu, 0, TRUE, &menuInfo);

    menuInfo.wID = 1;
    menuInfo.hSubMenu = hSub2;
    menuInfo.dwTypeData = (LPWSTR)TEXT("B");
    InsertMenuItem(hMenu, 1, TRUE, &menuInfo);

    menuInfo.fMask = MIIM_TYPE | MIIM_ID;
    // menuInfo.fType = MFT_STRING;

    menuInfo.wID = 0x1001;
    menuInfo.dwTypeData = (LPWSTR)TEXT("Exit");
    InsertMenuItem(hSub1, 0, TRUE, &menuInfo);

    menuInfo.wID = 0x1002;
    menuInfo.dwTypeData = (LPWSTR)TEXT("About");
    InsertMenuItem(hSub2, 0, TRUE, &menuInfo);

    SetMenu(hWnd, hMenu);



    HWND hChild = cw->create(mainWindow->getClientWindowHandle());
    if (hChild == NULL && GetLastError() != NO_ERROR)
    {
      auto errorMessage = Utils::Convert::lpctstrToString(Utils::Windows::getErrorMessage());
      logger.info(errorMessage);
    }

    cw->addCallback(WM_CLOSE, [&](HWND hWnd, UINT, WPARAM, LPARAM)
 {
   printf("closed\n");
   return DestroyWindow(hWnd);
      });

    return 0;
  });

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
