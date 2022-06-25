#include "pch.h"
#include "menu_item_separator.h"

namespace Ui
{
  MenuItemSeparator::MenuItemSeparator()
  {
    this->initialize(MIIM_TYPE, MFT_SEPARATOR);
  }

  MenuItemSeparator::~MenuItemSeparator()
  {
    // NOP
  }
}
