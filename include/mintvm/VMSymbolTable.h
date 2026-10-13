#ifndef MINTVM_VMSYMBOLTABLE_H
#define MINTVM_VMSYMBOLTABLE_H

#include "mintvm/BCModule.h"
#include "mintvm/MArray.h"
#include "mintvm/VMObject.h"
#include "mintvm/XData.h"
#include "types.h"

namespace mintvm {

class VMSymbolTable : public VMObject {
public:
    VMSymbolTable()
        : mSymbols(allocator(), 0) {}

    VMSymbolTable(const mintx::XData& data, const BCSymbolTable* table);

    virtual ~VMSymbolTable() {}

    const char* symbol(unsigned int index) const {
        return mSymbols.at(index);
    }

private:
    MArray<const char*> mSymbols;
};

}  // namespace mintvm

#endif
