#include "scn/step/enemy/owgulf/StateAttack1Way.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
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
#include "scn/step/enemy/owgulf/Custom.h"
#include "scn/step/enemy/owgulf/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

StateAttack1Way::StateAttack1Way(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(8);
    effect::Kind kind = obj().target().isRightDir() ? static_cast<effect::Kind>(0x5a3) : static_cast<effect::Kind>(0x5a2);
    obj().effect().state().requestP(kind, obj().model().model().nodes().at(1).worldMtx().getT());
}

void StateAttack1Way::procAnim() {
    if (++mFrame == obj().param().owgulf().m1WayFrame) {
        f32 sin = hel::math::Math::SinDegF(obj().param().owgulf().m1WayAngle);
        f32 cos = hel::math::Math::CosDegF(obj().param().owgulf().m1WayAngle);
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).shot(obj().location().pos() + hel::math::Vector3(0.0f, 0.5f, 0.0f), hel::math::Vector3(cos * obj().target().getSign(), -sin, 0.0f) * 0.1f,
        static_cast<weapon::owgulffeather::VariationKind>(0));
    }
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

}}}}  // namespace scn::step::enemy::owgulf
