#include "memoryHelper.h"

void Mem::Init() {
  uintptr_t mallocFn = 0xDEADBEEF;
  uintptr_t alignedAllocFn = 0xDEADBEEF;
  uintptr_t reallocFn = 0xDEADBEEF;
  uintptr_t freeFn = 0xDEADBEEF;

  R_ABORT_UNLESS(nn::ro::LookupSymbol(&mallocFn, "malloc"));
  R_ABORT_UNLESS(nn::ro::LookupSymbol(&alignedAllocFn, "aligned_alloc"));
  R_ABORT_UNLESS(nn::ro::LookupSymbol(&freeFn, "free"));
  R_ABORT_UNLESS(nn::ro::LookupSymbol(&reallocFn, "realloc"));

  Mem::Malloc = reinterpret_cast<void *(*)(size_t)>(mallocFn);
  Mem::AlignedAlloc = reinterpret_cast<void* (*)(size_t, size_t)>(alignedAllocFn);
  Mem::Free = reinterpret_cast<void (*)(void*)>(freeFn);
  Mem::Realloc = reinterpret_cast<void *(*)(void*, size_t)>(reallocFn);

  Logger::log("Mem initialized\n");
}

void* Mem::Allocate(size_t size) {
  return (Mem::Malloc)(size);
}

void* Mem::AllocateAlign(size_t align, size_t size) {
  return (Mem::AlignedAlloc)(align, size);
}

void Mem::Deallocate(void *ptr) {
  (Mem::Free)(ptr);
}

void* Mem::Reallocate(void *ptr, size_t new_size) {
  return (Mem::Realloc)(ptr, new_size);
}