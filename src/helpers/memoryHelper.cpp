#include "helpers/memoryHelper.h"

// Need a function to act as the default value
inline void catch_all() { XENO_ABORT("Memory not yet loaded");
}

static void *(*Malloc)(size_t) = reinterpret_cast<void* (*)(size_t)>(catch_all);
static void (*Free)(void*) = reinterpret_cast<void (*)(void*)>(catch_all);
static void *(*Realloc)(void*, size_t) = reinterpret_cast<void* (*)(void*, size_t)>(catch_all);
static void *(*AlignedAlloc)(size_t, size_t) = reinterpret_cast<void* (*)(size_t, size_t)>(catch_all);

void Mem::Init() {
  uintptr_t mallocFn;
  uintptr_t alignedAllocFn;
  uintptr_t reallocFn;
  uintptr_t freeFn;

  R_ABORT_UNLESS(nn::ro::LookupSymbol(&mallocFn, "malloc"));
  R_ABORT_UNLESS(nn::ro::LookupSymbol(&alignedAllocFn, "aligned_alloc"));
  R_ABORT_UNLESS(nn::ro::LookupSymbol(&freeFn, "free"));
  R_ABORT_UNLESS(nn::ro::LookupSymbol(&reallocFn, "realloc"));

  Malloc = reinterpret_cast<void *(*)(size_t)>(mallocFn);
  AlignedAlloc = reinterpret_cast<void* (*)(size_t, size_t)>(alignedAllocFn);
  Free = reinterpret_cast<void (*)(void*)>(freeFn);
  Realloc = reinterpret_cast<void *(*)(void*, size_t)>(reallocFn);

  Logger::log("Mem initialized\n");
}

void* Mem::Allocate(size_t size) {
  return (Malloc)(size);
}

void* Mem::AllocateAlign(size_t align, size_t size) {
  return (AlignedAlloc)(align, size);
}

void Mem::Deallocate(void *ptr) {
  (Free)(ptr);
}

void* Mem::Reallocate(void *ptr, size_t new_size) {
  return (Realloc)(ptr, new_size);
}