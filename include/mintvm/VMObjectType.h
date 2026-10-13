#ifndef MINTVM_VMOBJECTTYPE_H
#define MINTVM_VMOBJECTTYPE_H

#include "mintvm/BCModule.h"
#include "mintvm/VMObject.h"
// The order of these two decides the order of their strings in every unit that destroys a VMObjectType.
#include "mintvm/VMVariableList.h"
#include "mintvm/VMFunctionList.h"
#include "mintvm/XData.h"
#include "types.h"

namespace mintvm {

class VMCore;

class VMObjectType : public VMObject {
public:
    VMObjectType(const char* path);
    VMObjectType(const mintx::XData& data, const BCObjectType* type);

    virtual ~VMObjectType() {}

    u32 sizeOf(const VMCore& core) const;

    const char* path() const {
        return mPath;
    }

    const VMVariableList& variableList() const {
        return mVariables;
    }

    VMVariableList& variableList() {
        return mVariables;
    }

    VMFunctionList& functionList() {
        return mFunctions;
    }

private:
    const char* mPath;
    VMVariableList mVariables;
    VMFunctionList mFunctions;
};

}  // namespace mintvm

#endif
