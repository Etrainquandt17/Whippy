#ifndef SCN_STEP_BOSS_FATTYBUFFER_CUSTOM_H
#define SCN_STEP_BOSS_FATTYBUFFER_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/fattybuffer/CannonCaptureCtrl.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/EnemyReqBuff.h"
#include "scn/step/boss/fattybuffer/EyeCtrl.h"
#include "scn/step/boss/fattybuffer/MapCollCtrl.h"
#include "scn/step/boss/fattybuffer/PostureCtrl.h"
#include "scn/step/boss/fattybuffer/StalactiteCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::fattybuffer::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

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
    virtual void onProcFixPos();

    void setSubAnimEyeNormal();
    void setSubAnimEyeAngry();
    CollisionCtrl& collisionCtrl();
    MapCollCtrl& mapCollCtrl();
    EnemyReqBuff& enemyReqBuff();
    PostureCtrl& postureCtrl();
    StalactiteCtrl& stalactiteCtrl();
    CannonCaptureCtrl& cannonCaptureCtrl();

private:
    CollisionCtrl mCollisionCtrl;
    MapCollCtrl mMapCollCtrl;
    EnemyReqBuff mEnemyReqBuff;
    EyeCtrl mEyeCtrl;
    PostureCtrl mPostureCtrl;
    StalactiteCtrl mStalactiteCtrl;
    CannonCaptureCtrl mCannonCaptureCtrl;
};

}
}
}
}

#endif
