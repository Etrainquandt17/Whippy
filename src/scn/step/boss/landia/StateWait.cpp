#include "scn/step/boss/landia/StateWait.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/landia/CollisionCtrl.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/WaftCtrl.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace landia {

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    custom.waftCtrl().setWaveDefault();
    obj().hateCtrl().fix();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {}

void StateWait::procMove() {}

void StateWait::procFixPos() {}

}}}}  // namespace scn::step::boss::landia
