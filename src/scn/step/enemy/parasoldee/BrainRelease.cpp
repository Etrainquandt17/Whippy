#include "scn/step/enemy/parasoldee/BrainRelease.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/parasoldee/Custom.h"
#include "scn/step/enemy/parasoldee/StateFall.h"
#include "scn/step/enemy/parasoldee/StateParasolFall.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace parasoldee {

BrainRelease::BrainRelease(Enemy& enemy) : BrainBase(enemy) {}

bool BrainRelease::onStart() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setReleaseOnLanding();
    obj().stateChanger().setNextState<StateParasolFall, Enemy*>(&obj());
    return true;
}

bool BrainRelease::onRecover() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

void BrainRelease::update() {
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::parasoldee
