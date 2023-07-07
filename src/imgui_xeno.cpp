#include "imgui_xeno.h"
#include "imgui_backend/imgui_nvn.h"
#include "logger/Logger.hpp"

extern "C" void imgui_xeno_init(InitFunc init, ProcDrawFunc renderCallback) {
  nvnImGui::addInitFunc(init);
  nvnImGui::InstallHooks();
  nvnImGui::addDrawFunc(renderCallback);
}

extern "C" void* imgui_xeno_bootstrap_hook(const char *functionName, nvnImGui::OrigNvnBootstrap origFn) {
  return nvnImGui::NvnBootstrapHook(functionName, origFn);
}

extern "C" void imgui_xeno_set_logger(LoggerFunc loggerCallback) {
  Logger::instance().forward(loggerCallback);
}