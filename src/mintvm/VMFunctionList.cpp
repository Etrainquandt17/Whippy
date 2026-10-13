#include "mintvm/VMFunctionList.h"

namespace mintvm {

VMFunctionList::VMFunctionList(const mintx::XData& data, const BCFunctionList* list)
    : mFunctions(allocator(), list->mCount) {
    for (u32 i = 0; i < list->mCount; i++) {
        mFunctions.add(new VMFunction(data, static_cast<const BCFunction*>(data.labelAddressWithReference(list->mFunctions[i]))));
    }
}

VMFunction* VMFunctionList::addNativeFunction(const char* name, void (*func)(MintFuncProxy&)) {
    VMFunction* function = new VMFunction(name, func);
    mFunctions.add(function);
    return function;
}

}  // namespace mintvm
