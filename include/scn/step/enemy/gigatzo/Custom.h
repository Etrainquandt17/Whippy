#ifndef SCN_STEP_ENEMY_GIGATZO_CUSTOM_H
#define SCN_STEP_ENEMY_GIGATZO_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::gigatzo::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onInWater();
    virtual bool onOutWater();
    virtual void onProcFixPos();

    f32 aimAngle() const;
    bool isBackAttack();
    bool isAir();
    void setAimAngle(f32 angle);
    f32 playerAngle();
    bool isPlayerInAimArea();
    void setWaitEffect();
    int setWaitAttackTime();
    int setWaitBackAttackTime();
    int setWaitBackAttackMoreTime();
    void setModelColor();

private:
    f32 mAimAngle;
    bool mIsBackAttack;
    bool mIsAir;
};

}
}
}
}

#endif
