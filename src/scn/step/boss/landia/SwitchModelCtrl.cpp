#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/boss/landia/SwitchModelCtrl.h"

#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Desc.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/chara/Location.h"

using hel::math::Vector2;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace landia {

SwitchModelCtrl::SwitchModelCtrl(Boss& boss) : mBoss(boss) {}

SwitchModelCtrl::~SwitchModelCtrl() {}

void SwitchModelCtrl::createLandiaDummy() {
    Desc desc(static_cast<map::BinBossKind>(0x10), static_cast<map::BinBossVariation>(0), 1, false, mBoss.location().pos().getXY(),
              Vector2::ZERO);
    ObjRefHandle<Boss> dummy = mBoss.comp().bossManager().request(desc);
    if (dummy.isAlive()) {
        mDummy = dummy;
    }
}

void SwitchModelCtrl::deadLandiaDummy() {
    if (mDummy.isAlive()) {
        mDummy->dead();
    }
}

}}}}  // namespace scn::step::boss::landia
