#include "pch.h"

namespace Ui
{
  PopupMenu::PopupMenu()
  {
    this->setHandle(CreatePopupMenu());
  }

  PopupMenu::~PopupMenu()
  {
    DestroyMenu(this->getHandle());
  }
}