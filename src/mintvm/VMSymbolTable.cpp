#include "mintvm/VMSymbolTable.h"

namespace mintvm {

VMSymbolTable::VMSymbolTable(const mintx::XData& data, const BCSymbolTable* table)
    : mSymbols(allocator(), table->mCount) {
    for (u32 i = 0; i < mSymbols.count(); i++) {
        mSymbols.at(i) = data.R2String(table->mSymbols[i]) + 4;
    }
}

}  // namespace mintvm
