#ifndef FILE_FILEMANAGER_H
#define FILE_FILEMANAGER_H

#include "file/FileTree.h"
#include "types.h"

namespace file {

class FileManager : private FileTree {
public:
    FileManager();
    ~FileManager();

    FileTree& treeRoot();
    void disableClearInc();
    void disableClearDec();
    void clearFiles();
    void clearFilesIfEnable();

private:
    s32 mDisableClear;
};

}  // namespace file

#endif
