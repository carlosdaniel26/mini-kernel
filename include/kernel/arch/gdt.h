#pragma once

#if defined(TARGET_I686)
#include "i686/gdt.h"
#elif defined(TARGET_X86_64)
#include "x86-64/gdt.h"
#else
#error "Unsupported architecture. Define TARGET_I686 or TARGET_X86_64."
#endif