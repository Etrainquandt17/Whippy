#ifndef SCN_STEP_ENEMY_BURABURADEE_CUSTOM_H
#define SCN_STEP_ENEMY_BURABURADEE_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/buraburarope/ICustomReceiver.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace buraburadee {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::buraburadee::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace buraburadee {

class Custom : public CustomBase, public weapon::buraburarope::ICustomReceiver {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onVacuumReceive();
    virtual bool onDamaged();
    virtual void onCaptured();
    virtual void onDead();
    virtual void onProcFixPos();
    virtual void onRopeRequireUnsetReceiver(weapon::buraburarope::Custom& rope);

    void ropeFixAnim();
    void ropeFixMove();
    void deeAnimDecide();
    void onDamageProc();
    void ropeSmallOn();
    void offStateChange();
    bool isStateChange();
    void releaseRopeIfExist();
    void revertSetting();
    void requestRope();
    void unsetReceiverRope();

private:
    util::ObjRefHandle<weapon::Weapon> mRope;
    bool mIsRopeRequested;
    bool mIsReceiver;
    bool _1e;
    bool mIsStateChange;
    bool _20;
};

}
}
}
}

#endif
