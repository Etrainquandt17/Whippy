#include "scn/step/enemy/metalgeneralthunder/StateAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/metalgeneralthunder/ParamData.h"
#include "scn/step/enemy/metalgeneralthunder/StateWait.h"
#include "scn/step/ocoll/AttackType.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralthunder {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().move().resetVelocity();
}

StateAttack::~StateAttack() {
    obj().objColl().clearAttack();
    obj().effect().state().releaseAndVanish();
}

void StateAttack::procAnim() {
    const ParamData& param = obj().param().metalgeneralthunder();
    mFrame++;
    if (mFrame % 5 == 0) {
        if (mFrame < param.mAttackFrame) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(0));
        } else {
            obj().model().shake().request(static_cast<chara::ShakeKind>(1));
        }
    }
    if (mFrame == param.mAttackFrame) {
        obj().effect().state().requestN(static_cast<effect::Kind>(0x45d), 0);
        obj().soundSE().start(0x4b7);
        obj().objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x1dd));
        obj().objColl().addAttack(0, 0, param.mAttackRadius, hel::math::Vector2::ZERO, hel::math::Vector2(param.mAttackOffset));
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateAttack::procMove() {}

void StateAttack::procFixPos() {}

}}}}  // namespace scn::step::enemy::metalgeneralthunder
