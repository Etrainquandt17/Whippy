#ifndef SCN_STEP_BOSS_LOWPER_GEARCTRL_H
#define SCN_STEP_BOSS_LOWPER_GEARCTRL_H

#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "scn/step/map/BinItemKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

}
class Boss;
namespace lowper {

class GearCtrl {
public:
    GearCtrl(Boss& boss);
    ~GearCtrl();
    void setup(map::BinItemKind kind, u32 variation);

private:
    Boss& mBoss;
    bool mIsSetup;
    gobj::GearModelDesc mModelDesc;
    gobj::GearAnimDesc mAnimDesc;
};

}}}}  // namespace scn::step::boss::lowper

#endif
