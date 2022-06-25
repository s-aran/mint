#include "pch.h"

namespace Ui
{
  MenuItemBase::MenuItemBase()
  {
    // NOP
  }

  MenuItemBase::~MenuItemBase()
  {
    // NOP
  }

  MENUITEMINFO MenuItemBase::createMenuItemInfo(UINT fMask, UINT fType) const
  {
    MENUITEMINFO menuInfo = { 0 };

    menuInfo.cbSize = sizeof(menuInfo);
    menuInfo.fMask = MIIM_TYPE | fMask;
    menuInfo.fType = fType;
    menuInfo.fState = MFS_ENABLED;

    return menuInfo;
  }

  void MenuItemBase::initialize(UINT fMask, UINT fType)
  {
    auto mii = this->createMenuItemInfo(fMask, fType);
    this->setMenuItemInfo(std::move(mii));
  }

  void MenuItemBase::setMenuItemInfo(MENUITEMINFO&& menuItemInfo)
  {
    // memcpy(&this->m_menuItemInfo, &menuItemInfo, sizeof(menuItemInfo));
    this->m_menuItemInfo = menuItemInfo;
  }

  const MENUITEMINFO& MenuItemBase::getMenuItemInfo() const
  {
    return this->m_menuItemInfo;
  }

  LPMENUITEMINFO MenuItemBase::getMutableMenuItemInfo() 
  {
    return &this->m_menuItemInfo;
  }
}
