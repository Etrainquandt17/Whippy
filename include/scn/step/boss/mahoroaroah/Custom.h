#ifndef SCN_STEP_BOSS_MAHOROAROAH_CUSTOM_H
#define SCN_STEP_BOSS_MAHOROAROAH_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/mahoroaroah/BodyEffectCtrl.h"
#include "scn/step/boss/mahoroaroah/ScriptKind.h"
#include "scn/step/boss/mahoroaroah/SubAnimCtrl.h"
#include "scn/step/boss/mahoroaroah/WaftCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::mahoroaroah::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

class Custom : public CustomBase {
public:
    Custom(Boss& boss);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual void onInit();
    virtual void onAppear();
    virtual void onStart();
    virtual void onDamage();
    virtual void onDead();
    virtual void onProcAnim();
    virtual void onProcMove();
    virtual void onProcFixPos();
    virtual void onProcObjCollReact();

    void reqMotionWait();
    void reqMotionAppearFirstWarpOut(bool flag);
    void reqMotionAppearFirstWarpIn();
    void reqMotionDead();
    void reqMotionStar();
    void reqMotionBoomerang(ScriptKind kind);
    void reqMotionStorm();
    void reqMotionStormEnd();
    void reqMotionOar();
    void reqMotionWarpIn();
    void reqMotionWarpOut();
    void reqMotionBullet(u32 kind);
    void reqMotionAnger();
    void reqMotionEscapeWarpIn();
    void reqMotionEscapeWarpOut();
    BodyEffectCtrl& bodyEffectCtrl();
    WaftCtrl& waftCtrl();

private:
    BodyEffectCtrl mBodyEffectCtrl;
    SubAnimCtrl mSubAnimCtrl;
    WaftCtrl mWaftCtrl;
};

}
}
}
}

#endif
