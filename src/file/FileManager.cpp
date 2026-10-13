#include "file/FileManager.h"

#include "hel/common/ExplicitSingleton.h"
#include "mem/HeapCompaction.h"
#include "mem/HeapExp.h"
#include "mem/Memory.h"

namespace file {

FileManager::FileManager()
    : FileTree(hel::common::ExplicitSingleton<mem::Memory>::Object().mem1FixHeap(),
               hel::common::ExplicitSingleton<mem::Memory>::Object().externalHeap(), 0x200, 0x10)
    , mDisableClear(0) {
    setCompactionHeap(hel::common::ExplicitSingleton<mem::Memory>::Object().externalHeap());
}

FileTree& FileManager::treeRoot() {
    return *this;
}

void FileManager::disableClearInc() {
    mDisableClear++;
}

void FileManager::disableClearDec() {
    mDisableClear--;
}

void FileManager::clearFiles() {
    FileTree::clearFiles();
}

void FileManager::clearFilesIfEnable() {
    if (mDisableClear == 0) {
        FileTree::clearFiles();
    }
}

}  // namespace file
