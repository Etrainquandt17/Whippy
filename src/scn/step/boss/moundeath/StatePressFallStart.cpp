#include "scn/step/boss/moundeath/StatePressFallStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "scn/step/boss/moundeath/StatePressFall.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StatePressFallStart::StatePressFallStart(Boss* boss, JumpKind kind) : StateBase(boss), mKind(kind), mCount(0), mFrame(0) {
    const Param& param = obj().param().moundeath();
    obj().footState().setAir();
    f32 speed = 0.0f;
    switch (mKind) {
    case JUMP_KIND_0:
        speed = param._84;
        mFrame = param._88;
        obj().model().reqScript(0xC);
        break;
    case JUMP_KIND_1:
        speed = param._9C;
        mFrame = param._A0;
        obj().model().reqScript(0xC);
        break;
    case JUMP_KIND_2:
        speed = param._B8;
        mFrame = param._BC;
        obj().model().reqScript(0x10);
        obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AC));
        break;
    }
    obj().move().setVelocity(Vector3(0.0f, speed, 0.0f));
}

StatePressFallStart::~StatePressFallStart() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StatePressFallStart::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StatePressFall, Boss*, JumpKind>(objPtr(), mKind);
    }
}

void StatePressFallStart::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StatePressFallStart::procFixPos() {}

}}}}  // namespace scn::step::boss::moundeath
