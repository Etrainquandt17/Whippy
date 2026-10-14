#include "scn/step/hero/supersword/MintSwordSelector.h"

#include "hel/common/PointerWrapper.h"
#include "scn/step/hero/supersword/SwordSelector.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace hero {
namespace supersword {

namespace {

PointerWrapper<SwordSelector> t_obj;

}

namespace MintSwordSelector {

void Register(SwordSelector& obj) {
    t_obj.set(obj);
}

void Unregister(SwordSelector&) {
    t_obj.reset();
}

void SetKind(int kind) {
    t_obj->setKind(kind);
}

void SetRareTryCount(int count) {
    t_obj->setRareTryCount(count);
}

}}}}}  // namespace scn::step::hero::supersword::MintSwordSelector
