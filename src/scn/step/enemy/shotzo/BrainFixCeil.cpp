#include "scn/step/enemy/shotzo/BrainFixCeil.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
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
#include "scn/step/enemy/shotzo/Custom.h"
#include "scn/step/enemy/shotzo/StateWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

BrainFixCeil::BrainFixCeil(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFixCeil::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    f32 angle = 0.0f;
    if (obj().dirType() != static_cast<map::BinEnemyDirType>(0) && obj().dirType() != static_cast<map::BinEnemyDirType>(1)) {
        f32 rot = Utility::GetRotByDirType(obj());
        angle = hel::math::Math::Atan2DegF(hel::math::Math::SinDegF(rot), -hel::math::Math::CosDegF(rot));
    }
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setAimAngle(angle);
    return true;
}

}
}
}
}
