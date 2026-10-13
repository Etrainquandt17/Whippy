#include "scn/step/enemy/leafan/StateAttack.h"

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
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/leafan/ParamData.h"
#include "scn/step/enemy/leafan/StateFall.h"
#include "scn/step/enemy/leafan/StateWait.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace leafan {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    obj().model().rotCtrl().setRotHTarget(0.0f);
}

void StateAttack::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().model().rotCtrl().resetRotTarget();
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    } else if (mFrame == obj().param().leafan().mAttackShotFrame) {
        f32 sign = obj().target().getSign();
        hel::math::Vector2 center = obj().location().pos().getXY();
        center.y += 0.5f;
        hel::math::Vector2 pos = center;
        hel::math::Vector2 velocity(sign * obj().param().leafan().mWeaponSpeed, 0.0f);
        velocity.x += obj().move().velocity().x;
        weapon::Desc desc(static_cast<weapon::Kind>(0x10), 0, static_cast<ostop::Flag>(4), pos, center, velocity, obj().objColl().owner());
        obj().comp().weaponManager().request(desc);
        desc.mVariation = 1;
        obj().comp().weaponManager().request(desc);
    }
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
