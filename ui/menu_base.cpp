#include "pch.h"

namespace Ui
{
  MenuBase::MenuBase() : m_hMenu(NULL), m_currentItemId(0)
  {
    // NOP
  }

  MenuBase::~MenuBase()
  {
    this->m_hMenu = NULL;
    this->m_currentItemId = 0; 
  }

  bool MenuBase::build()
  {
    const auto size = this->m_items.size();
    const BOOL fByPosition = TRUE;

    for (int i = 0; i < size; i++)
    {
      const auto& itr = this->m_items[i];

      if (this->getItemIdBy(itr) <= 0)
      {
        return false;
      }

      const auto& item = itr.get();
      InsertMenuItem(this->m_hMenu, i, fByPosition, &item->getMenuItemInfo());
    }

    return true;
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

    const auto ptr = std::make_shared<MenuItemBase>(item);

    // add vector
    this->m_items.push_back(ptr);

    // add index
    this->m_itemIndex.emplace(std::make_pair(this->m_currentItemId, ptr));
    return this->m_currentItemId;
  }

  int MenuBase::insertItem(int id, MenuItemBase&& item)
  {
    this->m_currentItemId++;
    const auto ptr = std::make_shared<MenuItemBase>(item);

    // add vector
    {
      const auto& itr = std::find(
        std::cbegin(this->m_items),
        std::cend(this->m_items),
        this->getItemSharedPtrBy(id)
      );
      this->m_items.insert(itr, ptr);
    }

    // add index
    {
      this->m_itemIndex.emplace(
        std::make_pair(this->m_currentItemId, ptr)
      );
    }

    return this->m_currentItemId;
  }

  void MenuBase::deleteItem(int id)
  {
    // remove vector
    {
      const auto& itr = std::find(
        std::cbegin(this->m_items),
        std::cend(this->m_items),
        this->getItemSharedPtrBy(id)
      );
      this->m_items.erase(itr);
    }

    // remove index
    this->m_itemIndex.erase(id);
  }

  bool MenuBase::hasItem(int id) const
  {
    return this->m_itemIndex.count(id) > 0;
  }

  const MenuItemBase& MenuBase::getItemBy(int id) const
  {
    return *this->getItemSharedPtrBy(id).get();
  }

  const std::shared_ptr<MenuItemBase>& MenuBase::getItemSharedPtrBy(int id) const
  {
    return this->m_itemIndex.at(id);
  }

  int MenuBase::getItemIdBy(const std::shared_ptr<MenuItemBase>& itemSharedPtr)
  {
    for (const auto& itr : this->m_itemIndex)
    {
      if (itr.second == itemSharedPtr)
      {
        return itr.first;
      }
    }

    return 0;
  }

  MENUINFO MenuBase::createMenuInfo() const
  {
    MENUINFO menuInfo = { 0 };
    menuInfo.cbSize = sizeof(menuInfo);

    return menuInfo;
  }
}
