#ifndef APP_SYSTEM_H
#define APP_SYSTEM_H

#include "freeze/FreezeManager.h"
#include "gfx/GXFifoMemoryManager.h"
#include "gfx/RenderSetting.h"
#include "gfx/VISetting.h"
#include "gfx/XFBManager.h"
#include "hel/common/PrivateSingleton.h"
#include "hid/LibInitializer.h"
#include "snd/SoundManager.h"
#include "types.h"

namespace app {

class System : private hel::common::PrivateSingleton<System> {
public:
    class SDKInitializer {
    public:
        SDKInitializer();
    };

    class MemorySetupper {
    public:
        MemorySetupper();
    };

    class GXInitializer {
    public:
        GXInitializer(gfx::GXFifoMemoryManager& manager);
    };

    System();

    gfx::GXFifoMemoryManager& gxFifoMemoryManager();
    gfx::RenderSetting& renderSetting();
    gfx::XFBManager& xfbManager();

private:
    SDKInitializer mSDKInitializer;
    MemorySetupper mMemorySetupper;
    gfx::GXFifoMemoryManager mGXFifoMemoryManager;
    GXInitializer mGXInitializer;
    gfx::VISetting mVISetting;
    gfx::XFBManager mXFBManager;
    gfx::RenderSetting mRenderSetting;
    freeze::FreezeManager mFreezeManager;
    hid::LibInitializer mHIDLibInitializer;
    snd::SoundManager mSoundManager;
};

}  // namespace app

#endif
