#include "scn/step/enemy/bowby/StateAttack.h"

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
#include "scn/step/enemy/bowby/Custom.h"
#include "scn/step/enemy/bowby/ParamData.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace bowby {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setAnimStart(true);
}

StateAttack::~StateAttack() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setAnimStart(false);
}

void StateAttack::procAnim() {
    if (obj().model().anim().currentG3DAnimIndex() == 0) {
        obj().brainCtrl().toValid();
    }
    if (obj().model().anim().currentG3DAnimIndex() == 3) {
        if (obj().model().anim().frame() == static_cast<f32>(obj().param().bowby().mShotFrame)) {
            hel::math::Vector2 nodePos = obj().model().model().nodes().at(1).worldMtx().getT().getXY();
            hel::math::Vector2 pos = nodePos;
            weapon::Kind kind = static_cast<weapon::Kind>(0x37);
            if (obj().kind() == 0x5f) {
                kind = static_cast<weapon::Kind>(0x92);
            }
            weapon::Desc desc(kind, 0, static_cast<ostop::Flag>(4), pos, nodePos, hel::math::Vector2::ZERO, obj().objColl().owner());
            switch (obj().dirType()) {
            case 4:
                desc.mVariation = 0;
                break;
            case 5:
                desc.mVariation = 1;
                break;
            case 3:
                desc.mVariation = 2;
                break;
            default:
                desc.mVariation = 3;
                break;
            }
            obj().comp().weaponManager().request(desc);
        }
    }
}

}}}}  // namespace scn::step::enemy::bowby
