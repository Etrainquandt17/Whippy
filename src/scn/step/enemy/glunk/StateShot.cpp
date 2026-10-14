#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/glunk/StateShot.h"

#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/glunk/Custom.h"
#include "scn/step/enemy/glunk/ParamData.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().model().reqScript(7);
}

StateShot::~StateShot() {}

void StateShot::procAnim() {
    if (++mFrame == obj().param().glunk().mShotFrame) {
        shot();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFly, Enemy*>(objPtr());
    }
}

void StateShot::procFixPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!custom.checkExistLand()) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
        custom.setIsCurrentFall(true);
    }
}

void StateShot::shot() {
    obj().soundSE().start(0x2c5);
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(0x30);
    desc.mVariation = 0;
    desc.mFlag = static_cast<ostop::Flag>(4);
    NodeAccessor node = obj().model().model().nodes().at(1);
    desc.mPos = node.worldMtx().getT().getXY();
    desc._14 = obj().location().pos().getXY();
    desc._1c = node.worldMtx().getY().getXY();
    desc.mOwner = &obj().objColl().owner();
    ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        weapon->move().setVelocity(node.worldMtx().getZ() * -1.0f);
    }
}

}}}}  // namespace scn::step::enemy::glunk
