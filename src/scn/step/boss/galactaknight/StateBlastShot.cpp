#include "scn/step/boss/galactaknight/StateBlastShot.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateBlastShot::StateBlastShot(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0x16);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateBlastShot::~StateBlastShot() {}

void StateBlastShot::procAnim() {
    if (obj().scriptTrigger().get(3)) {
        generateBlastShot();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateBlastShot::procMove() {}

void StateBlastShot::procFixPos() {}

void StateBlastShot::generateBlastShot() {
    const Param& param = obj().param().galactaknight();
    Vector2 pos = obj().location().pos().getXY();
    pos.y += param._B4;
    Vector2 start = pos;
    start.x += param._B0 * obj().target().getSign();
    Vector2 dir = Vector2::BASIS_X;
    dir.x *= obj().target().getSign();
    dir *= param._AC;
    weapon::Desc desc(static_cast<weapon::Kind>(0x89), 0, static_cast<ostop::Flag>(8), start, pos, dir,
                      obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::boss::galactaknight
