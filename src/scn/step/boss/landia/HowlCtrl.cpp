#include "scn/step/boss/landia/HowlCtrl.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/landia/Param.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

HowlCtrl::HowlCtrl(Boss& boss) : mBoss(boss), mCount(0), mIsStop(false) {}

void HowlCtrl::update() {
    const Param& param = mBoss.param().landia();
    if (mIsStop) {
        mCount--;
        if (!mBoss.soundSE().loop().isPlaying()) {
            mIsStop = false;
            mBoss.soundSE().loop().setVolume(1.0f);
        }
        f32 volume = static_cast<f32>(mCount) / static_cast<f32>(param.mHowlStopFrame);
        mBoss.soundSE().loop().setVolume(volume);
        if (mCount == 0) {
            mIsStop = false;
            mBoss.soundSE().loop().stop();
            mBoss.soundSE().loop().setVolume(1.0f);
        }
    }
}

void HowlCtrl::reqStop() {
    const Param& param = mBoss.param().landia();
    if (mBoss.soundSE().loop().isPlaying()) {
        mCount = param.mHowlStopFrame;
        mIsStop = true;
    }
}

}
}
}
}
