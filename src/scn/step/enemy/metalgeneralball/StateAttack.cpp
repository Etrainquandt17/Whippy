#include "scn/step/enemy/metalgeneralball/StateAttack.h"

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
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/metalgeneralball/ParamData.h"
#include "scn/step/enemy/metalgeneralball/StateWait.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

using hel::math::Vector2;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralball {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(8);
    obj().move().resetVelocity();
}

StateAttack::~StateAttack() {}

void StateAttack::procAnim() {
    const ParamData& param = obj().param().metalgeneralball();
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    } else if (obj().model().anim().currentG3DAnimIndex() == 4 &&
               static_cast<f32>(param.mBeamFrame) == obj().model().anim().frame()) {
        reqBeam();
    }
}

void StateAttack::procMove() {}

void StateAttack::procFixPos() {}

void StateAttack::reqBeam() {
    Vector2 pos = obj().location().pos().getXY();
    weapon::Desc desc(static_cast<weapon::Kind>(0x3f), 1, static_cast<ostop::Flag>(8), pos, Vector2::ZERO,
                      obj().objColl().owner());
    const ObjRefHandle<weapon::Weapon>& beam = obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::enemy::metalgeneralball
