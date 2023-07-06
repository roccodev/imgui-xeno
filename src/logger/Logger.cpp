#include "Logger.hpp"
#include "imgui_backend_config.h"
#include "nifm.h"
#include "nx/kernel/svc.h"
#include "socket.h"
#include "util.h"

#include <cstring>

#if IMGUI_XENO_LOG_TCP
char socketPool[0x600000 + 0x20000] __attribute__((aligned(0x1000)));
#endif

Logger &Logger::instance() {
  static Logger instance;
  return instance;
}

nn::Result Logger::init(const char *ip, u16 port) {
  in_addr hostAddress = {0};
  sockaddr serverAddress = {0};

  if (mState != LoggerState::UNINITIALIZED)
    return -1;

  mIsEmulator = !IMGUI_XENO_LOG_TCP;

  if (mIsEmulator) {
    mState = LoggerState::CONNECTED;
    return 0;
  }

  nn::nifm::Initialize();

#if IMGUI_XENO_LOG_TCP
  nn::socket::Initialize(socketPool, 0x600000, 0x20000, 0xE);
#endif

  nn::nifm::SubmitNetworkRequest();

  while (nn::nifm::IsNetworkRequestOnHold()) {
  }

  if (!nn::nifm::IsNetworkAvailable()) {
    mState = LoggerState::UNAVAILABLE;
    return -1;
  }

  if ((mSocketFd = nn::socket::Socket(2, 1, 0)) < 0) {
    mState = LoggerState::UNAVAILABLE;
    return -1;
  }

  nn::socket::InetAton(ip, &hostAddress);

  serverAddress.address = hostAddress;
  serverAddress.port = nn::socket::InetHtons(port);
  serverAddress.family = 2;

  nn::Result result = nn::socket::Connect(mSocketFd, &serverAddress, sizeof(serverAddress));

  mState = result.isSuccess() ? LoggerState::CONNECTED : LoggerState::DISCONNECTED;

  if (mState == LoggerState::CONNECTED) {
    Logger::log("Connected!\n");
  }

  return result;
}

__attribute__((noinline)) void outputDebugString(const char *buf, size_t len) {
  asm("svc 0x27");
}


void Logger::log(const char *fmt, ...) {

  if ((instance().mState != LoggerState::CONNECTED && !IMGUI_XENO_LOG_SVC)
      || (!IMGUI_XENO_LOG_TCP && !IMGUI_XENO_LOG_SVC)) {
    return;
  }

  va_list args;
  va_start(args, fmt);

  char buffer[0x500] = {};

  if (nn::util::VSNPrintf(buffer, sizeof(buffer), fmt, args) > 0) {

    if (IMGUI_XENO_LOG_SVC) {
      outputDebugString(buffer, strlen(buffer));
    }
    if (IMGUI_XENO_LOG_TCP) {
      nn::socket::Send(instance().mSocketFd, buffer, strlen(buffer), 0);
    }
  }

  va_end(args);
}

void Logger::log(const char *fmt, va_list args) {

  if (instance().mState != LoggerState::CONNECTED || !IMGUI_XENO_LOG_TCP)
    return;

  char buffer[0x500] = {};

  if (nn::util::VSNPrintf(buffer, sizeof(buffer), fmt, args) > 0) {
    nn::socket::Send(instance().mSocketFd, buffer, strlen(buffer), 0);
  }
}
