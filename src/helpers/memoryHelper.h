#pragma once

#include "assert.hpp"
#include "logger/Logger.hpp"
#include "nx/abort.h"
#include "ro.h"
#include <cstddef>
#include <cstdint>

// Manual memory control: some games don't export or expose (with symbols) standard allocator calls.
// Looks like C calls like malloc etc. are still present, though

namespace Mem {
  void Init();

  void* Allocate(size_t size);

  void* AllocateAlign(size_t align, size_t size);

  void Deallocate(void *ptr);

  void* Reallocate(void *ptr, size_t new_size);
}


