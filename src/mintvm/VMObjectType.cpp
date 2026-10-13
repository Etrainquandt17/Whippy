#include "mintvm/VMObjectType.h"

#include "mintvm/VMCore.h"

namespace mintvm {

VMObjectType::VMObjectType(const char* path)
    : mPath(path)
    , mVariables(0)
    , mFunctions() {}

VMObjectType::VMObjectType(const mintx::XData& data, const BCObjectType* type)
    : mPath(data.R2String(type->mName) + 4)
    , mVariables(data, static_cast<const BCVariableList*>(data.labelAddressWithReference(type->mVariableList)))
    , mFunctions(data, static_cast<const BCFunctionList*>(data.labelAddressWithReference(type->mFunctionList))) {}

u32 VMObjectType::sizeOf(const VMCore& core) const {
    u32 size = 0;
    for (u32 i = 0; i < mVariables.count(); i++) {
        size += mVariables.variableIN(i)->sizeOf(core);
    }
    return size;
}

}
