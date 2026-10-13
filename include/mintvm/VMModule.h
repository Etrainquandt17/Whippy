#ifndef MINTVM_VMMODULE_H
#define MINTVM_VMMODULE_H

#include "mintvm/BCModule.h"
#include "mintvm/VMConstantTable.h"
#include "mintvm/VMObject.h"
#include "mintvm/VMObjectTypeList.h"
#include "mintvm/VMSymbolTable.h"
#include "mintvm/XData.h"
#include "types.h"

namespace mintvm {

class VMModule : public VMObject {
public:
    enum Kind {
        KIND_SCRIPT,
        KIND_NATIVE,
    };

    VMModule(const void* data);
    VMModule(const char* path);

    virtual ~VMModule() {}

    const VMConstantTable& constantTable() const {
        return mConstants;
    }

    const VMSymbolTable& symbolTable() const {
        return mSymbols;
    }

    VMObjectTypeList& objectTypeList() {
        return mObjectTypes;
    }

    const VMObjectTypeList& objectTypeList() const {
        return mObjectTypes;
    }

private:
    Kind mKind;
    mintx::XData mData;
    const BCModule* mModule;
    VMConstantTable mConstants;
    VMSymbolTable mSymbols;
    VMObjectTypeList mObjectTypes;
};

}  // namespace mintvm

#endif
