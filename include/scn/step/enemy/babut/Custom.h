#ifndef SCN_STEP_ENEMY_BABUT_CUSTOM_H
#define SCN_STEP_ENEMY_BABUT_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    bool isPlayerInArea();
    void enableResistCaptureHero();
    void disableResistCaptureHero();
    void setDamageCaptureHero(u32 damage, bool flag);
    bool chkReleaseHero();
    void setSuccessCaptureHero();
    void vomitCaptureHero();
    void startWingSound();
    bool chkCaptureHero();

private:
    // TODO: members.
    u32 _8[19];
};

}
}
}
}

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::babut::Custom>();

}
}

#endif
