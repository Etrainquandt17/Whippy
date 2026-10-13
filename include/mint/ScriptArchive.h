#ifndef MINT_SCRIPTARCHIVE_H
#define MINT_SCRIPTARCHIVE_H

#include "file/FileAccessor.h"
#include "types.h"
#include "xdata/XData.h"

namespace mint {

class ScriptArchive {
public:
    struct Name {
        u32 length;
        char str[1];
    };

    struct Script {
        const Name* name;
        const void* data;
    };

    ScriptArchive();

    u32 count() const;
    Script at(unsigned long index) const;

private:
    struct Entry {
        u32 name;
        u32 data;
    };

    struct Header {
        u32 count;
        Entry entries[1];
    };

    const Header* header() const;

    file::FileAccessor mFile;
    xdata::XData mXData;
};

}  // namespace mint

#endif
