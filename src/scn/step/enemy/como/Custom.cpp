#include "scn/step/enemy/como/Custom.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

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

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

ThreadCtrl& Custom::threadCtrl() {
    return mThreadCtrl;
}

}}}}  // namespace scn::step::enemy::como
