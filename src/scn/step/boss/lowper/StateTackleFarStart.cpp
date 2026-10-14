#include "scn/step/boss/lowper/StateTackleFarStart.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateTackleFarStart::StateTackleFarStart(Boss* boss) : StateBase(boss), _8(), _14(0), _18(0.0f), _1C(1.0f), _20(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_TACKLE_FAR);
    Utility::ControlHateOnAction(obj());
    Vector3 pos = obj().basePos().toVector3();
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    Vector3 diff = heroPos - obj().basePos().toVector3();
    pos.y += 3.5f;
    pos.z = -80.0f;
    if (diff.x > 2.0f) {
        pos.x += 4.0f;
    }
    if (diff.x < -2.0f) {
        pos.x -= 4.0f;
    }
    custom.waftMoveCtrl().setMoveIntpRate(0.075f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
    obj().model().reqScript(8);
    obj().model().rotCtrl().setRotHTarget(0.0f);
}

StateTackleFarStart::~StateTackleFarStart() {}

void StateTackleFarStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateTackleFarStart::procMove() {}

void StateTackleFarStart::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
