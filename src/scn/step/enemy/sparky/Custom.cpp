#include "scn/step/enemy/sparky/Custom.h"

#include "scn/step/chara/Effect.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sparky/ParamData.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace sparky {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x503), 2);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x503), 3);
    obj().objColl().clearBodyColl();
    f32 radius = Utility::GetModelScaleBySizeType(obj());
    radius *= obj().param().sparky().mBodyRadius;
    obj().objColl().addBodyColl(1, radius);
    return false;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::sparky
