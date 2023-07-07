#pragma once

#include "nn/result.h"
#include "xeno_types.h"


class Logger {
public:
  Logger() = default;

  static Logger &instance();

  void forward(LoggerFunc callback);

  static void log(const char *fmt, ...);

  static void log(const char *fmt, va_list args);

private:
  LoggerFunc forwarder;
};