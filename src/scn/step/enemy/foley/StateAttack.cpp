#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/foley/StateAttack.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/foley/Custom.h"
#include "scn/step/enemy/foley/ParamData.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace foley {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), _8(false), mFrame(0) {
    const ParamData& param = obj().param().foley();
    obj().footState().setAir();
    obj().move().resetSpeedH();
    obj().model().reqScript(7);
    obj().model().anim().setFrameRate(param.mAttackFrameRate);
    mAnimFrame = static_cast<u32>(static_cast<f32>(obj().model().anim().totalFrame()) / param.mAttackFrameRate);
    obj().model().model().nodes().at(1).setVisibility(false);
    obj().model().model().nodes().at(2).setVisibility(false);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setAttack(true);
    obj().effect().state().requestN(static_cast<effect::Kind>(0x43), 3);
}

StateAttack::~StateAttack() {}

// TODO: the weapon's variation is held in r31 in the original and in r30 here; everything else matches.
void StateAttack::procAnim() {
    mFrame++;
    if (obj().model().anim().currentG3DAnimIndex() == 3) {
        if (mFrame == 6) {
            NodeAccessor node = obj().model().model().nodes().at(3);
            Vector2 pos = node.worldMtx().getT().getXY()
                          + Vector2(obj().target().getSign() * obj().param().foley().mWeaponOffsetX, 0.0f);
            bool isRight = obj().target().isRightDir();
            weapon::Desc desc(static_cast<weapon::Kind>(0x36), isRight, static_cast<ostop::Flag>(4), pos, Vector2::ZERO,
                              obj().objColl().owner());
            ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
            if (weapon.isAlive()) {
                f32 scale = Utility::GetModelScaleBySizeType(obj());
                weapon->model().setScale(Vector3(scale, scale, scale));
            }
        }
        if (obj().model().isAllEnd()) {
            obj().model().reqScript(8);
        }
    }
}

void StateAttack::procMove() {
    const ParamData& param = obj().param().foley();
    if (mFrame >= mAnimFrame + param.mAttackWaitFrame) {
        if (mFrame == mAnimFrame + param.mAttackWaitFrame) {
            obj().soundSEState().start(0x2bd);
            obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x242));
        }
        obj().move().airDecelFall(obj().param().common().mDecel, param.mAttackFall);
    }
}

void StateAttack::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).requestRollExp();
    }
}

}}}}  // namespace scn::step::enemy::foley
