#pragma once

#include <cstddef>

// Manual memory control: some games don't export or expose (with symbols) standard allocator calls.
// Looks like C calls like malloc etc. are still present, though

class Mem {
  typedef void* (*Malloc)(size_t);
  typedef void* (*AlignedAlloc)(size_t, size_t);
  typedef void* (*Realloc)(void*, size_t);
  typedef void (*Free)(void*);

  public:
      Mem() = default;
      static Mem &instance();

      void Init();
      static void* Allocate(size_t size);
      static void* AllocateAlign(size_t align, size_t size);
      static void Deallocate(void *ptr);
      static void* Reallocate(void *ptr, size_t size);

  private:
      Malloc malloc;
      AlignedAlloc alignedAlloc;
      Realloc realloc;
      Free free;
};


