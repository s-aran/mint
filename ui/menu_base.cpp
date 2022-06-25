#include "pch.h"

namespace Ui
{
  MenuBase::MenuBase(): m_currentItemId(0)
  {
    // NOP
  }

  MenuBase::~MenuBase()
  {
    // NOP
  }

  HMENU MenuBase::getHandle() const
  {
    return this->m_hMenu;
  }

  void MenuBase::setHandle(HMENU hMenu)
  {
    this->m_hMenu = hMenu;
  }

  int MenuBase::addItem(MenuItemBase&& item)
  {
    this->m_currentItemId++;
    this->m_items.insert(make_pair(this->m_currentItemId, std::make_unique<MenuItemBase>(item)));
    return this->m_currentItemId;
  }

  void MenuBase::deleteItem(int id)
  {
    this->m_items.erase(id);
  }

  bool MenuBase::hasItem(int id) const
  {
    const auto& itr = this->m_items.find(id);
    return itr != this->m_items.cend();
  }

  const MenuItemBase& MenuBase::getItemBy(int id) const 
  {
    const auto& itr = this->m_items.find(id);
    return *itr->second.get();
  }

  MENUINFO MenuBase::createMenuInfo() const
  {
    MENUINFO menuInfo = { 0 };
    menuInfo.cbSize = sizeof(menuInfo);

    return menuInfo;
  }
}
