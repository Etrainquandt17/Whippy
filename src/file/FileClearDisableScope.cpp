#include "file/FileClearDisableScope.h"

#include "app/Application.h"
#include "file/FileManager.h"

namespace file {

FileClearDisableScope::FileClearDisableScope() {
    hel::common::ExplicitSingleton<app::Application>::object_->fileManager().disableClearInc();
}

FileClearDisableScope::~FileClearDisableScope() {
    hel::common::ExplicitSingleton<app::Application>::object_->fileManager().disableClearDec();
}

}  // namespace file
