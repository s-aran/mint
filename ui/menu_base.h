#pragma once

#include "framework.h"

namespace Ui
{
  class MenuBase
  {
  public:
    MenuBase();
    virtual ~MenuBase();

    HMENU getHandle() const;

    int addItem(MenuItemBase&& item);
    void deleteItem(int id);
    bool hasItem(int id) const;

  protected:
    void setHandle(HMENU hMenu);

    MENUINFO createMenuInfo() const;
    const MenuItemBase& getItemBy(int id) const;

  private:
    HMENU m_hMenu;
    
    int m_currentItemId;
    std::map<int, std::unique_ptr<MenuItemBase>> m_items;
  };
}