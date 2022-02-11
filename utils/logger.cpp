#include <cstdlib>
#include <iostream>
#include <sstream>
#include "logger.h"
#include "pch.h"

#define VARIABLEARGS_LOGGER(STR)    va_list vlList; \
                                    va_start(vlList, message);  \
                                    this->writeMessage(this->filePointer_, STR, message, vlList);  \
                                    va_end(vlList)    \

namespace Utils
{
  const char* Logger::NewLine = "\r\n";
  std::map<Logger::LoggerId, Logger> Logger::map_;

  Logger::Logger(): filePointer_(NULL)
  {
    // NOP
  }

  void Logger::setFilePointer(FILE* fp)
  {
    this->filePointer_ = fp;
  }

  FILE* Logger::getFilePointer() const
  {
    return this->filePointer_;
  }

  void Logger::trace(const std::string message, ...) const
  {
    VARIABLEARGS_LOGGER("TRACE");
  }

  void Logger::info(const std::string message, ...) const
  {
    VARIABLEARGS_LOGGER("INFO");
  }

  void Logger::warn(const std::string message, ...) const
  {
    VARIABLEARGS_LOGGER("WARN");
  }

  void Logger::error(const std::string message, ...) const
  {
    VARIABLEARGS_LOGGER("ERROR");
  }

  void Logger::fatal(const std::string message, ...) const
  {
    VARIABLEARGS_LOGGER("FATAL");
  }

  void Logger::info(LPCTSTR message, ...) const
  {
    VARIABLEARGS_LOGGER("INFO");
  }

  void Logger::writeRaw(const std::string message, ...) const
  {
    va_list vlList;
    va_start(vlList, message);
    Logger::write(this->filePointer_, message.c_str(), vlList);
    va_end(vlList);
  }

  void Logger::writeHex(const void* data, size_t size, bool showAscii) const
  {
    if (!data)
    {
      return;
    }

    static const char* HexHeader = "          | 00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F";
    static const char* HexLine = "----------+-------------------------------------------------";
    static const char* AsciiHeader = " | 0123456789ABCDEF";
    static const char* AsciiLine = "-+-----------------";

    if (showAscii)
    {
      this->writeRaw("%s%s%s", HexHeader, AsciiHeader, Logger::NewLine);
      this->writeRaw("%s%s", HexLine, AsciiLine);
    }
    else
    {
      this->writeRaw("%s%s", HexHeader, Logger::NewLine);
      this->writeRaw("%s", HexLine);
    }

    for (size_t i = 0; i < size; i++)
    {
      std::uint8_t masked = static_cast<std::uint8_t>(i & 0x0F);
      
      if (masked == 0x00)
      {
        this->writeRaw("%s %08X |", Logger::NewLine, i);
      }

      if (masked == 0x08)
      {
        this->writeRaw(" ");
      }

      this->writeRaw(" %02X", static_cast<const std::uint8_t*>(data)[i]);

      if (showAscii)
      {
        if ((masked == 0x0F) || (i == size - 1))
        {
          static const auto byteLength = strlen(" 00");
          for (size_t j = 0; j < static_cast<unsigned>(0x0F - masked) * byteLength + ((masked < 0x08) ? 1 : 0); j++)
          {
            this->writeRaw(" ");
          }

          this->writeRaw(" | ");

          for (size_t k = i - masked; k <= i; k++)
          {
            auto b = static_cast<const std::uint8_t*>(data)[k];
            this->writeRaw("%c", (b >= 0x20 && b < 0x7F) ? b : '.');
          }
        }
      }
    }
    this->writeRaw(Logger::NewLine);
  }

  void Logger::writeMessage(FILE* fp, const std::string& prefix, const std::string message, ...)
  {
    va_list vlList;
    va_start(vlList, message);
    Logger::writeMessage(fp, prefix, message, vlList);
    va_end(vlList);
  }

  void Logger::writeMessage(FILE* fp, const std::string& prefix, const std::string& message, va_list list)
  {
    int msgSize = vsnprintf(NULL, 0, message.c_str(), list);
    int prefixSize = snprintf(NULL, 0, "[%s] ", prefix.c_str());

    char* msg= (char*)malloc(msgSize + 1);
    vsnprintf(msg, msgSize, message.c_str(), list);

    const int size = prefixSize + msgSize + 1;
    char* str = (char*)malloc(size);
    snprintf(str, size, "[%s] %s", prefix.c_str(), msg);
    Logger::write(fp, str);

    free(str);
    free(msg);
  }

  void Logger::writeMessage(FILE* fp, const std::string& prefix, LPCTSTR message, va_list list)
  {
#ifdef UNICODE
    std::string str = Utils::Convert::wstringToString(message);
#else
    std::string str = message;
#endif  /* UNICODE */
    Logger::writeMessage(fp, prefix, str, list);
  }

  void Logger::write(FILE* fp, const char* message, ...)
  {
    va_list vlList;
    va_start(vlList, message);
    Logger::write(fp, message, vlList);
    va_end(vlList);
  }

  void Logger::write(FILE* fp, const char* message, va_list list)
  {
    FILE* f = fp ? fp : stderr;
    vfprintf(f, message, list);
    fflush(f);
  }
  
  Logger& Logger::getLogger(LoggerId id)
  {
    Logger::map_.emplace(id, Logger());
    return Logger::map_.find(id)->second;
  }

  bool Logger::exists(LoggerId id) 
  {
    return Logger::map_.find(id) != std::end(Logger::map_);
  }
}

#undef VARIABLEARGS_LOGGER
