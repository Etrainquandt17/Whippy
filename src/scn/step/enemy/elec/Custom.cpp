#include "scn/step/enemy/elec/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {
    obj().nururi().changeSetting(static_cast<nururi::Mode>(1));
}

void Custom::onProcFixPos() {
    hel::math::Vector3 dir = Utility::GetNearestPlayerPos(obj()).toVector3() - obj().location().pos();
    f32 angle = hel::math::Math::Atan2DegF(dir.y, dir.x);
    g3d::NodeAccessor node = obj().model().model().nodes().at(2);
    hel::math::Matrix34 mtx = hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(0.0f, angle, 0.0f));
    node.localMtx().setRTMtx(mtx);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}
}
}
}
