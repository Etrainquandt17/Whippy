#include "scn/step/enemy/como/BrainWhispy.h"

#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/como/StateAppear.h"
#include "scn/step/enemy/como/StateBack.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

BrainWhispy::BrainWhispy(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWhispy::onStart() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1C4));
    obj().stateChanger().setNextState<StateAppear, Enemy*>(&obj());
    return true;
}

bool BrainWhispy::onRecover() {
    obj().stateChanger().setNextState<StateBack, Enemy*>(&obj());
    return true;
}

}
}
}
}
