#define MEM_EXPLICITAUTODELETEARRAY_INLINE

#include "scn/step/boss/fattybuffer/CannonCaptureCtrl.h"

#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/ObjColl.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

// TODO: the original keeps the search hit in r31 and the component in r30; this gives the two swapped.
CannonCaptureCtrl::CannonCaptureCtrl(Boss& boss) : mBoss(boss), mAttackers(boss.allocator()) {
    while (mAttackers.count() != 4) {
        mAttackers.add<Component&, ::ocoll::SearchHit&>(mBoss.comp(), mBoss.objColl().searchHit());
    }
}

CannonCaptureCtrl::~CannonCaptureCtrl() {}

void CannonCaptureCtrl::checkCapture() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (!mAttackers[i].isCapture()) {
            if (mAttackers[i].chkCaptureHero()) {
                mAttackers[i].reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x17));
                break;
            }
        }
    }
}

void CannonCaptureCtrl::reqStateRelease() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            mAttackers[i].reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x19));
        }
    }
}

void CannonCaptureCtrl::clearCapture() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        mAttackers[i].clearCapture();
    }
}

void CannonCaptureCtrl::setConstraintPos(const hel::math::Vector3& pos) {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        mAttackers[i].setConstraintPos(pos);
    }
}

bool CannonCaptureCtrl::isCapture() const {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (mAttackers[i].isCapture()) {
            return true;
        }
    }
    return false;
}

}
}
}
}
