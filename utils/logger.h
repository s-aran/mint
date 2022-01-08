#pragma once
#include <stdarg.h>
#include "framework.h"

namespace Utils
{
  class Logger
  {
  public:
    using LoggerId = std::uint64_t;

  protected:
    Logger();

  public:
    void trace(const std::string message, ...) const;
    void info(const std::string message, ...) const;
    void warn(const std::string message, ...) const;
    void error(const std::string message, ...) const;
    void fatal(const std::string message, ...) const;

    void writeRaw(const std::string message, ...) const;
    void writeHex(const void* data, size_t size, bool showAscii = false) const;

    void setFilePointer(FILE* fp);
    FILE* getFilePointer() const;

  protected:

  private:
    FILE* filePointer_;

  private:
    static const char* NewLine;
    static std::map<LoggerId, Logger> map_;

    static void writeMessage(FILE* fp, const std::string& prefix, const std::string message, ...);
    static void writeMessage(FILE* fp, const std::string& prefix, const std::string& message, va_list list);
    static void write(FILE* fp, const char* message, ...);
    static void write(FILE* fp, const char* message, va_list list);
    
  public:
    static Logger& getLogger(LoggerId id);
    static FILE* getFile(const std::string& filePath);
  };
}
