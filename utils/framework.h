#pragma once

#include <map>
#include <string>
#include <cstdint>

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include <Windows.h>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/core/null_deleter.hpp>

#include "logger.h"
#include "string_converter.h"
#include "windows.h"

#pragma comment(lib, "utils")


