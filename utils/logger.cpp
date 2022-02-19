#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
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
    /*
    using namespace boost::log;

    sources::severity_logger<Logger::Level> source;

    using sink_t = sinks::asynchronous_sink<sinks::text_ostream_backend>;
    boost::shared_ptr<sink_t> sink = boost::make_shared<sink_t>();
    boost::shared_ptr<std::ostream> stream(&std::clog, boost::null_deleter{});
    sink->locked_backend()->add_stream(stream);
    // sink->set_filter(boost::log::expressions::is_in_range(severity, Logger::Level::Info, Logger::Level::Fatal));
    sink->set_formatter(expressions::stream << "[" << expressions::format_date_time(timestamp, "%Y/%m/%d %H:%M:%S.%f") << "]" << "[" << severity << "]" << expressions::smessage);
    core::get()->add_sink(sink);
   
    sources::severity_logger<Logger::Level> logger;
    BOOST_LOG_SEV(logger, Logger::Level::Trace) << "Trace";
    BOOST_LOG_SEV(logger, Logger::Level::Info) << "Info";
    BOOST_LOG_SEV(logger, Logger::Level::Warn) << "Warn";
    BOOST_LOG_SEV(logger, Logger::Level::Fatal) << "Fatal";
    {
      BOOST_LOG_SCOPED_LOGGER_ATTR(logger, "Timestamp", attributes::local_clock{})
        BOOST_LOG_SEV(logger, Logger::Level::Error) << "Error";
    }

    sink->flush();

    // boost::log::keywords::format = "[%TimeStamp%][%Tag%][%Scope%]: %Message%";
    */
    this->initializeLogger();
  }

  std::string Logger::getLogLevelStringFrom(Logger::Level level)
  {
    switch (level)
    {
    case Level::Trace:
      return "Trace";
    case Level::Info:
      return "Info";
    case Level::Warn:
      return "Warn";
    case Level::Error:
      return "Error";
    case Level::Fatal:
      return "Fatal";
    default:
      return "Unknown";
    }
  }


  void Logger::initializeLogger() const
  {
    using namespace boost::log;
    using min_severity_filter = expressions::channel_severity_filter_actor<std::string, Logger::Level>;

    // min_severity_filter min_severity = boost::log::expressions::channel_severity_filter(channel, severity);
    // min_severity["general"] = Logger::Level::Error;

    auto log = add_console_log(
      std::clog
      // keywords::filter = min_severity || severity >= Logger::Level::Fatal,
      // keywords::format = "%Tag%[%Timestamp%] %Message%"
    );
    
    log.get()->set_formatter(expressions::stream
        << "["
      << expressions::format_date_time(timestamp, "%Y/%m/%d %H:%M:%S.%f")
      << "]"
      << severity.get_name()
      << expressions::smessage
    );

    log.get()->set_filter(severity >= Logger::Level::Trace);
  }

  Logger::logger_type Logger::createLogger() const
  {
    this->initializeLogger();
    boost::log::add_common_attributes();

    logger_type logger;
    return logger;
  }

  void Logger::setInternalLogger(Logger::logger_type logger)
  {
    this->internalLogger_ = logger;
  }

  Logger::logger_type& Logger::getInternalLogger()
  {
    return this->internalLogger_;
  }

  void Logger::setFilePointer(FILE* fp)
  {
    this->filePointer_ = fp;
  }

  FILE* Logger::getFilePointer() const
  {
    return this->filePointer_;
  }

#if 0
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
#endif

  void Logger::traceString(std::string message) 
  {
    // BOOST_LOG_TRIVIAL(trace) << message;
    auto& logger = this->getInternalLogger();
    BOOST_LOG_SCOPED_LOGGER_ATTR(logger, "Timestamp", boost::log::attributes::local_clock{})
    BOOST_LOG_CHANNEL_SEV(logger, "general", Logger::Level::Trace) << message;
  }

  void Logger::debugString(std::string message) 
  {
    BOOST_LOG_TRIVIAL(debug) << message;
  }

  void Logger::infoString(std::string message) 
  {
    // BOOST_LOG_TRIVIAL(info) << message;
    auto& logger = this->getInternalLogger();
    BOOST_LOG_SCOPED_LOGGER_ATTR(logger, "Timestamp", boost::log::attributes::local_clock{})
    BOOST_LOG_CHANNEL_SEV(logger, "general", Logger::Level::Info) << message;
  }

  void Logger::warnString(std::string message) 
  {
    // BOOST_LOG_TRIVIAL(warning) << message;
    auto& logger = this->getInternalLogger();
    BOOST_LOG_SCOPED_LOGGER_ATTR(logger, "Timestamp", boost::log::attributes::local_clock{})
    BOOST_LOG_CHANNEL_SEV(logger, "general", Logger::Level::Warn) << message;
  }

  void Logger::errorString(std::string message) 
  {
    // BOOST_LOG_TRIVIAL(error) << message;
    auto& logger = this->getInternalLogger();
    BOOST_LOG_SCOPED_LOGGER_ATTR(logger, "Timestamp", boost::log::attributes::local_clock{})
    BOOST_LOG_CHANNEL_SEV(logger, "general", Logger::Level::Error) << message;
  }

  void Logger::fatalString(std::string message) 
  {
    // BOOST_LOG_TRIVIAL(fatal) << message;
    auto& logger = this->getInternalLogger();
    BOOST_LOG_SCOPED_LOGGER_ATTR(logger, "Timestamp", boost::log::attributes::local_clock{})
    BOOST_LOG_CHANNEL_SEV(logger, "general", Logger::Level::Fatal) << message;
  }

  void Logger::traceFormat(boost::format message) const
  {
    BOOST_LOG_TRIVIAL(trace) << message.str();
  }

  void Logger::debugFormat(boost::format message) const
  {
    BOOST_LOG_TRIVIAL(debug) << message.str();
  }

  void Logger::infoFormat(boost::format message) const
  {
    BOOST_LOG_TRIVIAL(info) << message.str();
  }

  void Logger::warnFormat(boost::format message) const
  {
    BOOST_LOG_TRIVIAL(warning) << message.str();
  }

  void Logger::errorFormat(boost::format message) const
  {
    BOOST_LOG_TRIVIAL(error) << message.str();
  }

  void Logger::fatalFormat(boost::format message) const
  {
    BOOST_LOG_TRIVIAL(fatal) << message.str();
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
