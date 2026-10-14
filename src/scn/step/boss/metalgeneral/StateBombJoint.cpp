#include "scn/step/boss/metalgeneral/StateBombJoint.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateBombJoint::StateBombJoint(Boss* boss, JointKind kind) : StateBase(boss), mKind(kind) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    switch (mKind) {
    case JOINT_KIND_0:
        obj().model().reqScript(0x1F);
        Utility::ControlHateOnAction(obj());
        break;
    case JOINT_KIND_1:
        obj().model().reqScript(0x21);
        break;
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().move().resetVelocity();
}

StateBombJoint::~StateBombJoint() {}

void StateBombJoint::procAnim() {
    if (obj().model().isAllEnd()) {
        switch (mKind) {
        case JOINT_KIND_0:
            obj().brainCtrl().toValid();
            break;
        case JOINT_KIND_1:
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            break;
        }
    }
}

void StateBombJoint::procMove() {}

void StateBombJoint::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
