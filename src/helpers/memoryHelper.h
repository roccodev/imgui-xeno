#pragma once

#include "diag/assert.hpp"
#include "logger/Logger.hpp"
#include "nx/abort.h"
#include "ro.h"
#include <cstddef>
#include <cstdint>

// Manual memory control: some games don't export or expose (with symbols) standard allocator calls.
// Looks like C calls like malloc etc. are still present, though

// Need a function to act as the default value
inline void catch_all() {
  EXL_ABORT("Memory not yet loaded");
}

namespace Mem {
  static void *(*Malloc)(size_t) = reinterpret_cast<void* (*)(size_t)>(catch_all);
  static void (*Free)(void*) = reinterpret_cast<void (*)(void*)>(catch_all);
  static void *(*Realloc)(void*, size_t) = reinterpret_cast<void* (*)(void*, size_t)>(catch_all);
  static void *(*AlignedAlloc)(size_t, size_t) = reinterpret_cast<void* (*)(size_t, size_t)>(catch_all);

  void Init();

  void* Allocate(size_t size);

  void* AllocateAlign(size_t align, size_t size);

  void Deallocate(void *ptr);

  void* Reallocate(void *ptr, size_t new_size);
}


