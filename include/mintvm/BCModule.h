#ifndef MINTVM_BCMODULE_H
#define MINTVM_BCMODULE_H

#include "mintvm/XData.h"
#include "types.h"

namespace mintvm {

struct BCSymbolTable {
    u32 mCount;
    u32 mSymbols[1];
};

struct BCModule {
    void dump(const mintx::XData& data);

    u32 mName;
    u32 mSymbolTable;
    u32 mConstantTable;
    // TODO: VMModule reads the symbol table's reference from here, not from offset 4.
    u32 _C;
    u32 mObjectTypeList;
};

struct BCConstantTable {
    u32 mCount;
    u32 mConstants[1];
};

struct BCFunction {
    u32 mName;
    u32 mInstruction;
};

struct BCFunctionList {
    u32 mCount;
    u32 mFunctions[1];
};

struct BCVariable {
    u32 mName;
    u32 mType;
};

struct BCVariableList {
    u32 mCount;
    u32 mVariables[1];
};

struct BCObjectType {
    u32 mName;
    u32 mVariableList;
    u32 mFunctionList;
};

struct BCObjectTypeList {
    u32 mCount;
    u32 mObjectTypes[1];
};

}

#endif
