// Provide a C shim for aborting in libnx
#pragma once

#include "types.h"
#include "nn/diag.h"

#ifndef R_ABORT_UNLESS
#define R_ABORT_UNLESS(r)   \
    {                       \
    Result _tmp_r = r;      \
    if(R_FAILED(_tmp_r))    \
        ::nn::diag::detail::AbortImpl(__FILE__, __func__, "Result abort", __LINE__, _tmp_r);   \
    }                                       

#elif
#error "Included abort.h outside of libnx!"
#endif