#include "scn/step/gimmick/challengedoor/MintChallengeDoor.h"

#include "hel/common/PointerWrapper.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace gimmick {
namespace challengedoor {

namespace {

PointerWrapper<ChallengeDoor> t_obj;

}

void MintChallengeDoor::Register(ChallengeDoor& obj) {
    t_obj.set(obj);
}

void MintChallengeDoor::Unregister(ChallengeDoor&) {
    t_obj.reset();
}

ChallengeDoor& MintChallengeDoor::Obj() {
    return t_obj.ref();
}

}}}}  // namespace scn::step::gimmick::challengedoor
