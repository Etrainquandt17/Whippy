#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_CUSTOM_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/galactaknight/CaptureCtrl.h"
#include "scn/step/boss/galactaknight/CollisionCtrl.h"
#include "scn/step/boss/galactaknight/LandCtrl.h"
#include "scn/step/boss/galactaknight/SwordBeamCtrl.h"
#include "scn/step/boss/galactaknight/ThunderSpineCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::galactaknight::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class Custom : public CustomBase {
public:
    Custom(Boss& boss);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual void onInit();
    virtual void onAppear();
    virtual void onStart();
    virtual void onDamage();
    virtual void onDead();
    virtual void onStateChange();
    virtual void onProcAnim();
    virtual void onProcMove();
    virtual void onProcFixPos();
    virtual void onProcObjCollReact();

    void setWhiteColorAnim();
    CollisionCtrl& collisionCtrl();
    LandCtrl& landCtrl();
    CaptureCtrl& captureCtrl();
    SwordBeamCtrl& swordBeamCtrl();
    ThunderSpineCtrl& thunderSpineCtrl();

private:
    CollisionCtrl mCollisionCtrl;
    LandCtrl mLandCtrl;
    CaptureCtrl mCaptureCtrl;
    SwordBeamCtrl mSwordBeamCtrl;
    ThunderSpineCtrl mThunderSpineCtrl;
    bool _180;
    u32 _184;
};

}
}
}
}

#endif
