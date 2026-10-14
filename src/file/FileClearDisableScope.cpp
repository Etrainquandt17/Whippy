#include "file/FileClearDisableScope.h"

#include "app/Application.h"
#include "file/FileManager.h"

using app::Application;
using hel::common::ExplicitSingleton;

namespace file {

FileClearDisableScope::FileClearDisableScope() {
    ExplicitSingleton<Application>::object_->fileManager().disableClearInc();
}

FileClearDisableScope::~FileClearDisableScope() {
    ExplicitSingleton<Application>::object_->fileManager().disableClearDec();
}

}  // namespace file
