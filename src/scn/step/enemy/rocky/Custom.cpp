#include "scn/step/enemy/rocky/Custom.h"

#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/rocky/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsFallSpeedUp(false) {}

bool Custom::onInit() {
    obj().objColl().clearBodyColl();
    f32 radius = Utility::GetModelScaleBySizeType(obj());
    radius *= obj().param().rocky().mBodyCollRadius;
    obj().objColl().addBodyColl(2, radius);
    return false;
}

void Custom::setFallSpeedUp(bool isFallSpeedUp) {
    mIsFallSpeedUp = isFallSpeedUp;
}

bool Custom::isFallSpeedUp() {
    return mIsFallSpeedUp;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}
}
}
}
