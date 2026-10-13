#include "scn/step/enemy/searches/StateAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/searches/ParamData.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace searches {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0), mDeadFrame(0), mIsExploded(false) {
    obj().footState().setAir();
    obj().move().resetVelocity();
    obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x241));
}

void StateAttack::procAnim() {
    mFrame++;
    if (mFrame == obj().param().searches().mAttackFrame) {
        obj().model().reqScript(7);
        obj().soundSEState().start(0x30c);
    }
    if (obj().model().isAllEnd() && !mIsExploded) {
        mIsExploded = true;
        mDeadFrame = obj().param().searches().mDeadFrame;
        hel::math::Vector2 velocity(0.0f, 0.0f);
        hel::math::Vector2 pos = obj().location().pos().getXY();
        pos.y += 0.5f;
        weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 3, static_cast<ostop::Flag>(4), pos, pos, velocity,
                          obj().objColl().owner());
        obj().comp().weaponManager().request(desc);
        obj().comp().permSoundSE().start(0x50e);
        obj().objColl().clearBodyColl();
        obj().vacuumReceiver().setIsValid(false);
        obj().deadChallenge();
    }
    if (mIsExploded) {
        mDeadFrame--;
        if (mDeadFrame == 0) {
            obj().dead();
        }
    }
}

}}}}  // namespace scn::step::enemy::searches
