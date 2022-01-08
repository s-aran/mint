#pragma once

#include <map>
#include <string>
#include <cstdint>

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include <Windows.h>

#include "logger.h"

#pragma comment(lib, "utils")

LPCTSTR getErrorMessage();
