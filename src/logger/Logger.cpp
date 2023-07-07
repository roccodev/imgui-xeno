#include "Logger.hpp"
#include "imgui_backend_config.h"
#include "nifm.h"
#include "util.h"
#include <cstring>

#if IMGUI_XENO_LOG_TCP
char socketPool[0x600000 + 0x20000] __attribute__((aligned(0x1000)));
#endif

Logger &Logger::instance() {
  static Logger instance;
  return instance;
}

NOINLINE void outputDebugString(const char *buf, size_t len) {
  asm("svc 0x27");
}

void Logger::log(const char *fmt, ...) {

  if (!IMGUI_XENO_LOG_SVC && !instance().forwarder) {
    return;
  }

  va_list args;
  va_start(args, fmt);
  Logger::log(fmt, args);
  va_end(args);
}

void Logger::log(const char *fmt, va_list args) {
  auto instance = Logger::instance();

  if (!IMGUI_XENO_LOG_SVC && !instance.forwarder) {
    return;
  }

  char buffer[0x500] = {};

  if (nn::util::VSNPrintf(buffer, sizeof(buffer), fmt, args) > 0) {
    if (instance.forwarder) {
      (instance.forwarder)(buffer, strlen(buffer));
    } else if (IMGUI_XENO_LOG_SVC) {
      outputDebugString(buffer, strlen(buffer));
    }
  }
}

void Logger::forward(LoggerFunc callback) {
  this->forwarder = callback;
}
