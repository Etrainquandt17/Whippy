#include "scn/step/boss/landia/StateWindCutter.h"

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
#include "scn/step/boss/landia/StateWindCutterTurn.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/boss/landia/WindCtrl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateWindCutter::StateWindCutter(Boss* boss, Config config) : StateBase(boss), mConfig(config) {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    switch (mConfig._0) {
    case 0:
        obj().model().reqScript(16);
        break;
    case 1:
        obj().model().reqScript(17);
        break;
    case 2:
        obj().model().reqScript(18);
        break;
    case 3:
        obj().model().reqScript(19);
        break;
    case 4:
        obj().model().reqScript(20);
        break;
    }
    custom.waftCtrl().setWaveWidth(hel::math::Vector2(param._124));
    custom.waftCtrl().setWaveThetaVel(hel::math::Vector2(param._12C, param._12C));
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateWindCutter::~StateWindCutter() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).windCtrl().clear();
}

void StateWindCutter::procAnim() {
    const Param& param = obj().param().landia();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        if (mConfig._0 == 3) {
            obj().stateChanger().setNextState<StateWindCutterTurn, Boss*>(objPtr());
        } else {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        }
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        reqWindCutter(false);
    }
    if (obj().scriptTrigger().get(1)) {
        reqWindCutter(true);
    }
    if (obj().scriptTrigger().get(2)) {
        custom.windCtrl().set(param._1EC * obj().target().getSign(), param._1F0 * obj().target().getSign(),
                              param._1F4 * obj().target().getSign());
    }
    if (obj().scriptTrigger().get(3)) {
        custom.windCtrl().clear();
    }
}

void StateWindCutter::procMove() {
    const Param& param = obj().param().landia();
    obj().move().decel(param.mDecel);
}

void StateWindCutter::procFixPos() {}

void StateWindCutter::reqWindCutter(bool isBig) {
    hel::math::Vector2 pos = hel::math::Vector2::ZERO;
    pos = obj().model().model().nodes().at(2).worldTrans().getXY();
    hel::math::Vector2 dir = hel::math::Vector2::BASIS_X * obj().target().getSign();
    // TODO: the original normalises the bool into its own saved register ahead of the owner() call (one instruction more).
    weapon::Desc desc(static_cast<weapon::Kind>(0x68), isBig != false, static_cast<ostop::Flag>(8), pos, dir, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

}
}
}
}
