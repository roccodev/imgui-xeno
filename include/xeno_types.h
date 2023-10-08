#pragma once

#include <cstddef>

typedef void (*ProcDrawFunc)();
typedef void (*InitFunc)();
typedef void (*NewFrameFunc)();
typedef void* (*OrigNvnBootstrap)(const char*);
typedef void (*LoggerFunc)(const char*, size_t);