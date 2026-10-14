#include "scn/step/boss/kingsdoo/StateChargeAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/kingsdoo/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjList.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

extern "C" double acos(double x);

StateChargeAttack::StateChargeAttack(Boss* boss, Config config) : StateBase(boss), mConfig(config) {
    obj().footState().setGround();
    obj().model().reqScript(18);
}

StateChargeAttack::~StateChargeAttack() {}

void StateChargeAttack::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqWaveShot();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
    }
}

void StateChargeAttack::procMove() {
    const Param& param = obj().param().kingsdoo();
    obj().move().groundDecel(param._24);
}

void StateChargeAttack::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

void StateChargeAttack::reqWaveShot() {
    const Param& param = obj().param().kingsdoo();
    Vector2 pos = obj().location().pos().getXY();
    pos += Vector2(param.mWaveShotOffset.x * obj().target().getSign(), param.mWaveShotOffset.y);
    Vector2 dir = Vector2::ZERO;
    if (mConfig._1) {
        dir = Utility::GetHatedHeroPos(obj()).getXY() - obj().location().pos().getXY();
        if (dir.isZeroLoose(0.00001f)) {
            dir = Vector2::BASIS_X * obj().target().getSign();
        } else {
            f32 angle = acos(dir.cos(Vector2::BASIS_X * obj().target().getSign()));
            if (angle > 0.017453292f * param.mWaveShotAngleMax) {
                dir = Vector2::BASIS_X * obj().target().getSign();
                dir.rotate(0.017453292f * param.mWaveShotAngleMax * obj().target().getSign());
            }
        }
        dir.normalize();
    } else {
        dir = Vector2::BASIS_X * obj().target().getSign();
    }
    bool isNormal = !mConfig._0;
    weapon::Desc desc(static_cast<weapon::Kind>(0x32), isNormal, static_cast<ostop::Flag>(8), pos, dir, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
    obj().move().setSpeedH(param.mWaveShotRecoil * -obj().target().getSign());
}

}}}}  // namespace scn::step::boss::kingsdoo
