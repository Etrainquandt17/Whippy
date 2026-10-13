#define MEM_EXPLICITAUTODELETEARRAY_INLINE

#include "scn/step/boss/galactaknight/CaptureCtrl.h"

#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/ObjColl.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

// TODO: the original keeps the search hit in r31 and the component in r30; this gives the two swapped.
CaptureCtrl::CaptureCtrl(Boss& boss) : mBoss(boss), mAttackers(boss.allocator()), mCaptureKind(CAPTURE_KIND_0) {
    while (mAttackers.count() != 4) {
        mAttackers.add<Component&, ::ocoll::SearchHit&>(mBoss.comp(), mBoss.objColl().searchHit());
    }
}

void CaptureCtrl::checkCapture() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        if (!mAttackers[i].isCapture()) {
            if (mAttackers[i].chkCaptureHero()) {
                hero::CaptureHeroStateKind kind = static_cast<hero::CaptureHeroStateKind>(0x24);
                switch (mCaptureKind) {
                case CAPTURE_KIND_0:
                    kind = static_cast<hero::CaptureHeroStateKind>(0x24);
                    break;
                case CAPTURE_KIND_1:
                    kind = static_cast<hero::CaptureHeroStateKind>(0x25);
                    break;
                }
                mAttackers[i].reqChangeState(kind);
                break;
            }
        }
    }
}

void CaptureCtrl::reqStateFinish() {
    if (mCaptureKind == CAPTURE_KIND_1) {
        for (u32 i = 0; i < mAttackers.count(); i++) {
            if (mAttackers[i].isCapture()) {
                mAttackers[i].reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x26));
            }
        }
    }
    clearCapture();
}

void CaptureCtrl::setConstraintPos(const hel::math::Vector3& pos) {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        mAttackers[i].setConstraintPos(pos);
    }
}

void CaptureCtrl::clearCapture() {
    for (u32 i = 0; i < mAttackers.count(); i++) {
        mAttackers[i].clearCapture();
    }
}

void CaptureCtrl::setCaptureKind(CaptureKind kind) {
    mCaptureKind = kind;
}

}}}}  // namespace scn::step::boss::galactaknight
