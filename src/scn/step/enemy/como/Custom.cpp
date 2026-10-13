#include "scn/step/enemy/como/Custom.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mThreadCtrl(enemy) {}

bool Custom::onHitPointIsZero() {
    mThreadCtrl.cut();
    return false;
}

void Custom::onCaptured() {
    mThreadCtrl.cut();
}

void Custom::onProcFixPos() {
    mThreadCtrl.update();
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

ThreadCtrl& Custom::threadCtrl() {
    return mThreadCtrl;
}

}
}
}
}
