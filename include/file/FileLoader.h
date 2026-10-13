#ifndef FILE_FILELOADER_H
#define FILE_FILELOADER_H

#include "hel/common/FixedString.h"
#include "hel/common/NonCopyable.h"
#include "mem/AllocatorHandle.h"
#include "mem/HeapCompactionNodeHandle.h"
#include "mem/MemBlock.h"
#include "types.h"

namespace mem {
class HeapCompaction;
}

namespace file {

class IFileInitializer;

class FileLoader : private hel::common::NonCopyable {
public:
    FileLoader();
    ~FileLoader();

    void load(const char* path, mem::IAllocator& allocator, bool, const IFileInitializer* initializer);
    void load(const char* path, mem::HeapCompaction& compaction, bool, const IFileInitializer* initializer);
    void load(const mem::MemBlock& block, const char* path, mem::IAllocator& allocator, const IFileInitializer* initializer);
    void unload();

    bool isLoaded() const;
    mem::MemBlock data() const;
    u32 latestUpdateDate() const;

private:
    void loadIN(const char* path, mem::IAllocator& allocator, mem::HeapCompaction* compaction, bool,
                const IFileInitializer* initializer, const mem::MemBlock* block);

    mem::AllocatorHandle mAllocator;
    mem::HeapCompaction* mCompaction;
    mem::HeapCompactionNodeHandle mNode;
    hel::common::FixedString<80> mPath;
    mem::MemBlock mBlock;
    u32 mLatestUpdateDate;
};

}  // namespace file

#endif
