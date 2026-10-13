#include "scn/step/boss/MintBoss.h"

#include "hel/common/PointerWrapper.h"

namespace scn {
namespace step {
namespace boss {

namespace {

hel::common::PointerWrapper<Boss> t_obj;

}

namespace MintBoss {

void Register(Boss& obj) {
    t_obj.set(obj);
}

void Unregister(Boss&) {
    t_obj.reset();
}

Boss& Obj() {
    return t_obj.ref();
}

}}}}  // namespace scn::step::boss::MintBoss
