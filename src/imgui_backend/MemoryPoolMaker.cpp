#include "MemoryPoolMaker.h"
#include "helpers/memoryHelper.h"
#include "imgui_impl_nvn.hpp"

bool MemoryPoolMaker::createPool(nvn::MemoryPool *result, size_t size, const nvn::MemoryPoolFlags &flags) {

  auto bd = ImguiNvnBackend::getBackendData();

  void *poolPtr = Mem::AllocateAlign(0x1000, size);

  nvn::MemoryPoolBuilder memPoolBuilder{};
  memPoolBuilder.SetDefaults().SetDevice(bd->device).SetFlags(flags).SetStorage(poolPtr, size);

  if (!result->Initialize(&memPoolBuilder)) {
    return false;
  }

  return true;
}