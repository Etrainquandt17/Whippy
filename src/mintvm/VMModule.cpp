#include "mintvm/VMModule.h"

namespace mintvm {

VMModule::VMModule(const void* data)
    : mKind(KIND_SCRIPT)
    , mData(data)
    , mModule(static_cast<const BCModule*>(mData.dataHeadAddress()))
    , mConstants(static_cast<const BCConstantTable*>(mData.labelAddressWithReference(mModule->mConstantTable)))
    , mSymbols(mData, static_cast<const BCSymbolTable*>(mData.labelAddressWithReference(mModule->_C)))
    , mObjectTypes(mData, static_cast<const BCObjectTypeList*>(mData.labelAddressWithReference(mModule->mObjectTypeList))) {}

VMModule::VMModule(const char* path)
    : mKind(KIND_NATIVE)
    , mData(0)
    , mModule(0)
    , mConstants()
    , mSymbols()
    , mObjectTypes(path) {}

}
