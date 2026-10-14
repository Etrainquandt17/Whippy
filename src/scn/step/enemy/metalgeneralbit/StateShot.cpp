#include "scn/step/enemy/metalgeneralbit/StateShot.h"

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
#include "scn/step/enemy/metalgeneralbit/ParamData.h"
#include "scn/step/enemy/metalgeneralbit/StateFly.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(8);
}

StateShot::~StateShot() {}

void StateShot::procAnim() {
    const ParamData& param = obj().param().metalgeneralbit();
    if (obj().model().anim().currentG3DAnimIndex() == 4 &&
        static_cast<f32>(param.mBeamFrame) == obj().model().anim().frame()) {
        reqBeam();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFly, Enemy*>(objPtr());
    }
}

void StateShot::procMove() {
    const ParamData& param = obj().param().metalgeneralbit();
    obj().move().decel(param.mDecel);
}

void StateShot::procFixPos() {}

void StateShot::reqBeam() {
    Vector2 pos = obj().location().pos().getXY();
    Vector2 offset = Vector2::ZERO;
    weapon::Desc desc(static_cast<weapon::Kind>(0x3f), 0, static_cast<ostop::Flag>(8), pos, offset, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
    obj().soundSE().start(0x1cc);
}

}}}}  // namespace scn::step::enemy::metalgeneralbit
