#ifndef SCN_STEP_ENEMY_LANDIASINGLE_CUSTOM_H
#define SCN_STEP_ENEMY_LANDIASINGLE_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "scn/step/enemy/landiasingle/HeadAngleCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::landiasingle::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual void onProcFixPos();

    void incrementFormationPassMoveShotCount();
    void resetFormationPassMoveShotCount();
    bool isFormationPassMoveShotHalfEnd();
    bool isFormationPassMoveShotNoMove();
    void incrementFireRainCount();
    void resetFireRainCount();
    u32 fireRainCount();
    void incrementGrandCrossStopCount();
    void resetGrandCrossStopCount();
    u32 grandCrossStopCount();
    bool flagActionEnd() const;
    void setFlagActionEnd();
    void resetFlagActionEnd();
    HeadAngleCtrl& headAngleCtrl();

private:
    bool mFlagActionEnd;
    u32 mFormationPassMoveShotCount;
    u32 mFireRainCount;
    u32 mGrandCrossStopCount;
    HeadAngleCtrl mHeadAngleCtrl;
};

}
}
}
}

#endif
