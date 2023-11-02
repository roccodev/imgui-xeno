#include "imgui_xeno.h"
#include "imgui_backend/imgui_nvn.h"
#include "logger/Logger.hpp"

extern "C" void imgui_xeno_init(InitFunc postInitCallback, ProcDrawFunc renderCallback) {
  if (postInitCallback != 0)
    nvnImGui::addPostInitFunc(postInitCallback);

  nvnImGui::InstallHooks();

  if (renderCallback != 0)
    nvnImGui::addDrawFunc(renderCallback);
}

extern "C" void* imgui_xeno_bootstrap_hook(const char *functionName, nvnImGui::OrigNvnBootstrap origFn) {
  return nvnImGui::NvnBootstrapHook(functionName, origFn);
}

extern "C" void imgui_xeno_add_on_pre_init(InitFunc preInitCallback) {
  if (preInitCallback != 0)
    nvnImGui::addPreInitFunc(preInitCallback);
}

extern "C" void imgui_xeno_add_on_new_frame(NewFrameFunc newFrameCallback) {
  if (newFrameCallback != 0)
    nvnImGui::addNewFrameFunc(newFrameCallback);
}

extern "C" void imgui_xeno_set_logger(LoggerFunc loggerCallback) {
  Logger::instance().forward(loggerCallback);
}