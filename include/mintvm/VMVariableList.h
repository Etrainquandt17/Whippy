#ifndef MINTVM_VMVARIABLELIST_H
#define MINTVM_VMVARIABLELIST_H

#include "mintvm/MPtrArray.h"
#include "mintvm/VMObject.h"
#include "mintvm/VMVariable.h"
#include "types.h"

namespace mintvm {

class VMCore;
class VMKey;

class VMVariableList : public VMObject {
public:
    VMVariableList(unsigned long max)
        : mVariables(allocator(), max) {}

    VMVariableList(const mintx::XData& data, const BCVariableList* list)
        : mVariables(allocator(), list->mCount) {
        for (u32 i = 0; i < list->mCount; i++) {
            mVariables.add(new VMVariable(data, static_cast<const BCVariable*>(data.labelAddressWithReference(list->mVariables[i]))));
        }
    }

    virtual ~VMVariableList() {}

    // TODO: VMObjectType::sizeOf expands the same lookup as variable(), which the header must have had inline.
    VMVariable* variableIN(unsigned int index) const {
        return mVariables.at(index);
    }

    unsigned int count() const {
        return mVariables.count();
    }

    VMVariable* variable(unsigned int index) {
        return mVariables.at(index);
    }

    int offsetOf(const VMCore& core, int index) const;
    VMVariable* variable(unsigned int index) const;
    int search(const VMKey& key) const;

private:
    MPtrArray<VMVariable> mVariables;
};

}

#endif
