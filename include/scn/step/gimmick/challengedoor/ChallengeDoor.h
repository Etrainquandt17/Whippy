#ifndef SCN_STEP_GIMMICK_CHALLENGEDOOR_CHALLENGEDOOR_H
#define SCN_STEP_GIMMICK_CHALLENGEDOOR_CHALLENGEDOOR_H

#include "g3d/CharaModel.h"
#include "g3d/ResFileAccessor.h"
#include "hel/math/Vector2.h"
#include "mint/Runner.h"
#include "scn/step/gimmick/Effect.h"
#include "scn/step/gimmick/Model.h"
#include "scn/step/gimmick/Stop.h"
#include "scn/step/gimmick/challengedoor/Result.h"
#include "scn/step/gimmick/spherecount/SphereCount.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace g3d {
class Root;
}

namespace scn {
namespace step {

class Component;

namespace map {
struct BinGmkGeneralEntry;
}

namespace gimmick {
namespace challengedoor {

class ChallengeDoor {
public:
    ChallengeDoor(const map::BinGmkGeneralEntry& entry, Component& component);
    ~ChallengeDoor();

    void registerToRoot(g3d::Root& root);
    void procAnim();
    bool searchAir(const hel::math::Vector2& pos) const;
    bool search(const hel::math::Vector2& pos) const;
    Result check(const hel::math::Vector2& pos) const;
    void startCameraDemo();
    void setToEnter();
    bool isLeaveDoor() const;
    void startLeaveDemo();
    void unlock();
    bool isUnlockEnd() const;
    void setZoom(f32, f32);
    void updateZoom(u32, f32);
    void unsetZoom(u32);

    Component& component() const { return mComponent; }
    const hel::math::Vector2& pos() const { return mPos; }

private:
    void mfSphereCounterRegisterToRoot(g3d::Root& root);
    void mfSeRequest(bool);
    void mfSeStop();
    void mfModelMainSetAnim(const char* name);
    void mfModelMainStart(bool doLoop);
    bool mfModelMainIsAnimEnd();
    void mfUpdateCover();
    void mfEffectSetupDoorRing();
    void mfEffectReleaseDoorRing();
    void mfEffectSetupDoorRelease();
    void mfEffectSetupDoorWelcome();
    void mfEffectReleaseDoorWelcome();

    Component& mComponent;
    Result mResult;
    hel::math::Vector2 mPos;
    g3d::ResFileAccessor mResFile;
    g3d::CharaModel mModelMain;
    Model mIcon;
    Model mBoard;
    int _4F4;
    Stop mStop;
    snd::SERequestor mSe;
    bool _5D4;
    bool _5D5;
    bool _5D6;
    mint::Runner mRunner;
    spherecount::SphereCount mSphereCounter;
    Effect mEffectDoorRelease;
    Effect mEffectDoorRing;
    Effect mEffectDoorWelcome;
    util::FrameCounter _1128;
    util::FrameCounter _1130;
};

}
}
}
}

#endif
