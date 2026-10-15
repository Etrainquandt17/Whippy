#define MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE
#define SCN_STEP_GIMMICK_MANAGER_SWITCHRECEIVERMANAGER_IN_CLASS

#include "scn/step/boss/goliath/StateDeadGroundChange.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/gimmick/SwitchReceiverManager.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/item/ShipPartKind.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateDeadGroundChange::StateDeadGroundChange(Boss* boss) : StateBase(boss), mFrame(30) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().model().setVisibility(false);
    obj().shadow().setVisibility(false);
}

StateDeadGroundChange::~StateDeadGroundChange() {}

void StateDeadGroundChange::procAnim() {
    changeGround();
    if (mFrame != 0) {
        mFrame--;
        if (mFrame == 0) {
            obj().comp().heroManager().setNextStateDemoFallAll();
        }
    }
}

void StateDeadGroundChange::procMove() {}

void StateDeadGroundChange::procFixPos() {}

void StateDeadGroundChange::changeGround() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!custom.landCtrl().isMaxLevel()) {
        reqGroundBreakEffect();
        obj().soundSE().normal().start(0x36B);
        u32 level = custom.landCtrl().getLevel();
        custom.landCtrl().levelUp();
        obj().comp().gimmickManager().switchReceiverManager().onSwitchOn(level);
        custom.cameraCtrl().startDeadGroundChange();
        if (custom.landCtrl().isMaxLevel()) {
            reqItem();
        }
    }
}

void StateDeadGroundChange::reqItem() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Vector2 goal(custom.landCtrl().getCenterX(), 2.5f + custom.landCtrl().getFloorY());
    Utility::GenerateShipParts(obj(), static_cast<item::ShipPartKind>(3),
                               obj().location().pos() + Vector3(0.0f, 1.75f, 0.0f), goal);
}

void StateDeadGroundChange::reqGroundBreakEffect() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    int num = static_cast<int>(custom.landCtrl().getWidth() / 4.0f) + 1;
    f32 step = custom.landCtrl().getWidth() / static_cast<f32>(num + 1);
    Vector3 pos(custom.landCtrl().getCenterX() - 0.5f * custom.landCtrl().getWidth(),
                0.5f * (custom.landCtrl().getFloorY() + custom.landCtrl().getFloorYWithBump()) - 0.5f, 0.0f);
    for (int i = 0; i < num; i++) {
        pos.x += step;
        obj().effect().fore().requestP(static_cast<effect::Kind>(0x1DB), pos);
    }
}

}}}}  // namespace scn::step::boss::goliath
