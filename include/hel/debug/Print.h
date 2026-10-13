#ifndef HEL_DEBUG_PRINT_H
#define HEL_DEBUG_PRINT_H

#include "hel/common/FixedString.h"

namespace hel {
namespace debug {

class Print {
public:
    static common::FixedString<384> HelSPrintfImpl(const char* format, ...);
};

}}  // namespace hel::debug

#endif
