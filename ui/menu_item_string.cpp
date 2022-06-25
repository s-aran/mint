#include "pch.h"

namespace Ui
{
  MenuItemString::MenuItemString(LPCTSTR&& lpszLabel)
  {
    this->initialize(MIIM_TYPE, MFT_STRING);
    auto mii = this->getMutableMenuItemInfo();
    mii->fState = MFS_ENABLED;
    mii->dwTypeData = const_cast<LPWSTR>(lpszLabel);
  }

  MenuItemString::~MenuItemString()
  {
    // NOP
  }

}
