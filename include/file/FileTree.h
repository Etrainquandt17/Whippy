#ifndef FILE_FILETREE_H
#define FILE_FILETREE_H

#include "types.h"

namespace mem {
class HeapCompaction;
class IAllocator;
class MemBlock;
}

namespace file {

class FileLoader;
class IFileInitializer;

class FileTree {
public:
    FileTree(mem::IAllocator& allocator1, mem::IAllocator& allocator2, u32 arg1, u32 arg2);
    ~FileTree();

    void setParent(FileTree& parent);
    void unsetParent();
    bool wasSetParent() const;
    void clearFiles();
    void setCompactionHeap(mem::HeapCompaction& heap);
    FileLoader* findFile(const char* path) const;
    FileLoader* addFile(const char* path, const IFileInitializer* initializer);
    FileLoader* addFile(const mem::MemBlock& block, const char* path, const IFileInitializer* initializer);

private:
    u8 _0[0x40];
};

}

#endif
