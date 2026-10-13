#include "mintvm/VMVariable.h"

#include "mintvm/VMCore.h"

namespace mintvm {

u32 VMVariable::sizeOf(const VMCore& core) const {
    return core.sizeOf(mType);
}

}
