#include "g3d/ResModelContext.h"

using hel::common::FixedStringIN;

namespace g3d {

const char* ResModelContext::DefaultEntryName() {
    return "Model";
}

ResModelContext::ResModelContext(const ResFileAccessor& resFile, const char* name)
    : mResFile(resFile)
    , mName(FixedStringIN<char, 40>::FromFormat("%s", name)) {}

}  // namespace g3d
