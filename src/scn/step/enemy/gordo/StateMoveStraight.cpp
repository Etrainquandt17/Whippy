#include "scn/step/enemy/gordo/StateMoveStraight.h"

#include "gobj/FootState.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/gordo/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

namespace {

// TODO: chara::MapCollResult::isHitWall(), which the shared header declares without its body.
inline bool t_IsHitWall(const chara::MapCollResult& result) {
    return result._2 || result._3;
}

}

StateMoveStraight::StateMoveStraight(Enemy* enemy)
    : StateBase(enemy), mDir(Utility::GetDirVecByDirType(*enemy)), mBaseX(obj().location().pos().x) {
    obj().footState().setAir();
    obj().model().reqScript(0);
}

void StateMoveStraight::procMove() {
    hel::math::Vector3 pos = obj().location().pos();
    pos += mDir * obj().param().gordo().mStraightSpeed;
    if (obj().dirType() == 4 || obj().dirType() == 5) {
        pos.x = mBaseX;
    }
    obj().location().setPos(pos);
}

void StateMoveStraight::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || obj().mapColl().result().mIsHitRoof || t_IsHitWall(obj().mapColl().result())) {
        mDir = -mDir;
    }
}

}}}}  // namespace scn::step::enemy::gordo
