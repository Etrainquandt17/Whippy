#include "scn/step/enemy/common/StateShootingFly.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateShootingFly::StateShootingFly(Enemy* enemy) : StateBase(enemy), _8(0.0f) {
    init();
}

StateShootingFly::StateShootingFly(Enemy* enemy, f32 _8) : StateBase(enemy), _8(_8) {
    init();
}

StateShootingFly::~StateShootingFly() {}

void StateShootingFly::init() {
    obj().model().reqScript(4);
    obj().brainCtrl().toValid();
    obj().move().resetVelocity();
}

void StateShootingFly::procAnim() {}

void StateShootingFly::procMove() {
    const ParamData& param = obj().param().common();
    if (hel::math::Math::EqZero(_8)) {
        obj().move().decel(param._4c);
    } else {
        hel::math::Vector3 velocity = hel::math::Vector3::ZERO;
        if (!hel::math::Math::EqZero(_8)) {
            velocity.x += obj().comp().mainCamera().getCenter().x - _8;
            obj().move().setVelocity(velocity);
            gobj::MoveParamDecel decel = gobj::MoveParamDecel::Zero();
            obj().move().decel(decel);
        }
    }
}

void StateShootingFly::procFixPos() {}

}}}}  // namespace scn::step::enemy::common
