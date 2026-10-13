#ifndef FILE_FILEACCESSOR_H
#define FILE_FILEACCESSOR_H

#include "mem/MemBlock.h"
#include "types.h"

namespace file {

class FileLoader;
class IFileInitializer;

class FileAccessor {
public:
    FileAccessor(const char* path, bool);
    ~FileAccessor();

    bool isLoaded() const;
    mem::MemBlock block() const;
    void load(const char* path, const IFileInitializer* initializer, bool);

private:
    FileLoader* mLoader;
};

}  // namespace file

#endif
