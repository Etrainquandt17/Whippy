// TODO: isAlive() is inline in the original; the shared header has its body behind this.
#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/boss/dubior/StateShot.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjList.h"

using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace dubior {

StateShot::StateShot(Boss* boss, f32 angle) : StateBase(boss), mAngle(angle) {
    obj().footState().setAir();
    obj().model().reqScript(12);
}

StateShot::~StateShot() {}

void StateShot::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqShot();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateShot::procMove() {
    const Param& param = obj().param().dubior();
    obj().move().decel(param._4C);
}

void StateShot::procFixPos() {}

void StateShot::reqShot() {
    const Param& param = obj().param().dubior();
    Vector2 pos = obj().location().pos().getXY();
    pos += Vector2(param.mShotOffset.x * obj().target().getSign(), param.mShotOffset.y);
    enemy::Desc desc(static_cast<map::BinEnemyKind>(0x77), map::BinEnemyVariation_0, 0, static_cast<map::BinEnemyDirType>(0),
                     static_cast<map::BinEnemySize>(0), false, false, pos);
    desc._28 = true;
    desc._20 = obj().location().pos().getXY();
    ObjRefHandle<enemy::Enemy> shot = obj().comp().enemyManager().request(desc);
    if (shot.isAlive()) {
        Vector3 velocity = Vector3::BASIS_Y * -1.0f;
        velocity.rotate(Vector3::AXIS_Z, 0.017453292f * mAngle);
        velocity.x *= obj().target().getSign();
        velocity *= param.mShotSpeed;
        shot->move().setVelocity(velocity);
        return;
    }
}

}}}}  // namespace scn::step::boss::dubior
