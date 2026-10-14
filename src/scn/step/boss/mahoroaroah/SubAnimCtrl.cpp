#include "scn/step/boss/mahoroaroah/SubAnimCtrl.h"

#include "gobj/Anim.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

SubAnimCtrl::SubAnimCtrl(Boss& boss) : mBoss(boss), mIsValid(false) {}

void SubAnimCtrl::setup() {
    mBoss.model().anim().subAnimSet(0, 1, 8);
    mBoss.model().anim().subAnimAccessor(0).start(true);
    mBoss.model().anim().subAnimSet(1, 1, 9);
    mBoss.model().anim().subAnimAccessor(1).start(true);
    mIsValid = true;
}

void SubAnimCtrl::update() {
    bool isValid = chkValidAnim();
    if (mIsValid != isValid) {
        mIsValid = isValid;
        mBoss.model().anim().subAnimClear(1);
        if (mIsValid) {
            mBoss.model().anim().subAnimSet(1, 1, 9);
            mBoss.model().anim().subAnimAccessor(1).start(true);
        }
    }
}

bool SubAnimCtrl::chkValidAnim() {
    switch (mBoss.model().anim().currentG3DAnimIndex()) {
    case 8:
    case 9:
        return false;
    default:
        return true;
    }
}

}}}}  // namespace scn::step::boss::mahoroaroah
