#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include <Windows.h>


#pragma comment(lib, "utils")

LPCTSTR getErrorMessage();
