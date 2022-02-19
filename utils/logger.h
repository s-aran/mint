#pragma once
#include <stdarg.h>
#include <type_traits>
#include "framework.h"

namespace Utils
{
  class Logger
  {
  public:
    using LoggerId = std::uint64_t;

    enum Level : int
    {
      Trace = 1,
      Info,
      Warn,
      Error,
      Fatal,
    };

  private:
    using logger_type = boost::log::sources::severity_channel_logger_mt<Logger::Level, std::string>;

  protected:
    Logger();

  public:
#if 0
    void trace(const std::string message, ...) const;
    void info(const std::string message, ...) const;
    void warn(const std::string message, ...) const;
    void error(const std::string message, ...) const;
    void fatal(const std::string message, ...) const;
#endif

    template<typename... Args>
    inline void trace(const std::string& message, Args&&... args) 
    {
      this->traceString(Logger::formatArgs(message, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void info(const std::string& message, Args&&... args) 
    {
      this->infoString(Logger::formatArgs(message, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void warn(const std::string& message, Args&&... args) 
    {
      this->warnString(Logger::formatArgs(message, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void error(const std::string& message, Args&&... args) 
    {
      this->errorString(Logger::formatArgs(message, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void fatal(const std::string& message, Args&&... args) 
    {
      this->fatalString(Logger::formatArgs(message, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void trace(LPCTSTR message, Args&&... args) const
    {
      this->traceString(Logger::formatArgs(message, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void info(LPCTSTR message, Args&&... args) const
    {
      this->infoString(Logger::formatArgs(message, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void warn(LPCTSTR message, Args&&... args) const
    {
      this->warnString(Logger::formatArgs(std::string(message), std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void error(LPCTSTR message, Args&&... args) const
    {
      this->errorString(Logger::formatArgs(message, std::forward<Args>(args)...));
    }

    template<typename... Args>
    inline void fatal(LPCTSTR message, Args&&... args) const
    {
      this->fatalString(Logger::formatArgs(message, std::forward<Args>(args)...));
    }

   //  void info(LPCTSTR message, ...) const;

    void writeRaw(const std::string message, ...) const;
    void writeHex(const void* data, size_t size, bool showAscii = false) const;

    void setFilePointer(FILE* fp);
    FILE* getFilePointer() const;

  protected:

  private:
    FILE* filePointer_;
    logger_type internalLogger_;

    void initializeLogger() const;
    Logger::logger_type createLogger() const;
    logger_type& getInternalLogger();
    void setInternalLogger(logger_type logger);

    void traceString(std::string message) ;
    void debugString(std::string message) ;
    void infoString(std::string message) ;
    void warnString(std::string message) ;
    void errorString(std::string message) ;
    void fatalString(std::string message) ;

    void traceFormat(boost::format message) const;
    void debugFormat(boost::format message) const;
    void infoFormat(boost::format message) const;
    void warnFormat(boost::format message) const;
    void errorFormat(boost::format message) const;
    void fatalFormat(boost::format message) const;

  private:
    static const char* NewLine;
    static std::map<LoggerId, Logger> map_;

    static void writeMessage(FILE* fp, const std::string& prefix, const std::string message, ...);
    static void writeMessage(FILE* fp, const std::string& prefix, const std::string& message, va_list list);
    static void writeMessage(FILE* fp, const std::string& prefix, LPCTSTR message, va_list list);
    static void write(FILE* fp, const char* message, ...);
    static void write(FILE* fp, const char* message, va_list list);

    static std::string getLogLevelStringFrom(Logger::Level level);

    template<typename ...Args>
    static inline std::string formatArgs(const std::string& message, Args&&... args)
    {
      return boost::str((boost::format(message) % ... % args));
    }

  public:
    static Logger& getLogger(LoggerId id);
    static bool exists(LoggerId id) ;
    static FILE* getFile(const std::string& filePath);
  };
}

BOOST_LOG_ATTRIBUTE_KEYWORD(channel, "Channel", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", Utils::Logger::Level)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "Timestamp", boost::posix_time::ptime)
