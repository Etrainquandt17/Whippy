#include "g3d/ResModelContext.h"

namespace g3d {

const char* ResModelContext::DefaultEntryName() {
    return "Model";
}

ResModelContext::ResModelContext(const ResFileAccessor& resFile, const char* name)
    : mResFile(resFile)
    , mName(hel::common::FixedStringIN<char, 40>::FromFormat("%s", name)) {}

}
