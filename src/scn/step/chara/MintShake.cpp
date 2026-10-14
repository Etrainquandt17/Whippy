#include "scn/step/chara/MintShake.h"

#include "hel/common/PointerWrapper.h"
#include "scn/step/chara/Shake.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace chara {

namespace {

PointerWrapper<Shake> t_obj;

}

namespace MintShake {

void Register(Shake& obj) {
    t_obj.set(obj);
}

void Unregister(Shake&) {
    t_obj.reset();
}

void Request(int kind) {
    t_obj->request(static_cast<ShakeKind>(kind));
}

}}}}  // namespace scn::step::chara::MintShake
