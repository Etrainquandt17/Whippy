#include "scn/step/boss/landia/StateFireBreath.h"

#include "g3d/NodeAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/Param.h"
#include "scn/step/boss/landia/StateWait.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateFireBreath::StateFireBreath(Boss* boss, Config config) : StateBase(boss) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    switch (config._0) {
    case 0:
        obj().model().reqScript(11);
        break;
    case 1:
        obj().model().reqScript(12);
        break;
    case 2:
        obj().model().reqScript(29);
        break;
    }
    custom.waftCtrl().setWaveWidthZero();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateFireBreath::~StateFireBreath() {}

void StateFireBreath::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        reqFireBreath(MOUTH_KIND_0);
    }
    if (obj().scriptTrigger().get(1)) {
        reqFireBreath(MOUTH_KIND_1);
    }
    if (obj().scriptTrigger().get(2)) {
        reqFireBreath(MOUTH_KIND_2);
    }
    if (obj().scriptTrigger().get(3)) {
        reqFireBreath(MOUTH_KIND_3);
    }
}

void StateFireBreath::procMove() {
    const Param& param = obj().param().landia();
    obj().move().decel(param.mDecel);
}

void StateFireBreath::procFixPos() {}

void StateFireBreath::reqFireBreath(MouthKind kind) {
    hel::math::Vector2 pos = hel::math::Vector2::ZERO;
    switch (kind) {
    case MOUTH_KIND_0:
        pos = obj().model().model().nodes().at(7).worldTrans().getXY();
        break;
    case MOUTH_KIND_1:
        pos = obj().model().model().nodes().at(8).worldTrans().getXY();
        break;
    case MOUTH_KIND_2:
        pos = obj().model().model().nodes().at(9).worldTrans().getXY();
        break;
    case MOUTH_KIND_3:
        pos = obj().model().model().nodes().at(10).worldTrans().getXY();
        break;
    }
    hel::math::Vector2 dir = hel::math::Vector2::BASIS_X * obj().target().getSign();
    weapon::Desc desc(static_cast<weapon::Kind>(0x66), 0, static_cast<ostop::Flag>(8), pos, dir, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}
}
}
}
