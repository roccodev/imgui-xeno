/**
* @file ro.h
* @brief Dynamic module API.
*/

#pragma once

#include "nx/types.h"
#include "types.h"

namespace nn {
   namespace ro {
       Result Initialize();
       Result LookupSymbol(uintptr_t* pOutAddress, const char* name);
   };  // namespace ro

};  // namespace nn