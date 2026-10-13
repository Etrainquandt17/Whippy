#ifndef SCN_STEP_ENEMY_SODORY_CUSTOM_H
#define SCN_STEP_ENEMY_SODORY_CUSTOM_H

#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::sodory::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onDamaged();

    f32 getSpeed() const;
    f32 getAnimRate() const;
    void resetBasePosX();
    void setBasePosX();
    void setBasePosX(f32 x);
    f32 getBasePosX();
    void setFrame();
    u32 getFrame() const;
    void setDirectionAll();
    void setDirection();
    void setEyeMtx(hel::math::Matrix34 mtx);
    void setEyeDirection();
    void setEyeDirectionOffs(f32 offs);
    hel::math::Vector3 getPlayerDiff();
    void addOffsY();
    void setPosYR(f32 rot);

private:
    f32 mSpeed;
    f32 mAnimRate;
    f32 mBasePosX;
    f32 mOffsY;
    u32 mFrame;
};

}
}
}
}

#endif
