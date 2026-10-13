#include "mint/ScriptArchive.h"

namespace mint {

namespace {

const char* T_FILE_NAME = "mint/Archive.bin.cmp";

}

ScriptArchive::ScriptArchive() : mFile(T_FILE_NAME, false), mXData() {
    if (!mFile.isLoaded()) {
        return;
    }
    mXData = xdata::XData(mFile.block().address());
    mXData.isValidData();
}

u32 ScriptArchive::count() const {
    return header()->count;
}

ScriptArchive::Script ScriptArchive::at(unsigned long index) const {
    Script script = {0, 0};
    script.name = static_cast<const Name*>(mXData.labelAddressWithReference(header()->entries[index].name));
    script.data = mXData.labelAddressWithReference(header()->entries[index].data);
    return script;
}

const ScriptArchive::Header* ScriptArchive::header() const {
    if (mXData.isValidData()) {
        return reinterpret_cast<const Header*>(static_cast<const u8*>(mXData.data()) + 0x10);
    }
    return 0;
}

}
