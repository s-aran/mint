#pragma once

#include <vector>
#include <map>
#include <utility>
#include <functional>
#include <memory>

#define BOOST_BIND_ENABLE_STDCALL
#include <boost/bind.hpp>

// #define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include <Windows.h>

#include "../utils/framework.h"

#include "classex.h"
#include "callback_base.h"
#include "window.h"
#include "mdi_child.h"
#include "mdi_parent.h"
// #include "defines.h"

#include "menu_item_base.h"
#include "menu_item_string.h"
#include "menu_item_separator.h"
#include "menu_base.h"
#include "menu.h"
#include "popup_menu.h"

#pragma comment(lib, "ui")

void fnui();
