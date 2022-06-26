#include "pch.h"

namespace Ui
{
  Menu::Menu()
  {
    this->setHandle(CreateMenu());
  }

  Menu::~Menu()
  {
    DestroyMenu(this->getHandle());
  }
}