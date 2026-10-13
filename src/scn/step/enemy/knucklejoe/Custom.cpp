#include "scn/step/enemy/knucklejoe/Custom.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
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
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/knucklejoe/ParamData.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mAttack(0), mAttackCount(0), mSpeed(0.0f), mAnimRate(0.0f), mNowLoop(0), mHitWall(false) {
    const ParamData& param = obj().param().knucklejoe();
    switch (obj().level()) {
    case 0:
        mSpeed = param.mSpeed[0];
        break;
    case 1:
        mSpeed = param.mSpeed[0];
        break;
    case 2:
        mSpeed = param.mSpeed[1];
        break;
    default:
        mSpeed = param.mSpeed[2];
        break;
    }
    mAnimRate = mSpeed / 0.02f;
}

bool Custom::onInit() {
    mAttack = 0;
    mAttackCount = 0;
    return false;
}

bool Custom::onDamaged() {
    mHitWall = false;
    resetNowLoop();
    return false;
}

f32 Custom::getSpeed() const {
    return mSpeed;
}

f32 Custom::getAnimRate() const {
    return mAnimRate;
}

u32 Custom::getNowLoop() const {
    return mNowLoop;
}

void Custom::resetNowLoop() {
    mNowLoop = 0;
}

void Custom::incNowLoop() {
    mNowLoop++;
}

int Custom::getAttack() const {
    return mAttack;
}

void Custom::setAttack() {
    int attack;
    int near = 4;
    int far = 4;
    hel::math::Vector2 diff = Utility::GetNearestPlayerPos(obj()) - obj().location().pos().getXY();
    if (hel::math::Math::Abs(diff.x) >= 3.0f) {
        near = 8;
    }
    if (obj().level() == 0) {
        far = 0;
    } else if (diff.y > 1.0f) {
        far = 8;
    }
    int rand = app::Random::Rand(far + near + 8);
    if (rand < near) {
        attack = 1;
    } else if (rand < near + 4) {
        attack = 3;
    } else {
        attack = rand < near + 8 ? 4 : 2;
    }
    if (mAttack == attack) {
        mAttackCount++;
        if (mAttackCount >= obj().param().knucklejoe().mAttackRepeatMax) {
            mAttackCount = 0;
            switch (attack) {
            case 1:
                rand = app::Random::Rand(far + 8);
                if (rand < 4) {
                    attack = 3;
                } else if (rand < 8) {
                    attack = 4;
                } else {
                    attack = 2;
                }
                break;
            case 2:
                rand = app::Random::Rand(near + 8);
                if (rand < near) {
                    attack = 1;
                } else if (rand < near + 4) {
                    attack = 3;
                } else {
                    attack = 4;
                }
                break;
            case 3:
                rand = app::Random::Rand(far + 4 + near);
                if (rand < near) {
                    attack = 1;
                } else if (rand < near + 4) {
                    attack = 4;
                } else {
                    attack = 2;
                }
                break;
            case 4:
                rand = app::Random::Rand(far + 4 + near);
                if (rand < near) {
                    attack = 1;
                } else if (rand < near + 4) {
                    attack = 3;
                } else {
                    attack = 2;
                }
                break;
            }
        }
    } else {
        mAttackCount = 0;
    }
    mAttack = attack;
}

void Custom::shot() {
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(0x3d);
    desc.mVariation = 0;
    desc.mFlag = static_cast<ostop::Flag>(4);
    g3d::NodeAccessor node = obj().model().model().nodes().at(1);
    desc.mPos = obj().location().pos().getXY() + hel::math::Vector2(obj().target().getSign(), 0.6f);
    desc._14 = obj().location().pos().getXY() + hel::math::Vector2(obj().target().getSign(), 0.6f);
    desc._1c = hel::math::Vector2(obj().target().getSign() * 0.25f, 0.0f);
    desc.mOwner = &obj().objColl().owner();
    obj().comp().weaponManager().request(desc);
}

void Custom::setHitWall(bool isHit) {
    mHitWall = isHit;
}

bool Custom::getHitWall() {
    return mHitWall;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::knucklejoe
