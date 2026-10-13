#ifndef SCN_STEP_ENEMY_LANZER_CUSTOM_H
#define SCN_STEP_ENEMY_LANZER_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::lanzer::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onDamaged();

    f32 getSpeed() const;
    f32 getAnimRate() const;
    u32 getLoopCount() const;
    u32 getNowLoop() const;
    void resetNowLoop();
    void incNowLoop();
    void resetBasePosX();
    void setBasePosX();
    void setBasePosX(f32 x);
    f32 getBasePosX();
    void setTurnFlag();
    void resetTurnFlag();
    bool getTurnFlag();
    void setDir(bool dir);
    bool getDir();

private:
    f32 mSpeed;
    f32 mAnimRate;
    u32 mLoopCount;
    u32 mNowLoop;
    f32 mBasePosX;
    bool mTurnFlag;
    bool mDir;
};

}
}
}
}

#endif
