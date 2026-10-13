#ifndef APP_APPIMPL_H
#define APP_APPIMPL_H

#include "app/Reset.h"
#include "file/FileManager.h"
#include "font/FontManager.h"
#include "hbm/HomeButtonMenu.h"
#include "hid/HIDManager.h"
#include "preload/PreLoadManager.h"
#include "std/auto_ptr.h"
#include "storage/StorageManager.h"
#include "types.h"

namespace seq {
class ISequence;
}

namespace app {

class System;

class AppImpl {
public:
    AppImpl(System& system);
    ~AppImpl();

    void run(bool flag);
    void runWithRootSequence(std::auto_ptr<seq::ISequence> root);

private:
    // TODO: two base classes with virtual functions.
    u8 _0[0x8];
    System& mSystem;
    Reset mReset;
    u8 _60[0x3E0];
    file::FileManager mFileManager;
    u8 _484[0x3D0];
    font::FontManager mFontManager;
    // TODO: hid::HIDManager is 0x1410 bytes and aligned to 8; its header does
    // not say so yet.
    hid::HIDManager mHidManager __attribute__((aligned(8)));
    u8 _1D88[0x1424 - sizeof(hid::HIDManager)];
    preload::PreLoadManager mPreLoadManager;
    u8 _D900[0x10];
    hbm::HomeButtonMenu mHomeButtonMenu;
    storage::StorageManager mStorageManager;
    u8 _DEF8[0x1EB0];
};

}  // namespace app

#endif
