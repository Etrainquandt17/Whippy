#include "scn/step/boss/lowper/StateSparkShot.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateSparkShot::StateSparkShot(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0x25);
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.1f);
}

StateSparkShot::~StateSparkShot() {}

void StateSparkShot::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqBullet();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateSparkShot::procMove() {}

void StateSparkShot::procFixPos() {}

void StateSparkShot::reqBullet() {
    Vector3 pos = obj().location().pos();
    pos.y += 0.5f;
    Vector3 speed(0.3f * obj().target().getSign(), 0.0f, 0.0f);
    weapon::Desc desc(static_cast<weapon::Kind>(0x80), 0, static_cast<ostop::Flag>(8), pos.getXY(), speed.getXY(),
                      obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}}}}  // namespace scn::step::boss::lowper
