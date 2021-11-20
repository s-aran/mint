// utils.cpp : スタティック ライブラリ用の関数を定義します。
//

#include "pch.h"
#include "framework.h"

TCHAR m_lpszWindowsErrorMessage[4096] = { '\0' };

LPCTSTR getErrorMessage()
{
  LPVOID lpMessageBuffer;

  FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      GetLastError(),
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPWSTR)&lpMessageBuffer,
      0,
      NULL
  );


  lstrcpy(m_lpszWindowsErrorMessage, (LPCTSTR)lpMessageBuffer);

  LocalFree(lpMessageBuffer);

  return (LPCWSTR)m_lpszWindowsErrorMessage;
}