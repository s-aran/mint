#pragma once

#include "framework.h"

namespace Ui
{
  template <typename T>
  class CallbackBase
  {
  public:
    virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

  public:
    CallbackBase()
    {
      this->map_.clear();
    }

    void add(UINT uMsg, T callback)
    {
      this->map_.emplace(uMsg, callback);
    }

    void remove(UINT uMsg)
    {
      this->map_.erase(uMsg);
    }

    const bool has(UINT uMsg) const
    {
      if (this->map_.size() <= 0)
      {
        return false;
      }

      return this->map_.find(uMsg) != std::cend(this->map_);
    }

    const T get(UINT uMsg) const
    {
      auto itr = this->map_.find(uMsg);
      return itr->second;
    }

  protected:
    const std::map<UINT, T>& getMap() const
    {
      return this->map_;
    }

  private:
    std::map<UINT, T> map_;
  };
}