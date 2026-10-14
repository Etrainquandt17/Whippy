#define MEM_MEMBLOCK_IMPLICIT_ASSIGNMENT
#include "file/FileLoader.h"

#include "app/Application.h"
#include "file/IFileInitializer.h"
#include "file/Utility.h"
#include "hel/common/ExplicitSingleton.h"
#include "mem/HeapCompaction.h"
#include "mem/HeapExp.h"
#include "mem/Memory.h"
#include "preload/PreLoadManager.h"
#include "revolution/os/OSCache.h"
#include "std/cstring.h"

using app::Application;
using hel::common::ExplicitSingleton;
using hel::common::FixedString;

namespace file {

namespace {

inline bool t_isCompressed(const char* path) {
    u32 length = strlen(path);
    if (length >= 4 && strcmp(&path[length - 4], ".cmp") == 0) {
        return true;
    }
    return false;
}

}

FileLoader::FileLoader()
    : mAllocator()
    , mCompaction(0)
    , mNode()
    , mPath()
    , mBlock(mem::MemBlock::EmptyBlock())
    , mLatestUpdateDate(0) {}

FileLoader::~FileLoader() {
    if (mAllocator.isValid()) {
        unload();
    }
}

void FileLoader::load(const char* path, mem::IAllocator& allocator, bool arg, const IFileInitializer* initializer) {
    loadIN(path, allocator, 0, arg, initializer, 0);
}

void FileLoader::load(const char* path, mem::HeapCompaction& compaction, bool arg, const IFileInitializer* initializer) {
    loadIN(path, compaction, &compaction, arg, initializer, 0);
}

void FileLoader::load(const mem::MemBlock& block, const char* path, mem::IAllocator& allocator, const IFileInitializer* initializer) {
    loadIN(path, allocator, 0, false, initializer, &block);
}

void FileLoader::unload() {
    if (mAllocator.isValid()) {
        if (data().startAddress() != 0) {
            mAllocator.obj()->allocatorFree(data().startAddress());
        }
        mBlock = mem::MemBlock::EmptyBlock();
        mPath = FixedString<80>();
        mNode = mem::HeapCompactionNodeHandle();
        mCompaction = 0;
        mAllocator = mem::AllocatorHandle();
    }
}

bool FileLoader::isLoaded() const {
    return mAllocator.isValid();
}

mem::MemBlock FileLoader::data() const {
    if (mNode.isValid()) {
        u32 size = mBlock.size();
        return mem::MemBlock(mNode.block().startAddress(), size);
    }
    return mBlock;
}

u32 FileLoader::latestUpdateDate() const {
    return mLatestUpdateDate;
}

void FileLoader::loadIN(const char* path, mem::IAllocator& allocator, mem::HeapCompaction* compaction, bool,
                        const IFileInitializer* initializer, const mem::MemBlock* block) {
    bool hasBlock = block != 0;
    if (hasBlock || Utility::IsExistFileOnUsbOrDvd(path)) {
        mAllocator = mem::AllocatorHandle(allocator);
        if (compaction != 0) {
            mCompaction = compaction;
        }
        mPath = FixedString<80>(path);
        mLatestUpdateDate = Utility::LatestUpdateDateOnUSB(path, true);
        preload::PreLoadManager::FindResult found;
        if (!hasBlock) {
            if (ExplicitSingleton<Application>::IsExist()) {
                found = ExplicitSingleton<Application>::object_->preLoadManager().find(path);
            }
            if (!found.isValid()) {
                Utility::IsFileLoadWarningEnable();
            }
        }
        if (hasBlock) {
            mBlock = Utility::UncompressedFile(*block, allocator);
        } else {
            if (t_isCompressed(path)) {
                if (found.isValid()) {
                    mBlock = Utility::UncompressedFile(found.block(), allocator);
                } else {
                    // TODO: mem::Memory::sceneHeap() returns the HeapExp; mem/Memory.h declares it as its base.
                    mem::IAllocator& tail =
                        static_cast<mem::HeapExp&>(ExplicitSingleton<mem::Memory>::object_->sceneHeap()).allocFromTailAllocator();
                    mem::MemBlock loaded = Utility::LoadFromUsbOrDvd(path, tail);
                    mBlock = Utility::UncompressedFile(loaded, allocator);
                    tail.allocatorFree(loaded.address());
                }
            } else if (found.isValid()) {
                mem::MemBlock source = found.block();
                mBlock = mem::MemBlock(allocator.allocatorAlloc(source.size(), 0x20), source.size());
                memcpy(mBlock.address(), source.address(), source.size());
                DCStoreRangeNoSync(mBlock.address(), mBlock.size());
            } else {
                mBlock = Utility::LoadFromUsbOrDvd(path, allocator);
            }
        }
        if (initializer != 0) {
            initializer->initialize(mBlock);
        }
        if (mCompaction != 0) {
            mNode = mCompaction->search(mBlock.address());
        }
    }
}

}  // namespace file
