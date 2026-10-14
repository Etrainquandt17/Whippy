#include "scn/step/boss/hrd3/StateFirst.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/ShadowCtrl.h"
#include "scn/step/boss/hrd3/StateAppear.h"
#include "scn/step/chara/Model.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateFirst::StateFirst(Boss* boss) : StateBase(boss), mCount(boss->param().hrd3()._4C) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().setVisibility(false);
    custom.shadowCtrl().setVisibility(false);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
}

StateFirst::~StateFirst() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().setVisibility(true);
    custom.shadowCtrl().setVisibility(true);
}

void StateFirst::procAnim() {
    if (mCount != 0) {
        if (--mCount == 0) {
            u32 num = obj().comp().bossManager().getBossCount();
            bool isExist = false;
            for (u32 i = 0; i < num; i++) {
                ObjRefHandle<Boss> boss = obj().comp().bossManager().getBossByIndex(i);
                if (boss.operator->() != 0 && boss->kind() == static_cast<map::BinBossKind>(0xB)) {
                    isExist = true;
                }
            }
            if (!isExist) {
                obj().stateChanger().setNextState<StateAppear, Boss*, bool>(objPtr(), false);
            }
        }
    }
}

void StateFirst::procMove() {}

void StateFirst::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
