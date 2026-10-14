#include "scn/step/carryitem/UseAlgorithm.h"

#include "gobj/FootState.h"
#include "gobj/Location.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "metafortress.h"
#include "ocoll/Owner.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/arena/Manager.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/IndiviUtil.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/carryitem/VacuumReceiver.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/map/KindUtil.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace carryitem {

namespace {

const common::UseParam& t_param(CarryItem& carryItem) {
    return carryItem.param().common().mUse;
}

}

UseAlgorithm::UseAlgorithm(CarryItem& carryItem)
    : mObj(carryItem)
    , mIsRightDir(false)
    , mIsBackDir(false)
    , mRotH(0.0f)
    , mOffset(0.0f, -0.2f, 0.0f)
    , mOwnerPos()
    , mUseSE(0xF9)
    , mThrowSE(0xFE) {
    init();
}

UseAlgorithm::UseAlgorithm(CarryItem& carryItem, u32 useSE, u32 throwSE)
    : mObj(carryItem)
    , mIsRightDir(false)
    , mIsBackDir(false)
    , mRotH(0.0f)
    , mOffset(0.0f, -0.2f, 0.0f)
    , mOwnerPos()
    , mUseSE(useSE)
    , mThrowSE(throwSE) {
    init();
}

void UseAlgorithm::init() {
    mObj.mapColl().setValid(false);
    mObj.footState().setAir();
    if (mObj.getUser().wasSet()) {
        mIsRightDir = mObj.getUser()->isRightDir();
        mOwnerPos = mObj.getUser()->getOwnerPos();
    }
    mObj.target().setIsRightDir(true);
    mObj.model().rotCtrl().initRotV(0.0f);
    mObj.model().rotCtrl().initRotH(0.0f);
    mObj.model().rotCtrl().setRotHTargetDefault(0.0f);
    mObj.model().rotCtrl().setRotVTargetDefault(0.0f);
    if (mObj.getUser().wasSet()) {
        if (!mObj.getUser()->isNoUseSE()) {
            mObj.soundSE().start(mUseSE);
        }
        mObj.getUser()->clearNoUseSE();
    }
    mObj.resetReleaseType();
    mObj.vacuumReceiver().clearIgnoreAttacker();
    if (mObj.getUser().wasSet()) {
        if (mObj.getUser()->getOCOwner().teamNo() == 0) {
            mObj.setCanGather(false);
        }
        if (mObj.kind() == 2 && mObj.comp().arenaManager().isArena()
            && map::KindUtil::IsArenaStage(mObj.comp().context().mapKind)) {
            mObj.comp().arenaManager().setBoxState(static_cast<scn::arena::ArenaData::BoxState>(2));
        }
    } else if (mObj.kind() == 2 && mObj.comp().arenaManager().isArena()
               && map::KindUtil::IsArenaStage(mObj.comp().context().mapKind)) {
        mObj.comp().arenaManager().setBoxState(static_cast<scn::arena::ArenaData::BoxState>(1));
    }
    if (!IndiviUtil::IsRideItem(mObj.kind()) && IndiviUtil::HasShadow(mObj.kind())) {
        mObj.shadow().setVisibility(false);
    }
    if (map::KindUtil::IsShootingMap(mObj.comp().context().mapKind)) {
        mObj.model().setScale(Vector3::ALL_ONE * 0.5f);
    }
}

