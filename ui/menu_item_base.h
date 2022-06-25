#pragma once

#include "framework.h"

namespace Ui
{
  class MenuItemBase
  {
  public:
    MenuItemBase();
    virtual ~MenuItemBase();

    const MENUITEMINFO& getMenuItemInfo() const;

  protected:
    void initialize(UINT fMask, UINT fType);

    MENUITEMINFO createMenuItemInfo(UINT fMask, UINT fType) const;

    void setMenuItemInfo(MENUITEMINFO&& menuItemInfo);
    LPMENUITEMINFO getMutableMenuItemInfo();

  private:
    MENUITEMINFO m_menuItemInfo;
  };
}