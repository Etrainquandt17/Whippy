#include "scn/step/boss/watergalboros/StateQuivery.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/watergalboros/Param.h"
#include "scn/step/boss/watergalboros/ScriptKind.h"
#include "scn/step/boss/watergalboros/StateAttackJoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using app::Random;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

StateQuivery::StateQuivery(Boss* boss, Config config) : StateBase(boss), mRot(0.0f), mCount(0), mConfig(config), mIsStart(false) {
    mRot = 90.0f;
    obj().footState().setGround();
    obj().model().reqScript(0xC);
}

StateQuivery::~StateQuivery() {}

void StateQuivery::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsStart = true;
    }
    if (mIsStart) {
        if (++mCount % mConfig._4 == 0) {
            reqQuivery();
        }
        mRot = obj().model().rotCtrl().calcChangedRot(mRot, true, 360.0f / (f32)mConfig._0);
        obj().model().rotCtrl().initRotH(mRot);
        if (mCount == mConfig._0) {
            obj().stateChanger().setNextState<StateAttackJoint, Boss*, ScriptKind>(objPtr(), SCRIPT_KIND_13);
        }
    }
}

void StateQuivery::procMove() {
    const Param& param = obj().param().watergalboros();
    obj().move().groundDecel(param._24);
}

void StateQuivery::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

void StateQuivery::reqQuivery() {
    const Param& param = obj().param().watergalboros();
    Vector2 pos = obj().location().pos().getXY();
    pos += Vector2(param.mQuiveryOffset.x * obj().target().getSign(), param.mQuiveryOffset.y);
    Vector2 speed(param.mQuiverySpeed.x * Random::RandAF(), param.mQuiverySpeed.y);
    weapon::Desc desc(static_cast<weapon::Kind>(0x33), 0, static_cast<ostop::Flag>(8), pos, speed, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::boss::watergalboros
