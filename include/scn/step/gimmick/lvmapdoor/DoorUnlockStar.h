#ifndef SCN_STEP_GIMMICK_LVMAPDOOR_DOORUNLOCKSTAR_H
#define SCN_STEP_GIMMICK_LVMAPDOOR_DOORUNLOCKSTAR_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/gimmick/Effect.h"
#include "scn/step/gimmick/Model.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace step {

class Component;

namespace gimmick {
namespace lvmapdoor {

class DoorUnlockStar {
public:
    enum State {
        STATE_NONE,
        STATE_START,
        STATE_FLY,
        STATE_DESTROY,
        STATE_END,
    };

    DoorUnlockStar(Component& component);
    ~DoorUnlockStar();

    void setPos(const hel::math::Vector2& from, const hel::math::Vector2& to, const hel::math::Vector2& door);
    void procAnim();
    void start();
    void start_Boss();
    void setZoom(bool, f32);
    void updateZoom();
    void unsetZoom();
    bool isFlyEnd() const;
    void getCameraSetting(hel::math::Vector2& center, f32& zoom);
    f32 getFlyPosRatio(int frame) const;
    void setVisibleDoorPosValid(bool isValid);

private:
    void mfSetupEffect();

    Component& mComponent;
    hel::math::Vector3 mFrom;
    hel::math::Vector3 mTo;
    hel::math::Vector3 mPos;
    bool _28;
    bool mIsBoss;
    hel::math::Vector2 mDoorPos;
    Model mModel;
    Effect mEffect;
    u32 mZoomHandle;
    util::FrameCounter mCounter;
    snd::SERequestor mSE;
    State mState;
};

}
}
}
}

#endif
