#ifndef MINTVM_VMFUNCTIONLIST_H
#define MINTVM_VMFUNCTIONLIST_H

#include "mintvm/BCModule.h"
#include "mintvm/MPtrArray.h"
#include "mintvm/MintSetting.h"
#include "mintvm/VMFunction.h"
#include "mintvm/VMObject.h"
#include "mintvm/XData.h"
#include "types.h"

namespace mintvm {

class VMFunctionList : public VMObject {
public:
    VMFunctionList()
        : mFunctions(allocator(), ExplicitSingleton<MintSetting>::Instance()->_1C) {}

    VMFunctionList(const mintx::XData& data, const BCFunctionList* list);

    virtual ~VMFunctionList() {}

    VMFunction* addNativeFunction(const char* name, void (*func)(MintFuncProxy&));

    unsigned int count() const {
        return mFunctions.count();
    }

    VMFunction* function(unsigned int index) {
        return mFunctions.at(index);
    }

private:
    MPtrArray<VMFunction> mFunctions;
};

}  // namespace mintvm

#endif
