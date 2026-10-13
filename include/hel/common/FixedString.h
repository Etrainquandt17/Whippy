#ifndef HEL_COMMON_FIXEDSTRING_H
#define HEL_COMMON_FIXEDSTRING_H

#include "hel/common/FixedStringIN.h"

namespace hel {
namespace common {

template <int N>
class FixedString : public FixedStringIN<char, N> {
public:
    FixedString() {}
    FixedString(const char* str) : FixedStringIN<char, N>(str) {}
    FixedString(const FixedStringIN<char, N>& other) : FixedStringIN<char, N>(other) {}
};

}}  // namespace hel::common

#endif
