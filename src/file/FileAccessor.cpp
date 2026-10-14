#include "file/FileAccessor.h"

#include "app/Application.h"
#include "file/FileLoader.h"
#include "file/FileManager.h"
#include "file/FileTree.h"

using app::Application;
using hel::common::ExplicitSingleton;

namespace file {

FileAccessor::FileAccessor(const char* path, bool arg)
    : mLoader(0) {
    load(path, 0, arg);
}

bool FileAccessor::isLoaded() const {
    bool loaded = false;
    if (mLoader != 0 && mLoader->isLoaded()) {
        loaded = true;
    }
    return loaded;
}

mem::MemBlock FileAccessor::block() const {
    return mLoader->data();
}

void FileAccessor::load(const char* path, const IFileInitializer* initializer, bool) {
    FileTree& tree = ExplicitSingleton<Application>::object_->fileManager().treeRoot();
    FileLoader* loader = tree.findFile(path);
    if (loader != 0) {
        mLoader = loader;
        return;
    }
    loader = tree.addFile(path, initializer);
    if (loader != 0) {
        mLoader = loader;
    }
}

}  // namespace file
