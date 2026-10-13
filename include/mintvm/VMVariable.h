#ifndef MINTVM_VMVARIABLE_H
#define MINTVM_VMVARIABLE_H

#include "mintvm/BCModule.h"
#include "mintvm/MValue.h"
#include "mintvm/VMObject.h"
#include "mintvm/XData.h"
#include "types.h"

namespace mintvm {

class VMCore;

class VMVariable : public VMObject {
public:
    VMVariable(const mintx::XData& data, const BCVariable* variable)
        : mName(data.R2String(variable->mName) + 4)
        , mType(data.R2String(variable->mType) + 4) {
        mValue.mU32 = 0;
    }

    virtual ~VMVariable() {}

    u32 sizeOf(const VMCore& core) const;

    const char* mName;
    const char* mType;
    MValue mValue;
};

}

#endif
