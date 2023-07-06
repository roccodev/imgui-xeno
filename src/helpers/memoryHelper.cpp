#include "memoryHelper.h"
#include "logger/Logger.hpp"
#include "nx/abort.h"
#include "ro.h"

Mem& Mem::instance() {
  static Mem instance;
  return instance;
}

void Mem::Init() {
  uintptr_t mallocFn = 0xDEADBEEF;
  uintptr_t alignedAllocFn = 0xDEADBEEF;
  uintptr_t reallocFn = 0xDEADBEEF;
  uintptr_t freeFn = 0xDEADBEEF;

  R_ABORT_UNLESS(nn::ro::LookupSymbol(&mallocFn, "malloc"));
  R_ABORT_UNLESS(nn::ro::LookupSymbol(&alignedAllocFn, "aligned_alloc"));
  R_ABORT_UNLESS(nn::ro::LookupSymbol(&freeFn, "free"));
  R_ABORT_UNLESS(nn::ro::LookupSymbol(&reallocFn, "realloc"));

  this->malloc = reinterpret_cast<void *(*)(size_t)>(mallocFn);
  this->alignedAlloc = reinterpret_cast<void *(*)(size_t, size_t)>(alignedAllocFn);
  this->free = reinterpret_cast<void (*)(void*)>(freeFn);
  this->realloc = reinterpret_cast<void *(*)(void*, size_t)>(reallocFn);

  Logger::log("Mem initialized\n");
}

void* Mem::Allocate(size_t size) {
  return (Mem::instance().malloc)(size);
}


void Mem::Deallocate(void* ptr) {
  (Mem::instance().free)(ptr);
}

void* Mem::Reallocate(void* ptr, size_t size) {
  return (Mem::instance().realloc)(ptr, size);
}

void* Mem::AllocateAlign(size_t align, size_t size) {
  return (Mem::instance().alignedAlloc)(align, size);
}
