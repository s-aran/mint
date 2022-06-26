#pragma once

#include "framework.h"

namespace Ui
{
  class MenuBase
  {
  public:
    MenuBase();
    virtual ~MenuBase();

    bool build();

    HMENU getHandle() const;

    int addItem(MenuItemBase&& item);
    int insertItem(int id, MenuItemBase&& item);
    void deleteItem(int id);
    bool hasItem(int id) const;

  protected:
    void setHandle(HMENU hMenu);

    MENUINFO createMenuInfo() const;
    const MenuItemBase& getItemBy(int id) const;

  private:
    HMENU m_hMenu;
    
    int m_currentItemId;
    std::vector<std::shared_ptr<MenuItemBase>> m_items;
    std::map<int, std::shared_ptr<MenuItemBase>> m_itemIndex;

    const std::shared_ptr<MenuItemBase>& getItemSharedPtrBy(int id) const;
    int getItemIdBy(const std::shared_ptr<MenuItemBase>& itemSharedPtr);
  };
}