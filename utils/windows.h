#pragma once
#include "framework.h"

namespace Utils
{
  class Windows
  {
  public:
    static LPCTSTR getErrorMessage();
    static LPCTSTR getErrorMessage(DWORD dwError);
  };
}