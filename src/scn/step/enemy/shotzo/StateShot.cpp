#include "scn/step/enemy/shotzo/StateShot.h"

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
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/shotzo/Custom.h"
#include "scn/step/enemy/shotzo/ParamData.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "snd/SERequestor.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().brainCtrl().toValid();
    obj().model().reqScript(7);
}

void StateShot::procAnim() {
    if (++mFrame == 10) {
        shot();
    }
}

void StateShot::procMove() {
    const common::ParamData& param = obj().param().common();
    if (!DynamicCastToRef<Custom, ICustom>(obj().custom()).isFixPos() && obj().footState().isAir()) {
        obj().move().airDecelFall(param.mDecel, param.mFall);
    } else {
        obj().move().resetSpeedV();
    }
}

void StateShot::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().footState().setGround();
    } else {
        obj().footState().setAir();
    }
}

void StateShot::shot() {
    obj().soundSE().start(0x2b3);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4dc), 2);
    f32 speed = obj().variation() == 0x139 ? obj().param().shotzo().mShotSpeed : 1.0f;
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(0xf);
    desc.mVariation = 0;
    desc.mFlag = static_cast<ostop::Flag>(4);
    NodeAccessor node = obj().model().model().nodes().at(2);
    desc.mPos = node.worldMtx().getT().getXY();
    desc._14 = obj().location().pos().getXY() + Vector2(0.0f, 0.5f);
    desc._1c = node.worldMtx().getZ().getXY() * speed;
    desc.mOwner = &obj().objColl().owner();
    obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::enemy::shotzo
