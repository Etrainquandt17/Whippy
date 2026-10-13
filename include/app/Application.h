#ifndef APP_APPLICATION_H
#define APP_APPLICATION_H

#include "hel/common/ExplicitSingleton.h"
#include "hel/common/ScopedPtr.h"

namespace file {
class FDGManager;
class FileManager;
}

namespace font {
class FontManager;
}

namespace gfx {
class GameScreen;
}

namespace hel {
namespace math {
class Random;
}}  // namespace hel::math

namespace hid {
class HIDManager;
}

namespace msg {
class Manager;
}

namespace nand {
class NandManager;
}

namespace preload {
class PreLoadManager;
}

namespace storage {
class StorageManager;
}

namespace app {

class AppImpl;
class HIDErrorMenu;
class NANDErrorMenu;
class Reset;
class ResidentFile;
class SaveInfo;
class System;

class Application : public hel::common::ExplicitSingleton<Application> {
public:
    static void Run(System& system, bool flag);

    Application(System& system, bool flag);
    ~Application();

    file::FDGManager& fdgManager();
    file::FileManager& fileManager();
    font::FontManager& fontManager();
    gfx::GameScreen& gameScreen();
    HIDErrorMenu& hidErrorMenu();
    hid::HIDManager& hidManager();
    msg::Manager& messageManager();
    NANDErrorMenu& nandErrorMenu();
    nand::NandManager& nandManager();
    preload::PreLoadManager& preLoadManager();
    hel::math::Random& random();
    Reset& reset();
    ResidentFile& residentFile();
    storage::StorageManager& storageManager();
    SaveInfo& saveInfo();

private:
    hel::common::ScopedPtr<AppImpl> mImpl;
};

}  // namespace app

#endif
