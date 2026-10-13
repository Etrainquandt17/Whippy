#ifndef MINTVM_VMCONSTANTTABLE_H
#define MINTVM_VMCONSTANTTABLE_H

#include "mintvm/BCModule.h"
#include "mintvm/MintAssert.h"
#include "mintvm/VMObject.h"
#include "types.h"

namespace mintvm {

class VMConstantTable : public VMObject {
public:
    VMConstantTable()
        : mData(0)
        , mSize(0) {}

    VMConstantTable(const BCConstantTable* table)
        : mData(reinterpret_cast<const u8*>(table->mConstants))
        , mSize(table->mCount) {}

    virtual ~VMConstantTable() {}

    const void* get(unsigned short offset) const {
        MINT_ASSERT("VMConstantTable.hpp", 36, offset < mSize);
        return mData + offset;
    }

private:
    const u8* mData;
    u32 mSize;
};

}  // namespace mintvm

#endif
