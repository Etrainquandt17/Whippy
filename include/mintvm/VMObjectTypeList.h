#ifndef MINTVM_VMOBJECTTYPELIST_H
#define MINTVM_VMOBJECTTYPELIST_H

#include "mintvm/BCModule.h"
#include "mintvm/MPtrArray.h"
#include "mintvm/VMObject.h"
#include "mintvm/VMObjectType.h"
#include "mintvm/XData.h"
#include "types.h"

namespace mintvm {

class VMCore;
class VMKey;

class VMObjectTypeList : public VMObject {
public:
    VMObjectTypeList(const char* path);
    VMObjectTypeList(const mintx::XData& data, const BCObjectTypeList* list);

    virtual ~VMObjectTypeList() {}

    u32 sizeOf(const VMCore& core, const char* path) const;
    int offsetOf(const VMCore& core, const VMKey& key) const;

    unsigned int count() const {
        return mObjectTypes.count();
    }

    VMObjectType* objectType(unsigned int index) {
        return mObjectTypes.at(index);
    }

    const VMObjectType* objectType(unsigned int index) const {
        return mObjectTypes.at(index);
    }

private:
    MPtrArray<VMObjectType> mObjectTypes;
};

}  // namespace mintvm

#endif
