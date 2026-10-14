#include "mintvm/VMVariableList.h"

#include "mintvm/VMCore.h"
#include "mintvm/VMKey.h"

namespace mintvm {

int VMVariableList::offsetOf(const VMCore& core, int index) const {
    switch (index) {
    case 0:
        return 0;
    case 1:
        return variable(index - 1)->sizeOf(core);
    default:
        return variable(index - 1)->sizeOf(core) + offsetOf(core, index - 1);
    }
}

VMVariable* VMVariableList::variable(unsigned int index) const {
    return mVariables.at(index);
}

int VMVariableList::search(const VMKey& key) const {
    for (u32 i = 0; i < mVariables.count(); i++) {
        if (strcmp(key.mName, variable(i)->mName) == 0) {
            return i;
        }
    }
    return -1;
}

}  // namespace mintvm
