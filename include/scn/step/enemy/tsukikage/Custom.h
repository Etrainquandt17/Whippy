#ifndef SCN_STEP_ENEMY_TSUKIKAGE_CUSTOM_H
#define SCN_STEP_ENEMY_TSUKIKAGE_CUSTOM_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::tsukikage::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onVacuumReceive();
    virtual bool onDamaged();
    virtual bool onInWater();

    void setWall(bool isWall);
    bool isWall();
    void requestShuriken();
    s32 getJumpNum();
    bool isJumpAttack();
    bool isWallAttack();
    void setWarp(bool isWarp);
    s32 setJumpNum();
    bool isFirstAppear();
    void setFirstAppear(bool isFirstAppear);
    hel::math::Vector3 getBasePos();

private:
    bool mIsWall;
    bool mIsNear;
    bool mIsFirstAppear;
    bool mIsWarp;
    hel::math::Vector3 mBasePos;
    s32 mPrevJumpNum;
    s32 mJumpNum;
};

}
}
}
}

#endif
