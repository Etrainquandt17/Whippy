#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/cappy/Custom.h"

#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Vector2.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/cappy/ParamData.h"
#include "scn/step/enemy/cappy/StateLostHat.h"
#include "scn/step/enemy/cappy/StateSkinned.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy)
    , mCap(true)
    , mCanCatch(true)
    , mIsValidTurn(true)
    , mThrowCount(0)
    , mIsSearchHat(false)
    , mIsLostHat(false)
    , mSearchHatFrame(0) {}

bool Custom::onInit() {
    obj().model().model().nodes().at(3).setVisibility(false);
    return false;
}

void Custom::onProcFixPos() {
    if (mIsSearchHat) {
        mSearchHatFrame--;
        if (mSearchHatFrame == 0) {
            mIsLostHat = true;
            obj().stateChanger().setNextState<StateLostHat, Enemy*>(&obj());
            obj().stateChanger().changeStateIfPossible();
        }
    }
}

bool Custom::onVacuumReceive() {
    if (obj().model().model().nodes().at(2).isVisible()) {
        f32 x = obj().location().pos().x;
        map::BinEnemyDirType dirType;
        hel::math::Vector2 attackerPos = obj().vacuumReceiver().getAttackerPos();
        if (attackerPos.x > x) {
            dirType = static_cast<map::BinEnemyDirType>(3);
        } else {
            dirType = static_cast<map::BinEnemyDirType>(2);
        }
        obj().setPotentialCount(1);
        hel::math::Vector2 pos = obj().location().pos().getXY();
        Desc desc(static_cast<map::BinEnemyKind>(0x92), obj().variation(), obj().level(), dirType, obj().size(), false, false, pos);
        util::ObjRefHandle<Enemy> skinned = obj().comp().enemyManager().request(desc);
        if (skinned.isAlive()) {
            if (obj().objGenerator() != 0) {
                ogen::Generator& generator = *obj().objGenerator();
                skinned->setObjGenerator(generator);
            }
            skinned->stateChanger().setNextState<StateSkinned, Enemy*>(skinned.operator->());
            skinned->stateChanger().changeStateIfPossible();
        }
        obj().model().model().nodes().at(1).setVisibility(false);
    }
    mIsSearchHat = false;
    disableCatch();
    return false;
}

bool Custom::onHitPointIsZero() {
    mIsSearchHat = false;
    disableCatch();
    return false;
}

bool Custom::onDamaged() {
    mIsSearchHat = false;
    disableCatch();
    return false;
}

void Custom::onDead() {
    mIsSearchHat = false;
    disableCatch();
}

void Custom::onCaptured() {
    mIsSearchHat = false;
    disableCatch();
}

void Custom::disableCatch() {
    mCanCatch = false;
}

void Custom::enableCatch() {
    mCanCatch = true;
}

bool Custom::isCanHat() {
    return mCanCatch;
}

bool Custom::cap() const {
    return mCap;
}

void Custom::setCap(bool cap) {
    mCap = cap;
}

u32 Custom::throwCount() const {
    return mThrowCount;
}

void Custom::setThrowCount(u32 count) {
    mThrowCount = count;
}

void Custom::setSearchHat(bool isSearch) {
    const ParamData& param = obj().param().cappy();
    mIsSearchHat = isSearch;
    mSearchHatFrame = param.mSearchHatFrame;
}

bool Custom::isLostHat() {
    return mIsLostHat;
}

void Custom::returnHat() {
    obj().setPotentialCount(2);
    mIsSearchHat = false;
    mThrowCount = 120;
    obj().model().model().nodes().at(2).setVisibility(true);
    obj().model().model().nodes().at(3).setVisibility(false);
    mCap = true;
}

void Custom::setValidTurn(bool isValid) {
    mIsValidTurn = isValid;
}

bool Custom::isValidTurn() {
    return mIsValidTurn;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
