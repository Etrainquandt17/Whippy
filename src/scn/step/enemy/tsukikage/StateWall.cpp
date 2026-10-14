#include "scn/step/enemy/tsukikage/StateWall.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/tsukikage/Custom.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

StateWall::StateWall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isWall()) {
        if (obj().dirType() == static_cast<map::BinEnemyDirType>(3)) {
            obj().model().reqScript(11);
            obj().model().rotCtrl().initRotH(90.0f);
        } else {
            obj().model().reqScript(10);
            obj().model().rotCtrl().initRotH(90.0f);
        }
        obj().model().rotCtrl().setValid(false);
    }
    obj().brainCtrl().toValid();
}

StateWall::~StateWall() {
    obj().model().rotCtrl().setValid(true);
}

}}}}  // namespace scn::step::enemy::tsukikage
