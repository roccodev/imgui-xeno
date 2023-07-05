#include "imgui_backend/imgui_nvn.h"
#include "logger/Logger.hpp"

extern "C" void imgui_nvn_init(nvnImGui::InitFunc init, nvnImGui::ProcDrawFunc renderCallback) {
  Logger::log("Initing imgui nvn");
  nvnImGui::addInitFunc(init);
  nvnImGui::InstallHooks();
  nvnImGui::addDrawFunc(renderCallback);
}

extern "C" void* imgui_nvn_bootstrap_hook(const char *functionName, nvnImGui::OrigNvnBootstrap origFn) {
  return nvnImGui::NvnBootstrapHook(functionName, origFn);
}