#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H

#include "hel/common/FixedString.h"
#include "hel/common/MutableArray.h"
#include "mem/MemBlock.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace file {

class Utility {
public:
    static mem::MemBlock LoadFromUsbOrDvd(const char* path, mem::IAllocator& allocator);
    static bool IsExistFileOnUsbOrDvd(const char* path);
    static bool IsFileLoadWarningEnable();
    static void SetIsFileLoadWarningEnable(bool enable);
    static void DNProcess(const hel::common::MutableArray<hel::common::FixedString<64>, 24>& paths, bool);
    static mem::MemBlock UncompressedFile(const mem::MemBlock& block, mem::IAllocator& allocator);
    static u32 LatestUpdateDateOnUSB(const char* path, bool);
};

}  // namespace file

#endif
