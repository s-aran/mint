#pragma once

#include "framework.h"

namespace Ui
{
  class MenuItemString : public MenuItemBase
  {
  public:
    MenuItemString(LPCTSTR&& lpszLabel);
    virtual ~MenuItemString();
  };
}