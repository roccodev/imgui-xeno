#pragma once

#include "types.h"

#define IMGUINVN_ADDDRAW(FuncBody) nvnImGui::addDrawFunc([]() {             \
FuncBody                                                                    \
});                                                                         \

namespace nvnImGui {

  typedef void (*ProcDrawFunc)();
  typedef void (*InitFunc)();
  typedef void (*NewFrameFunc)();
  typedef void* (*OrigNvnBootstrap)(const char*);

  void InstallHooks();

  bool InitImGui();

  void procDraw();

  void addDrawFunc(ProcDrawFunc func);
  void addPreInitFunc(InitFunc func);
  void addPostInitFunc(InitFunc func);
  void addNewFrameFunc(NewFrameFunc func);

  void* NvnBootstrapHook(const char *funcName, OrigNvnBootstrap origFn);
}
