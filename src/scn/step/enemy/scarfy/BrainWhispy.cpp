#include "scn/step/enemy/scarfy/BrainWhispy.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/scarfy/Custom.h"
#include "scn/step/enemy/scarfy/StateAngerChase.h"
#include "scn/step/enemy/scarfy/StateFaceChange.h"
#include "scn/step/enemy/scarfy/StateWhispyAppear.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

BrainWhispy::BrainWhispy(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWhispy::onStart() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1c4));
    obj().stateChanger().setNextState<StateWhispyAppear, Enemy*>(&obj());
    return true;
}

bool BrainWhispy::onRecover() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isAngerFlag() == true) {
        obj().stateChanger().setNextState<StateAngerChase, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateFaceChange, Enemy*>(&obj());
    }
    return true;
}

}}}}  // namespace scn::step::enemy::scarfy
