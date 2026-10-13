#include "scn/step/weapon/mahoroasuperbeamball/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroasuperbeamball/Custom.h"
#include "scn/step/weapon/mahoroasuperbeamball/StateGlide.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperbeamball {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().model().rotCtrl().setValid(false);
    obj().culling().setValid(false);
    obj().effect().normal().requestN(
        Utility::IsExtra(obj()) ? static_cast<effect::Kind>(0x417) : static_cast<effect::Kind>(0x42D), 0,
        hel::math::Vector3(0.0f, 0.0f, -3.0f)
    );
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x203));
    obj().objColl().addAttack(0, Utility::IsExtra(obj()) ? 2.5f : 3.0f);
    obj().objColl().setAttackCenter(0, hel::math::Vector2::ZERO);
}

StateMain::~StateMain() {
    obj().objColl().clearAttack();
}

void StateMain::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isRequestedStartGlide()) {
        obj().stateChanger().setNextState<StateGlide, Weapon*, hel::math::Vector3, u32>(
            objPtr(), custom.getTargetPos(), custom.getGlideTotalFrame()
        );
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
    hel::geo::Rect rect = static_cast<const Component&>(obj().comp()).mainCamera().getViewRect();
    rect._0 -= 1.0f;
    rect._4 += 1.0f;
    rect._8 += 1.0f;
    rect._C -= 1.0f;
    hel::math::Vector3 pos = obj().location().pos();
    hel::math::Vector3 velocity = obj().move().velocity();
    bool isReflect = false;
    if (pos.x < rect._8) {
        velocity.x = hel::math::Math::Abs(velocity.x);
        isReflect = true;
    }
    if (pos.x > rect._C) {
        velocity.x = -1.0f * hel::math::Math::Abs(velocity.x);
        isReflect = true;
    }
    if (pos.y < rect._4) {
        velocity.y = hel::math::Math::Abs(velocity.y);
        isReflect = true;
    }
    if (pos.y > rect._0) {
        velocity.y = -1.0f * hel::math::Math::Abs(velocity.y);
        isReflect = true;
    }
    if (isReflect) {
        velocity.setLength(0.01f + velocity.length());
        obj().move().setVelocity(velocity);
        obj().soundSE().start(0x41C);
    }
}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroasuperbeamball
