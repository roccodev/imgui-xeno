#include "imgui_backend/imgui_nvn.h"
#include "imgui_backend_config.h"
#include "logger/Logger.hpp"
#include "nx/abort.h"

extern "C" void imgui_nvn_init(nvnImGui::InitFunc init, nvnImGui::ProcDrawFunc renderCallback) {
  if (IMGUI_XENO_LOG_TCP) {
    R_ABORT_UNLESS(Logger::instance().init(IMGUI_XENO_LOG_TCP_IP, IMGUI_XENO_LOG_TCP_PORT))
  }

  nvnImGui::addInitFunc(init);
  nvnImGui::InstallHooks();
  nvnImGui::addDrawFunc(renderCallback);
}

extern "C" void* imgui_nvn_bootstrap_hook(const char *functionName, nvnImGui::OrigNvnBootstrap origFn) {
  return nvnImGui::NvnBootstrapHook(functionName, origFn);
}