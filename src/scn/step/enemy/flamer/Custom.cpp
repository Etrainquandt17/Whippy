#include "scn/step/enemy/flamer/Custom.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/flamer/ParamData.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mAttackCount(0), mIsMove(true) {
    obj().nururi().changeSetting(static_cast<nururi::Mode>(1));
}

void Custom::attack() {
    mAttackCount++;
}

bool Custom::isAttackEnd() const {
    return mAttackCount >= obj().param().flamer().mAttackNum;
}

void Custom::dead() {
    obj().deadWithEffect();
}

bool Custom::isMove() const {
    return mIsMove;
}

void Custom::setIsMove(bool isMove) {
    mIsMove = isMove;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::flamer
