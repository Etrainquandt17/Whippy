#include "scn/step/boss/common/StateJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace common {

StateJump::StateJump(Boss* boss, StateJumpDesc& desc, u32 scriptKind) : StateBase(boss), mDesc(desc) {
    obj().footState().setAir();
    obj().model().reqScript(scriptKind);
    obj().objColl().bodyColl().initAttackType(mDesc._38);
    Vector2 speed(mDesc._0.x * obj().target().getSign(), mDesc._0.y);
    obj().move().setVelocity(speed.toVector3());
}

StateJump::~StateJump() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StateJump::procAnim() {
    if (mDesc._2C) {
        Utility::TurnHatedHero(obj());
    }
}

void StateJump::procMove() {
    obj().move().airDecelFall(mDesc._C, mDesc._10);
}

void StateJump::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    Vector3 velocity = obj().move().velocity();
    if (velocity.y < 0.0f && result.mIsHitFloor) {
        if (mDesc._34) {
            Vector2 pos = mDesc._1C;
            Vector2 speed = mDesc._24;
            Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
            obj().effect().normal().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos() + pos.toVector3());
            pos.x *= -1.0f;
            speed.x *= -1.0f;
            Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
            obj().effect().normal().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos() + pos.toVector3());
        }
        switch (mDesc._30) {
        case 0:
            obj().stateChanger().setNextState<StateLanding, Boss*>(objPtr());
            break;
        case 1:
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            break;
        case 2:
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
            obj().soundSE().normal().start(0x5B6);
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            break;
        }
    }
}

}}}}  // namespace scn::step::boss::common
