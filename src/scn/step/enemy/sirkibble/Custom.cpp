#include "scn/step/enemy/sirkibble/Custom.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sirkibble/ParamData.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsPlayerUpPos(false), mIsChangeDirType(false), mIsNextTurnJump(false) {
    if (obj().dirType() == 2 || obj().dirType() == 3) {
        mIsChangeDirType = false;
    } else {
        mIsChangeDirType = true;
    }
    mJumpLog2 = true;
    mJumpLog1 = true;
    mJumpLog0 = true;
}

bool Custom::onDamaged() {
    setNextTurnJumpInvalid();
    return false;
}

void Custom::onProcFixPos() {
    if (obj().footState().isAir()) {
        obj().signal().set(0);
    }
}

void Custom::reqWeapon() {
    const ParamData& param = obj().param().sirkibble();
    f32 sign = obj().target().getSign();
    hel::math::Vector2 center = Utility::GetCenterPos(obj()).getXY();
    hel::math::Vector2 pos = center;
    pos.x += sign * param.mWeaponOffsetX;
    hel::math::Vector2 velocity(sign * param.mWeaponSpeed, 0.0f);
    weapon::Desc desc(static_cast<weapon::Kind>(0xe), 0, static_cast<ostop::Flag>(4), pos, center, velocity, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

void Custom::chkPlayerPos() {
    f32 playerY = Utility::GetNearestPlayerPos(obj()).y;
    if (playerY >= 1.0f + obj().location().pos().y) {
        mIsPlayerUpPos = true;
    } else {
        mIsPlayerUpPos = false;
    }
}

void Custom::chkNextTurnJump() {
    if (obj().variation() == 0x13) {
        mIsNextTurnJump = false;
        return;
    }
    if (app::Random::Rand(3) == 0) {
        mIsNextTurnJump = true;
    } else {
        mIsNextTurnJump = false;
    }
    mJumpLog2 = mJumpLog1;
    mJumpLog1 = mJumpLog0;
    mJumpLog0 = mIsNextTurnJump;
    if (mJumpLog2 == mJumpLog1 && mJumpLog1 == mJumpLog0) {
        if (mJumpLog0 == true) {
            mIsNextTurnJump = false;
        } else {
            mIsNextTurnJump = true;
        }
    }
    mJumpLog0 = mIsNextTurnJump;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

bool Custom::isPlayerUpPos() {
    return mIsPlayerUpPos;
}

bool Custom::isChangeDirType() {
    return mIsChangeDirType;
}

bool Custom::isNextTurnJump() {
    return mIsNextTurnJump;
}

void Custom::setNextTurnJumpInvalid() {
    mIsNextTurnJump = false;
}

}}}}  // namespace scn::step::enemy::sirkibble
