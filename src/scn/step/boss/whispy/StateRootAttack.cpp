#include "scn/step/boss/whispy/StateRootAttack.h"

#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/whispy/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateRootAttack::StateRootAttack(Boss* boss) : StateBase(boss) {
    obj().model().reqScript(23);
}

StateRootAttack::~StateRootAttack() {}

void StateRootAttack::procAnim() {
    if (obj().scriptTrigger().get(0) || obj().model().isAllEnd()) {
        for (u32 i = 0; i < 4; i++) {
            hel::math::Vector2 pos = obj().location().pos().getXY();
            pos.x -= 2.0f + i;
            weapon::Desc desc(static_cast<weapon::Kind>(0x56), i, static_cast<ostop::Flag>(8), pos, hel::math::Vector2::ZERO, obj().objColl().owner());
            obj().comp().weaponManager().request(desc);
        }
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateRootAttack::procMove() {}

void StateRootAttack::procFixPos() {}

}
}
}
}
