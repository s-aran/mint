#include "pch.h"


namespace Utils
{
  TCHAR m_lpszWindowsErrorMessage[4096] = { '\0' };

  LPCTSTR Windows::getErrorMessage()
  {
    return Windows::getErrorMessage(GetLastError());
  }

  LPCTSTR Windows::getErrorMessage(DWORD dwError)
  {
    LPVOID lpMessageBuffer;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dwError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&lpMessageBuffer,
        0,
        NULL
    );


    lstrcpy(m_lpszWindowsErrorMessage, (LPCTSTR)lpMessageBuffer);

    LocalFree(lpMessageBuffer);

    return (LPCWSTR)m_lpszWindowsErrorMessage;
  }
}