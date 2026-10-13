#ifndef SCN_STEP_ENEMY_CLAYN_CUSTOM_H
#define SCN_STEP_ENEMY_CLAYN_CUSTOM_H

#include "hel/math/Matrix34.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::clayn::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onInWater();
    virtual bool onOutWater();
    virtual void onCaptured();
    virtual void onProcFixPos();

    u32 getHideWaitCount() const;
    u32 getWaitCount() const;
    void setRotate(f32 rotate);
    hel::math::Matrix34 rotateForce(f32 rotate);
    f32 normalizeAngle(f32 angle) const;
    void setPos();

private:
    f32 mRotate;
    f32 mRotateTarget;
    u32 mHideWaitCount;
    u32 mWaitCount;
    bool mIsDamaged;
};

}
}
}
}

#endif
