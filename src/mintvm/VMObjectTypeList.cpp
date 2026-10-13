#include "mintvm/VMObjectTypeList.h"

#include "mintvm/MintAssert.h"
#include "mintvm/VMCore.h"
#include "mintvm/VMKey.h"
#include "mintvm/stdc.h"

namespace mintvm {

VMObjectTypeList::VMObjectTypeList(const char* path)
    : mObjectTypes(allocator(), 1) {
    mObjectTypes.add(new VMObjectType(path));
}

VMObjectTypeList::VMObjectTypeList(const mintx::XData& data, const BCObjectTypeList* list)
    : mObjectTypes(allocator(), list->mCount) {
    for (u32 i = 0; i < list->mCount; i++) {
        mObjectTypes.add(new VMObjectType(data, static_cast<const BCObjectType*>(data.labelAddressWithReference(list->mObjectTypes[i]))));
    }
}

u32 VMObjectTypeList::sizeOf(const VMCore& core, const char* path) const {
    for (u32 i = 0; i < count(); i++) {
        if (strcmp(objectType(i)->path(), path) == 0) {
            return objectType(i)->sizeOf(core);
        }
    }
    MINT_ASSERT("VMObjectTypeList.cpp", 46, false);
    return 0;
}

int VMObjectTypeList::offsetOf(const VMCore& core, const VMKey& key) const {
    for (u32 i = 0; i < count(); i++) {
        if (strcmp(key.mNs, objectType(i)->path()) == 0) {
            const VMObjectType* type = objectType(i);
            return type->variableList().offsetOf(core, type->variableList().search(key));
        }
    }
    MINT_ASSERT("VMObjectTypeList.cpp", 61, false);
    return 0;
}

}
