#include "scn/step/hero/parasol/Custom.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/ObjColl.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

// TODO: the original reads mHero for comp() into a saved register ahead of the call to owner() (31
// instructions against 30).
Custom::Custom(Hero& hero)
    : AbilityCustomBase(hero)
    , mBarrier(mHero.comp().objCollManager(), mHero.objColl().objColl().owner(), 1) {
}

Custom::~Custom() {
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

::ocoll::Attack& Custom::barrier() {
    return mBarrier;
}

}
}
}
}