#define MF_FUNCTION __dt__Q43scn4step9carryitem12UseAlgorithmFv
UseAlgorithm::~UseAlgorithm() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0x811C9E07;
    asm {
        bl      after1
        opword  MF_WORD(0x38)
        opword  MF_WORD(0x3C)
        opword  0x117E2708
        opword  0xB3092800
    after1:
        mflr    r22
        lwz     r26, 0x0(r22)
        lwz     r30, 0x4(r22)
        add     r26, r26, r22
        add     r30, r30, r26
        stw     r26, start
        stw     r30, end
    }
    mObj.mapColl().setValid(true);
    word = start;
    last = end;
    mObj.target().setIsRightDir(mIsRightDir);
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash ^= *(u16*)word;
        hash *= 0x010001A7;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xB8)
        opword  0x4DF56EAB
    after2:
        mflr    r25
        lwz     r20, 0x0(r25)
        stw     r20, expected
    }
    hash += hash << 3;
    mObj.setCanGather(true);
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0) {
        volatile u32 offset;
        volatile u32 base;
        volatile u32 response;
        volatile u32 unused;

        asm {
            stw     r26, -0x4(r1)
            bl      after3
            opword  MF_WORD(0x108)
        after3:
            mflr    r26
            lwz     r15, 0x0(r26)
            stw     r15, 0x0(r1)
            stw     r26, 0x4(r1)
            mtlr    r15
            bl      after4
            opword  MF_WORD(0x124)
            opword  0x6AD0D300
            opword  0xD904B10D
            opword  MF_WORD(0x130)
        after4:
            mflr    r19
            lwz     r29, 0x0(r19)
            lwz     r26, 0xc(r19)
            stw     r26, unused
            stw     r29, offset
            stw     r19, base
        }
        offset = offset - 0xE1;
        unused = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        if (!IndiviUtil::IsRideItem(mObj.kind()) && IndiviUtil::HasShadow(mObj.kind())) { mObj.shadow().setVisibility(true); }
    }
}
#undef MF_FUNCTION

void UseAlgorithm::procAnim() {
    f32 rate = t_param(mObj)._0;
    f32 target;
    if (mIsBackDir) {
        target = mIsRightDir ? 180.0f : -180.0f;
    } else {
        f32 angle = mObj.kind() == 4 ? 90.0f : 50.0f;
        target = angle * (mIsRightDir ? 1.0f : -1.0f);
    }
    mRotH = mRotH * (1.0f - rate) + target * rate;
    mObj.model().rotCtrl().initRotH(mRotH);
}

void UseAlgorithm::procMove() {
    obj().move().airDecelFall(t_param(mObj)._4, t_param(mObj)._8);
}

bool UseAlgorithm::procConstraint() {
    if (mObj.getUser().operator->() == 0) {
        if (mObj.getReleaseType() == RELEASE_TYPE_THROW) {
            mObj.soundSE().start(mThrowSE);
            f32 rate = mObj.getThrowPowerRate();
            Vector3 velocity(
                t_param(mObj)._14 + rate * (rate * t_param(mObj)._18), t_param(mObj)._1C + rate * t_param(mObj)._20, 0.0f);
            if (mObj.getThrowPower() == 0) {
                velocity.x = 0.0f;
            } else {
                velocity.x *= mIsRightDir ? 1.0f : -1.0f;
            }
            mObj.move().setVelocity(velocity);
        } else {
            mObj.move().resetVelocity();
            mObj.soundSE().start(0xF2);
        }
        Vector3 pos = mObj.location().pos() - mOffset;
        mObj.location().setPos(mOwnerPos);
        mObj.location().updatePrevPos();
        mObj.mapColl().setValid(true);
        if (mObj.getReleaseType() == RELEASE_TYPE_THROW || mObj.kind() == 7) {
            Vector3 offset(0.0f, 0.2f, 0.0f);
            obj().location().setPos(pos + offset);
        } else {
            Vector3 offset(mIsRightDir ? 1.0f : -1.0f, 0.2f, 0.0f);
            obj().location().setPos(mOwnerPos + offset);
        }
        mObj.mapColl().procMapColl();
        mObj.mapColl().reset();
        mObj.worldCage().proc();
        return true;
    }
    mIsRightDir = mObj.getUser()->isRightDir();
    mIsBackDir = mObj.getUser()->isBackDir();
    Vector3 offset = mOffset;
    offset.x *= mIsRightDir ? 1.0f : -1.0f;
    obj().location().setPos(mObj.getUser()->getConstraintPos() + offset);
    mOwnerPos = mObj.getUser()->getOwnerPos();
    return false;
}

void UseAlgorithm::setOffset(const Vector3& offset) {
    mOffset = offset;
}

}}}  // namespace scn::step::carryitem
