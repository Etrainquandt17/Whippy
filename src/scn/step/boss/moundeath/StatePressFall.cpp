#include "scn/step/boss/moundeath/StatePressFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StatePressFall::StatePressFall(Boss* boss, JumpKind kind) : StateBase(boss), mKind(kind) {
    const Param& param = obj().param().moundeath();
    obj().footState().setAir();
    f32 speed = 0.0f;
    switch (mKind) {
    case JUMP_KIND_0:
        speed = param._8C;
        obj().model().reqScript(3);
        obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AC));
        break;
    case JUMP_KIND_1:
        speed = param._A4;
        obj().model().reqScript(3);
        obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AC));
        break;
    case JUMP_KIND_2:
        speed = param._C0;
        obj().model().reqScript(0x11);
        obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1B4));
        break;
    }
    obj().move().setVelocity(Vector3(0.0f, speed, 0.0f));
}

StatePressFall::~StatePressFall() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StatePressFall::procAnim() {}

void StatePressFall::procMove() {
    const Param& param = obj().param().moundeath();
    obj().move().airDecelFall(param._28, param._2C);
}

void StatePressFall::procFixPos() {
    const Param& param = obj().param().moundeath();
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        Vector2 pos(param._44.x * obj().target().getSign(), param._44.y);
        Vector2 speed(param._4C.x * obj().target().getSign(), param._4C.y);
        Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos() + pos.toVector3());
        pos.x *= -1.0f;
        speed.x *= -1.0f;
        Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos() + pos.toVector3());
        switch (mKind) {
        case JUMP_KIND_0:
            obj().stateChanger().setNextState<common::StateLanding, Boss*, ScriptKind>(objPtr(), static_cast<ScriptKind>(0xB));
            break;
        case JUMP_KIND_1:
            obj().stateChanger().setNextState<common::StateLanding, Boss*, ScriptKind>(objPtr(), static_cast<ScriptKind>(0xE));
            break;
        case JUMP_KIND_2:
            obj().stateChanger().setNextState<common::StateLanding, Boss*, ScriptKind>(objPtr(), static_cast<ScriptKind>(0xF));
            break;
        }
    }
}

}}}}  // namespace scn::step::boss::moundeath
