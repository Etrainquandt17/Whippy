#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/bulby/StateAttack.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
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
#include "scn/step/enemy/bulby/ParamData.h"
#include "scn/step/enemy/bulby/StateHide.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(12);
    obj().objColl().clearBodyColl();
    f32 scale = Utility::GetModelScaleBySizeType(obj());
    scale *= obj().param().bulby().mBodyRadius;
    obj().objColl().addBodyColl(1, scale);
}

void StateAttack::procAnim() {
    const ParamData& param = obj().param().bulby();
    mFrame++;
    if (mFrame == param.mAttackShotFrame) {
        shot(Vector3::BASIS_Y * param.mShotSpeed);
        if (obj().variation() == 0x66) {
            f32 sin = Math::SinDegF(param.mShotAngle);
            f32 cos = Math::CosDegF(param.mShotAngle);
            shot(Vector3(sin, cos, 0.0f) * param.mShotSpeed);
            shot(Vector3(-sin, cos, 0.0f) * param.mShotSpeed);
        }
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateHide, Enemy*>(objPtr());
    }
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

void StateAttack::shot(Vector3 velocity) {
    Vector2 nodePos = obj().model().model().nodes().at(0).worldMtx().getT().getXY();
    const ParamData& param = obj().param().bulby();
    Vector2 pos = nodePos + param.mShotOffset;
    weapon::Desc desc(static_cast<weapon::Kind>(0x34), 0, static_cast<ostop::Flag>(4), pos, velocity.getXY(),
                      obj().objColl().owner());
    ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        weapon->move().setVelocity(velocity);
    }
    obj().soundSE().start(0x2e8);
}

}}}}  // namespace scn::step::enemy::bulby
